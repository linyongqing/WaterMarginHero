#include "GameData.h"
#include "Config.h"
#define MAXVALUE 10000
#define MINVALUE -1
#define SIZE 14
#define NUMBER 5

static GameData *game = NULL;

GameData::GameData()
{
	roleDic = __Dictionary::create();
	roleDic->retain();
	dic = __Dictionary::create();
	dic->retain();
	subMapId = 0;
	mapId = 0;
	speed = 3;

	mlevel = UserDefault::getInstance()->getIntegerForKey("level", 1);
	mxp = UserDefault::getInstance()->getIntegerForKey("xp", 1);
	mMoney = UserDefault::getInstance()->getIntegerForKey("money", 20000);
	mCoin = UserDefault::getInstance()->getIntegerForKey("coin", 200);
	
	UserDefault::getInstance()->flush();
	
	this->readZhuangbei();
	this->readJson();
}

GameData::~GameData(){}

GameData * GameData::shareGameData(){
	if (!game){
		game = new GameData();
	}
	return game;
}

void GameData::readZhuangbei()
{
	std::string path = FileUtils::getInstance()->getWritablePath() + "myzhuanbei.json";
	Data data = FileUtils::getInstance()->getDataFromFile(path.c_str());

	std::string content = std::string((const char*)data.getBytes(), 0, data.getSize());

	rapidjson::Document document;
	document.Parse<0>(content.c_str());
	map<int, ZhuangBeiType> ZhuangTypes = Config::sharedConfig()->getZhuangBei();
	if (!document.HasParseError())
	{
		rapidjson::Value &reZhuang = document["ZhuangBei"];
		for (int i = 0; i < reZhuang.Size(); i++)
		{
			ZhuangBeiType zhuang;
			int level = reZhuang[i]["level"].GetInt();//等级
			int type = reZhuang[i]["type"].GetInt();//类型
			zhuang.exlevel = reZhuang[i]["exlevel"].GetInt();//经验
			zhuang.index = reZhuang[i]["index"].GetInt();//索引
			zhuang.type = type;
			zhuang.level = level;
			zhuang.ap = 0;
			zhuang.hp = 0;
			zhuang.user = reZhuang[i]["user"].GetInt();
			zhuang.magicdefender = 0;
			zhuang.defender = 0;

			map<int, ZhuangBeiType>::iterator iter = ZhuangTypes.find(type);

			if (iter != ZhuangTypes.end())
			{
				ZhuangBeiType headtype = iter->second;
				zhuang.star = headtype.star;//星级
				zhuang.name = headtype.name;
				zhuang.hp = headtype.hp + headtype.hp*level / 10;
				zhuang.ap = headtype.ap + headtype.ap*level / 10;
				zhuang.textureName = headtype.textureName;//图片
				zhuang.defender = headtype.defender + headtype.defender*level / 10;
				zhuang.magicdefender = headtype.magicdefender + headtype.magicdefender*level / 10;
				m_ZhuangBeis.push_back(zhuang);
			}
		}
	}
}

void GameData::readJson()
{
	unsigned  long nSize = 0;
	string path = FileUtils::getInstance()->getWritablePath() + "myhero.json";
	Data data = FileUtils::getInstance()->getDataFromFile(path.c_str());
	
	std::string content = std::string((const char*)data.getBytes(), 0, data.getSize());
	rapidjson::Document document;
	document.Parse<0>(content.c_str());
	if (document.HasParseError())
	{
		rapidjson::Value &reMyHero = document["MyHero"];
		map<int, HeroType> HeroTypes = Config::sharedConfig()->getHerosType();
		map<int, ZhuangBeiType> ZhuangTypes = Config::sharedConfig()->getZhuangBei();
		for (unsigned int i = 0; i < reMyHero.Size(); ++i)
		{
			HeroType herodata;
			herodata.level = reMyHero[i]["level"].GetInt();//等级
			herodata.exlevel = reMyHero[i]["exlevel"].GetInt();//强化等级
			herodata.type = reMyHero[i]["type"].GetInt();//类型
			herodata.xp = reMyHero[i]["xp"].GetInt();//经验
			herodata.pos = reMyHero[i]["pos"].GetInt();//位置
			herodata.index = reMyHero[i]["index"].GetInt();//索引
			map<int, HeroType>::iterator iterHero = HeroTypes.find(herodata.type);
			if (iterHero != HeroTypes.end())
			{
				HeroType herotype = iterHero->second;
				herodata.name = herotype.name;
				herodata.textureName = herotype.textureName;//英雄图片
				herodata.card = herotype.card;//花色
				herodata.number = herotype.number;//数字
				herodata.exname = herotype.exname;//绰号
				herodata.starname = herotype.starname;//星座


				herodata.hp = (herotype.hp + herotype.hp*herodata.level / 10)*(1 + herodata.exlevel / 10.0);//卡牌总血量
				herodata.ap = (herotype.ap + herotype.ap*herodata.level / 10)*(1 + herodata.exlevel / 10.0);//卡牌总攻击
				herodata.defend = herotype.defend;
				herodata.magicdefend = herotype.magicdefend;
				herodata.skillsid = herotype.skillsid;
				herodata.attackid = herotype.attackid;
				herodata.totalmagicdefend = 0;
				herodata.totaldefend = 0;
				herodata.totalap = herodata.ap;
				herodata.totalhp = herodata.hp;
				herodata.des = herotype.des;
				herodata.skillsname = herotype.skillsname;


				for (int j = 0; j < 6; j++)
				{
					char str[32];
					sprintf(str, "zhuang%d", j);
					int head = reMyHero[i][str].GetInt();//头盔类型等级
					char strIndex[32];
					sprintf(strIndex, "index%d", j);
					int index = reMyHero[i][strIndex].GetInt();//头盔类型等级

					int headlevel = head % 100;
					int type = head / 1000;
					map<int, ZhuangBeiType>::iterator iter = ZhuangTypes.find(type);
					if (iter != ZhuangTypes.end())
					{
						ZhuangBeiType headtype = iter->second;
						herodata.zhuang[j].index = index;
						herodata.zhuang[j].type = type;//类型
						herodata.zhuang[j].level = headlevel;//等级
						herodata.zhuang[j].star = headtype.star;//星级
						herodata.zhuang[j].name = headtype.name;
						herodata.zhuang[j].textureName = headtype.textureName;//图片
						herodata.zhuang[j].defender = headtype.defender + headtype.defender*headlevel / 10;
						herodata.zhuang[j].magicdefender = headtype.magicdefender + headtype.magicdefender*headlevel / 10;
						herodata.zhuang[j].hp = headtype.hp + headtype.hp*headlevel / 10;
						herodata.zhuang[j].ap = headtype.ap + headtype.ap*headlevel / 10;
						herodata.totalap += herodata.zhuang[i].ap;
						herodata.totalhp += herodata.zhuang[i].hp;
						herodata.totaldefend += herodata.zhuang[i].defender;
						herodata.totalmagicdefend += herodata.zhuang[i].magicdefender;
					}
					else
					{
						herodata.zhuang[j].type = 0;//类型
						herodata.zhuang[j].level = 0;//等级
						herodata.zhuang[j].star = 0;//星级
						herodata.zhuang[j].defender = 0;
						herodata.zhuang[j].magicdefender = 0;
						herodata.zhuang[j].hp = 0;
						herodata.zhuang[j].ap = 0;
					}
				}
				if (herodata.exlevel >= 2)
				{
					float number = ((108 - herodata.type) / 10 + 20) / 100 + 1.0;
					herodata.totalhp *= number;
				}
				else if (herodata.exlevel >= 5)
				{
					float number1 = (herodata.type / 10 + 20) % 100 + 1;
					herodata.totalap *= number1;
				}
			}
			m_Heros.push_back(herodata);
		}
	}
}

