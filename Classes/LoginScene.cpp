#include "LoginScene.h"
#include "GameScene.h"

#define TAG_CHAT_BG 1

Scene *LoginScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoginScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoginScene::init()
{
	if (!Layer::init())
		return false;

	m_iCurMsgIndex = 0;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *touch, Event *event){
		return true;
	};
	listener->onTouchEnded = [&](Touch *touch, Event *event)
	{
		this->showNextMsg();
	};
	Size winSize = Director::getInstance()->getWinSize();
	Sprite* bgSp = Sprite::create("storybg.png");
	bgSp->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	bgSp->setScaleX(winSize.width / 640);
	bgSp->setScaleY(winSize.height / 960);
	this->addChild(bgSp, 0, 0);

	Sprite* chatBg = Sprite::create("chatbg.png");
	chatBg->setPosition(Vec2(winSize.width / 2, chatBg->getContentSize().height / 2));
	this->addChild(chatBg, 1, TAG_CHAT_BG);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->readJson();
	this->showNextMsg();
	return true;
}

void LoginScene::readJson()
{
	std::string path = FileUtils::getInstance()->fullPathForFilename("story.json");
	Data date = FileUtils::getInstance()->getDataFromFile(path.c_str());
	
	//data构建string
	content = std::string((const char*)date.getBytes(), 0, date.getSize());
	rapidjson::Document document;
	document.Parse<0>(content.c_str());
	//解析错误
	CCASSERT(!document.HasParseError(), "Parsing to document failure");
	const rapidjson::Value &redatas = document["datas"];
	for (unsigned int i = 0; i < redatas.Size(); i++)
	{
		row = ValueMap();
		const rapidjson::Value &redate = redatas[i];
		const rapidjson::Value &re_name = redate["name"];
		row["name"] = Value(re_name.GetString());
		const rapidjson::Value &re_msg = redate["msg"];
		row["msg"] = Value(re_msg.GetString());
		const rapidjson::Value &re_picture = redate["picture"];
		row["picture"] = Value(re_picture.GetString());
		list.push_back(Value(row));
	}
}

void LoginScene::showNextMsg()
{
	int size = list.size();
	if (m_iCurMsgIndex > size)
		return;
	if (m_iCurMsgIndex == size)
	{
		rapidjson::Document document;
		document.SetObject();
		rapidjson::Document::AllocatorType &allocator = document.GetAllocator();
		rapidjson::Value array(rapidjson::kArrayType);
		rapidjson::Value array1(rapidjson::kArrayType);
		rapidjson::Value array2(rapidjson::kArrayType);
		rapidjson::Value object1(rapidjson::kObjectType);
		rapidjson::Value object2(rapidjson::kObjectType);
		
		object1.AddMember("level", 1, allocator);		//等级
		object1.AddMember("exlevel", 0, allocator);		//品阶
		object1.AddMember("type", 3, allocator);		//类型
		object1.AddMember("xp", 0, allocator);			//经验
		object1.AddMember("pos", 1, allocator);			//位置
		object1.AddMember("index", 0, allocator);		//索引
		object1.AddMember("zhuang0", 300000, allocator);	//头盔
		object1.AddMember("zhuang1", 400000, allocator);	//盔甲
		object1.AddMember("zhuang2", 500000, allocator);	//武器
		object1.AddMember("zhuang3", 600000, allocator);	//宝物
		object1.AddMember("zhuang4", 700000, allocator);	//鞋子
		object1.AddMember("zhuang5", 800000, allocator);	//坐骑
		array1.PushBack(object1, allocator);

		object2.AddMember("level", 1, allocator);
		object2.AddMember("exlevel", 0, allocator);
		object2.AddMember("type", 108, allocator);
		object2.AddMember("xp", 0, allocator);
		object2.AddMember("pos", 2, allocator);
		object2.AddMember("index", 1, allocator);
		object2.AddMember("zhuang0", 300000, allocator);
		object2.AddMember("zhuang1", 400000, allocator);
		object2.AddMember("zhuang2", 500000, allocator);
		object2.AddMember("zhuang3", 600000, allocator);
		object2.AddMember("zhuang4", 700000, allocator);
		object2.AddMember("zhuang5", 800000, allocator);
		array2.PushBack(object2, allocator);

		array.PushBack(array1, allocator);
		array.PushBack(array2, allocator);
		document.AddMember("MyHero", array, allocator);

		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

		document.Accept(writer);

		std::string path = FileUtils::getInstance()->getWritablePath();
		path.append("myhero.json");
		FILE *file = fopen(path.c_str(), "wb");
		if (file)
		{
			fputs(buffer.GetString(), file);
			fclose(file);
		}

		this->saveZhuangBei();

		auto scene = new GameScene(0);
		Director::getInstance()->replaceScene(scene);
		return;
	}
	std::string name = list.at(m_iCurMsgIndex).asValueMap().at("name").asString();
	std::string msg = list.at(m_iCurMsgIndex).asValueMap().at("msg").asString();
	std::string picture = list.at(m_iCurMsgIndex).asValueMap().at("picture").asString();
	log("name = %s", name.c_str());
	log("msg = %s", msg.c_str());
	log("picture = %s", picture.c_str());

	Sprite* chatBG = (Sprite*)this->getChildByTag(TAG_CHAT_BG);
	chatBG->removeAllChildrenWithCleanup(true);
	Size bgSize = chatBG->getContentSize();

	/* 人物名字 */
	LabelTTF* nameLab = LabelTTF::create(name.c_str(), "Arial", 32);
	nameLab->setPosition(ccp(bgSize.width * 0.2f, bgSize.height * 0.9f));
	nameLab->setColor(Color3B::RED);
	chatBG->addChild(nameLab, 1);

	/* 对话内容 */
	LabelTTF* msgLab = LabelTTF::create(msg.c_str(), "Arial", 32, CCSize(300, 0), kCCTextAlignmentLeft);
	msgLab->setPosition(Vec2(bgSize.width / 2 - 120, bgSize.height * 0.4f));
	msgLab->setColor(Color3B::BLUE);
	chatBG->addChild(msgLab, 1);

	/* 人物图片 */
	Sprite* actorSp = Sprite::create(picture.c_str());
	CCSize actorSize = actorSp->getContentSize();
	actorSp->setPosition(Vec2(bgSize.width - actorSize.width / 2, actorSize.height / 2));
	chatBG->addChild(actorSp, 1);

	m_iCurMsgIndex++;
}

