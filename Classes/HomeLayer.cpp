#include "HomeLayer.h"
#include "ui\UIImageView.h"
#include "GameData.h"
#include "EquipmentLayer.h"

USING_NS_CC;

const float PAUSE_MENU_POS_X = 460;
const float PAUSE_MENU_POS_Y = 300;

const float JOYSTICK_POS_X = 50;
const float JOYSTICK_POS_Y = 50;
const float JOYSTICK_DEAD_RADIUS = 10;
const float JOYSTICK_THRESHOLD = 0.4f;

const float BTN_A_POS_X = 430;
const float BTN_A_POS_Y = 50;

HomeLayer::HomeLayer()
{
	isBeingUsed = false;
	init();
}

HomeLayer::~HomeLayer()
{

}

bool HomeLayer::init()
{
	if (!Layer::init())
		return false;
	this->setKeyboardEnabled(true);

	auto ul = Layer::create();
	this->addChild(ul);

	Size winSize = Director::getInstance()->getWinSize();

	auto image = ui::ImageView::create("level.png");
	image->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 240));
	ul->addChild(image);

	mlevel = GameData::shareGameData()->mlevel;
	mxp = GameData::shareGameData()->mxp;
	char str[32];
	sprintf(str, "%d", mlevel);
	levellabel = Label::create();
	levellabel->setSystemFontSize(48);
	levellabel->setString(str);
	levellabel->setPosition(ccp(image->getPosition().x + 20, image->getPosition().y - 10));
	ul->addChild(levellabel);

	int totalxp = getExp(1.1, mlevel);
	auto timebg = ui::ImageView::create("xp2.png");
	timebg->setPosition(Vec2(winSize.width / 2, image->getPosition().y - image->getContentSize().height / 2 - 20));
	ul->addChild(timebg);

	auto sp = Sprite::create("xp1.png");
	healthBar = ProgressTimer::create(sp);
	ul->addChild(healthBar);
	healthBar->setPosition(Vec2(winSize.width / 2, image->getPosition().y - image->getContentSize().height / 2 - 20));
	healthBar->setType(kCCProgressTimerTypeBar);
	healthBar->setMidpoint(Vec2(0, 0.5));
	healthBar->setBarChangeRate(Vec2(1, 0));
	healthBar->setPercentage(((float)mxp / (float)totalxp) * 100);

	__String *exp = __String::createWithFormat("%d/%d", mxp, totalxp);
	xpLabel = LabelTTF::create(exp->getCString(), "Arial", 25);
	xpLabel->setColor(Color3B::BLUE);
	xpLabel->setPosition(healthBar->getPosition());
	ul->addChild(xpLabel);

	auto *moneyBg = ui::ImageView::create("coin1.png");
	moneyBg->setPosition(Vec2(winSize.width / 2 - 60, winSize.height / 2 - moneyBg->getPosition().y + 100));
	ul->addChild(moneyBg);

	auto *coinBg = ui::ImageView::create("money1.png");
	coinBg->setPosition(Vec2(winSize.width / 2 - 60, winSize.height / 2 - coinBg->getPosition().y));

	ul->addChild(coinBg);

	int money = GameData::shareGameData()->mMoney;
	__String *strMoney = __String::createWithFormat("%d", money);
	moneyLabel = LabelTTF::create();
	moneyLabel->setFontSize(32);
	moneyLabel->setPosition(Vec2(120 + moneyBg->getPosition().x, moneyBg->getPosition().y));
	moneyLabel->setString(strMoney->getCString());
	this->addChild(moneyLabel);

	int coin = GameData::shareGameData()->mCoin;
	__String *strCoin = __String::createWithFormat("%d", coin);
	coinLabel = LabelTTF::create();
	coinLabel->setFontSize(32);
	coinLabel->setPosition(Vec2(coinBg->getPosition().x + 120, coinBg->getPosition().y));
	coinLabel->setString(strCoin->getCString());
	addChild(coinLabel);

	auto *textButton = ui::Button::create();
	textButton->setEnabled(true);
	textButton->loadTextures("zhuangbei1.png", "zhuangbei2.png", "zhuangbei2.png");
	textButton->setPosition(Vec2(textButton->getContentSize().width / 2, winSize.height / 2 + 100));
	textButton->addClickEventListener(CC_CALLBACK_1(HomeLayer::menuCallback, this));
	textButton->setTag(11);
	ul->addChild(textButton);

	auto *textButton1 = ui::Button::create();
	textButton1->setEnabled(true);
	textButton1->loadTextures("yinxiong1.png", "yinxiong2.png", "");
	textButton1->setPosition(Vec2(textButton1->getContentSize().width / 2, winSize.height / 2));
	textButton1->addClickEventListener(CC_CALLBACK_1(HomeLayer::menuCallback, this));
	textButton1->setTag(12);
	ul->addChild(textButton1);

	auto *textButton2 = ui::Button::create();
	textButton2->setEnabled(true);
	textButton2->loadTextures("login1.png", "login2.png", "");
	textButton2->setPosition(Vec2(winSize.width - textButton2->getContentSize().width / 2, winSize.height / 2 + 100));
	textButton2->addClickEventListener(CC_CALLBACK_1(HomeLayer::menuCallback, this));
	textButton2->setTag(13);
	ul->addChild(textButton2);

	auto *textButton3 = ui::Button::create();
	textButton3->setEnabled(true);
	textButton3->loadTextures("levelup1.png", "levelup2.png", "");
	textButton3->setPosition(Vec2(winSize.width - textButton3->getContentSize().width / 2, winSize.height / 2));
	textButton3->addClickEventListener(CC_CALLBACK_1(HomeLayer::menuCallback, this));
	textButton3->setTag(14);
	ul->addChild(textButton3);

	UserDefault *TextFieldV = UserDefault::getInstance();
	coinNum = TextFieldV->getIntegerForKey("coin", 20000);
	diamondsNum = TextFieldV->getIntegerForKey("money", 200);
	UserDefault::sharedUserDefault()->flush();

	healthBarLogic(NULL);
	return true;
}