void GameData::saveDefault()
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType &allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);
	rapidjson::Value object(rapidjson::kObjectType);

	object.AddMember("level", 1, allocator);//等级
	object.AddMember("exlevel", 0, allocator);//品介
	object.AddMember("type", 3, allocator);//类型
	object.AddMember("xp", 0, allocator);//经验
	object.AddMember("pos", 1, allocator);//位置
	object.AddMember("index", 0, allocator);//卡牌索引
	object.AddMember("zhuang0", 300000, allocator);//头盔
	object.AddMember("zhuang1", 400000, allocator);//盔甲
	object.AddMember("zhuang2", 500000, allocator);//武器
	object.AddMember("zhuang3", 600000, allocator);//宝物
	object.AddMember("zhuang4", 700000, allocator);//鞋子
	object.AddMember("zhuang5", 800000, allocator);//坐骑
	object.AddMember("index0", -1, allocator);//头盔
	object.AddMember("index1", -1, allocator);//盔甲
	object.AddMember("index2", -1, allocator);//武器
	object.AddMember("index3", -1, allocator);//宝物
	object.AddMember("index4", -1, allocator);//鞋子
	object.AddMember("index5", -1, allocator);//坐骑
	
	object.AddMember("level", 1, allocator);//等级
	object.AddMember("exlevel", 0, allocator);//品介
	object.AddMember("type", 108, allocator);//类型
	object.AddMember("xp", 0, allocator);//经验
	object.AddMember("pos", 2, allocator);//位置
	object.AddMember("index", 1, allocator);//卡牌索引
	object.AddMember("zhuang0", 300000, allocator);//头盔
	object.AddMember("zhuang1", 400000, allocator);//盔甲
	object.AddMember("zhuang2", 500000, allocator);//武器
	object.AddMember("zhuang3", 600000, allocator);//宝物
	object.AddMember("zhuang4", 700000, allocator);//鞋子
	object.AddMember("zhuang5", 800000, allocator);//坐骑
	object.AddMember("index0", -1, allocator);//头盔
	object.AddMember("index1", -1, allocator);//盔甲
	object.AddMember("index2", -1, allocator);//武器
	object.AddMember("index3", -1, allocator);//宝物
	object.AddMember("index4", -1, allocator);//鞋子
	object.AddMember("index5", -1, allocator);//坐骑

	array.PushBack(array, allocator);
	document.AddMember("myhero", array, allocator);

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

}

void GameData::setData(int money, int xp)
{
	mMoney = money;
	mxp = xp;
	int totalxp = getexp(1.1, mlevel);
	if (mxp >= totalxp)
	{
		mxp -= totalxp;
		mlevel++;
	}
	UserDefault::getInstance()->setIntegerForKey("level", mlevel);
	UserDefault::getInstance()->setIntegerForKey("money", money);
	UserDefault::getInstance()->setIntegerForKey("xp", xp);
	UserDefault::getInstance()->flush();
}

vector<ZhuangBeiType> GameData::getZhuangbei()
{
	return m_ZhuangBeis;
}

int GameData::getexp(float x, int n)
{
	if (n == 0)
	{
		return LEVELXP;
	}

	return x * getexp(x, n - 1);
}