void LoginScene::saveZhuangBei()
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType &allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);
	rapidjson::Value array1(rapidjson::kArrayType);
	rapidjson::Value array2(rapidjson::kArrayType);
	rapidjson::Value array3(rapidjson::kArrayType);
	rapidjson::Value array4(rapidjson::kArrayType);
	rapidjson::Value array5(rapidjson::kArrayType);
	rapidjson::Value object1(rapidjson::kObjectType);
	rapidjson::Value object2(rapidjson::kObjectType);
	rapidjson::Value object3(rapidjson::kObjectType);
	rapidjson::Value object4(rapidjson::kObjectType);
	rapidjson::Value object5(rapidjson::kObjectType);

	object1.AddMember("level", 1, allocator);//等级
	object1.AddMember("exlevel", 0, allocator);//品介
	object1.AddMember("type", 301, allocator);//类型
	object1.AddMember("index", 0, allocator);//卡牌索引
	object1.AddMember("user", -1, allocator);//哪个英雄装备
	array1.PushBack(object1, allocator);

	object2.AddMember("level", 1, allocator);
	object2.AddMember("exlevel", 0, allocator);//品介
	object2.AddMember("type", 401, allocator);
	object2.AddMember("index", 1, allocator);
	object2.AddMember("user", -1, allocator);//哪个英雄装备
	array2.PushBack(object2, allocator);

	object3.AddMember("level", 1, allocator);
	object3.AddMember("exlevel", 0, allocator);//品介
	object3.AddMember("type", 501, allocator);//公孙胜武器七星剑
	object3.AddMember("index", 2, allocator);
	object3.AddMember("user", -1, allocator);//哪个英雄装备
	array3.PushBack(object3, allocator);

	object4.AddMember("level", 1, allocator);
	object4.AddMember("exlevel", 0, allocator);//品介
	object4.AddMember("type", 601, allocator);
	object4.AddMember("index", 3, allocator);
	object4.AddMember("user", -1, allocator);//哪个英雄装备
	array4.PushBack(object4, allocator);

	object5.AddMember("level", 1, allocator);
	object5.AddMember("exlevel", 0, allocator);//品介
	object5.AddMember("type", 701, allocator);
	object5.AddMember("index", 4, allocator);
	object5.AddMember("user", -1, allocator);//哪个英雄装备
	array5.PushBack(object5, allocator);

	array.PushBack(array1, allocator);
	array.PushBack(array2, allocator);
	array.PushBack(array3, allocator);
	array.PushBack(array4, allocator);
	array.PushBack(array5, allocator);

	document.AddMember("ZhuangBei", array, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> wirte(buffer);

	document.Accept(wirte);

	std::string path = FileUtils::getInstance()->getWritablePath();
	path.append("myzhuanbei.json");
	FILE *file = fopen(path.c_str(), "wb");
	if (file)
	{
		fputs(buffer.GetString(), file);
		fclose(file);
	}
}