void HomeLayer::onExit()
{
	
}

void HomeLayer::update(float dt)
{

}

int HomeLayer::getExp(float x, float n)
{
	if (n == 0)
	{
		return LEVELXP;
	}

	return x * getExp(x, n - 1);
}

void HomeLayer::healthBarLogic(Ref *sender)
{
	int level = GameData::shareGameData()->mlevel;
	int xp = GameData::shareGameData()->mxp;
	int totalxp = getExp(1.1, level);
	if (xp >= totalxp)
	{
		mxp -= totalxp;
		xp -= totalxp;
		level++;
		mlevel++;
	}

	__String *lelstr = __String::createWithFormat("%d", level);
	levellabel->setString(lelstr->getCString());
	healthBar->setPercentage(((float)xp / (float)totalxp) * 100);

	__String *exp = __String::createWithFormat("%d/%d", xp, totalxp);
	xpLabel->setString(exp->getCString());
	int money = GameData::shareGameData()->mMoney;
	__String *strMoney = __String::createWithFormat("%d", money);
	moneyLabel->setString(strMoney->getCString());

	int coin = GameData::shareGameData()->mCoin;
	__String *strCoin = __String::createWithFormat("%d", coin);
	coinLabel->setString(strCoin->getCString());
}

void HomeLayer::menuCallback(Ref *sender)
{
	auto btn = (ui::Button*)sender;
	int tag = btn->getTag();
	HeroType hero;
	if (tag == 11)
	{
		ZhuangBeiType zhuang;
		EquimentLayer *zhuangbei = new EquimentLayer();
		zhuangbei->autorelease();
		zhuangbei->init(hero, -1, zhuang);
		addChild(zhuangbei, 10);
	}
	if (tag == 12)
	{
		/*HeroListLayer *list = new HeroListLayer();
		list->init(hero, -1);
		list->autorelease();
		addChild(list, 10);*/
	}
	if (tag == 13)
	{
		//OnGetMoney();
	}
	else if (tag == 14)
	{
		/*JiangLiLayer *layer = new JiangLiLayer();
		layer->autorelease();
		addChild(layer, 10);*/
	}
}