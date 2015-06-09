#include "GameScene.h"

GameScene::GameScene(int level)
{
	init(level);

	mHudLayer = new HomeLayer();
	mHudLayer->setPosition(ccp(0, 0));
	mHudLayer->autorelease();
	this->addChild(mHudLayer, 1, HOMEGAG);
}

bool GameScene::init(int level)
{
	auto size = Director::getInstance()->getWinSize();
	auto bg = Sprite::create("homebg.png");
	bg->setPosition(Vec2(size.width / 2, size.height / 2));
	bg->setScaleX(size.width / 640);
	bg->setScaleY(size.height / 960);
	this->addChild(bg);

	auto tile = Sprite::create("tile.png");
	tile->setPosition(Vec2(size.width / 2, size.height - 80 - tile->getContentSize().height / 2));
	this->addChild(tile);

	auto item1 = MenuItemImage::create("home1.png", "home2.png");
	auto item2 = MenuItemImage::create("group1.png", "group2.png");
	auto item3 = MenuItemImage::create("hero1.png", "hero2.png");
	auto item4 = MenuItemImage::create("war1.png", "war2.png");
	auto item5 = MenuItemImage::create("tujian1.png", "tujian2.png");
	auto item6 = MenuItemImage::create("store1.png", "store2.png");

	item1->setTag(1);
	item2->setTag(2);
	item3->setTag(3);
	item4->setTag(4);
	item5->setTag(5);
	item6->setTag(6);

	auto menu = Menu::create(item1, item2, item3, item4, item5, item6, NULL);
	menu->alignItemsHorizontally();
	menu->setPosition(ccp(size.width / 2, item1->getContentSize().height / 2));
	menu->setTag(888);
	this->addChild(menu, 1000);
	return true;
}

GameScene::~GameScene(){}

