#include "EquipmentLayer.h"
#include "ui\UIScrollView.h"

bool EquimentLayer::init(HeroType hero, int type, ZhuangBeiType zhuang)
{
	if (!Layer::init())
		return false;

	m_hero = hero;
	m_type = type;
	m_zhuangtype = zhuang;
	setData(hero, type, zhuang);
	return true;
}

void EquimentLayer::setData(HeroType hero, int type, ZhuangBeiType zhuangtype)
{
	auto m_pUILayer = Layer::create();
	this->addChild(m_pUILayer, 0);
	auto winSize = Director::getInstance()->getWinSize();

	this->setTouchEnabled(true);
	auto imageBg = ui::ImageView::create("herobg.png");
	imageBg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	m_pUILayer->addChild(imageBg);

	auto scrollView = ui::ScrollView::create();
	scrollView->setTouchEnabled(true);
	scrollView->setBounceEnabled(true);

	scrollView->setPosition(Vec2(0, winSize.height / 2 - 360));
	m_pUILayer->addChild(scrollView, 10);

	vector<ZhuangBeiType> zhuangBeis = GameData::shareGameData()->getZhuangbei();
	int j = 0;
	int index = zhuangBeis.size();
	std::string index1 = "" + index;
	for (int i = 0; i < zhuangBeis.size(); i++)
	{
		ZhuangBeiType zhuang = zhuangBeis[i];
		int t = (type + 3) * 100;

		if ((zhuang.type >= t && zhuang.type < (t + 100)) || type == -1)
		{
			j++;
			auto *imageView = ui::ImageView::create("cellbg.png");
			int imageHeight = imageView->getContentSize().height;
			float innerWidth = scrollView->getContentSize().width;
			float innerHeight = scrollView->getContentSize().height + imageHeight*zhuangBeis.size();
			scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));

			imageView->setPosition(Vec2(innerWidth / 2, scrollView->getInnerContainerSize().height - imageHeight*j + imageHeight / 2));
			scrollView->addChild(imageView);

			auto *imagebg = ui::ImageView::create("addbutton.png");
			imagebg->setPosition(Vec2(120, scrollView->getInnerContainerSize().height - imageHeight*j + imageHeight / 2));
			scrollView->addChild(imagebg);

			auto *imageHead = ui::ImageView::create(zhuang.textureName.c_str());
			imageHead->setPosition(Vec2(120, scrollView->getInnerContainerSize().height - imageHeight*j + imageHeight / 2));
			scrollView->addChild(imageHead);

			auto *label = Label::create();
			char strlevel[32];
			sprintf(strlevel, "Lv:%d", zhuang.level);
			label->setSystemFontSize(24);
			label->setString(strlevel);
			label->setColor(Color3B::BLUE);
			label->setPosition(Vec2(winSize.width / 2 - 100, scrollView->getInnerContainerSize().height - imageHeight*j + imageHeight - 60));
			scrollView->addChild(label);

			auto *namelabel = Label::create();
			namelabel->setSystemFontSize(24);
			namelabel->setString(zhuang.name.c_str());
			namelabel->setColor(Color3B::BLUE);
			namelabel->setPosition(Vec2(winSize.width / 2, scrollView->getInnerContainerSize().height - imageHeight*j + imageHeight - 60));
			scrollView->addChild(namelabel);

			if (zhuang.hp > 0)
			{
				auto *imageattack = ui::ImageView::create("heart.png");
				imageattack->setPosition(Vec2(winSize.width / 2 - 100, scrollView->getInnerContainerSize().height - imageHeight*j + imageHeight / 3));
				scrollView->addChild(imageattack);
				auto *label = Label::create();
				label->setPosition(Vec2(winSize.width / 2 - 40, scrollView->getInnerContainerSize().height - imageHeight*j + imageHeight / 3));
				scrollView->addChild(label);
				char str[32];
				int hp = zhuang.hp + (40 + 10 * zhuang.star)*zhuang.level;
				sprintf(str, "%d", hp);
				label->setSystemFontSize(24);
				label->setColor(Color3B::BLACK);
				label->setString(str);
			}
			if (zhuang.ap > 0)
			{
				auto *imageattack = ui::ImageView::create("swordicon.png");
				imageattack->setPosition(Vec2(winSize.width / 2 + 40, scrollView->getInnerContainerSize().height - imageHeight*j + imageHeight / 3));
				scrollView->addChild(imageattack);
				auto *label = Label::create();
				label->setPosition(Vec2(winSize.width / 2 + 100, scrollView->getInnerContainerSize().height - imageHeight*j + imageHeight / 3));
				scrollView->addChild(label);
				char str[32];
				int ap = zhuang.ap + (10 + 2 * zhuang.star)*zhuang.level;
				sprintf(str, "%d", ap);
				label->setColor(Color3B::BLACK);
				label->setSystemFontSize(24);
				label->setString(str);

			}

			if (zhuang.defender > 0)
			{
				auto *imageattack = ui::ImageView::create("fang.png");
				imageattack->setPosition(ccp(winSize.width / 2 - 100, scrollView->getInnerContainerSize().height - imageHeight*j + imageHeight / 3));
				scrollView->addChild(imageattack);
				auto *label = Label::create();
				label->setPosition(Vec2(winSize.width / 2 - 40, scrollView->getInnerContainerSize().height - imageHeight*j + imageHeight / 3));
				scrollView->addChild(label);
				char str[32];
				int defender = zhuang.defender + (6 + 1 * zhuang.star)*zhuang.level;
				sprintf(str, "%d", defender);
				label->setColor(Color3B::BLACK);
				label->setSystemFontSize(24);
				label->setString(str);
			}
			if (zhuang.magicdefender > 0)
			{
				auto *imageattack = ui::ImageView::create("mofang.png");
				imageattack->setPosition(Vec2(winSize.width / 2 + 40, scrollView->getInnerContainerSize().height - imageHeight*j + imageHeight / 3));
				scrollView->addChild(imageattack);
				auto *label = Label::create();
				label->setPosition(Vec2(winSize.width / 2 + 100, scrollView->getInnerContainerSize().height - imageHeight*j + imageHeight / 3));
				scrollView->addChild(label);
				char str[32];
				int magicdefender = zhuang.magicdefender + (6 + 1 * zhuang.star)*zhuang.level;
				sprintf(str, "%d", magicdefender);
				label->setSystemFontSize(24);
				label->setColor(Color3B::BLACK);
				label->setString(str);
			}
			for (int i = 0; i < zhuang.star; i++)
			{
				auto* imageattack = ui::ImageView::create("star.png");
				imageattack->setPosition(Vec2(winSize.width / 2 + i * 20 + 100, scrollView->getInnerContainerSize().height - imageHeight*j + imageHeight - 60));
				scrollView->addChild(imageattack);
			}

			auto* button = ui::Button::create();
			button->setEnabled(true);
			button->setTag(zhuang.index);
			if (type == -1)
			{
				button->loadTextures("heroup1.png", "heroup2.png", "");
				button->addClickEventListener(CC_CALLBACK_1(EquimentLayer::Shengji, this));
			}
			else
			{
				button->loadTextures("zhuangbei1.png", "zhuangbei2.png", "");
				button->addClickEventListener(CC_CALLBACK_1(EquimentLayer::menuPauseCallback, this));
			}

			button->setPosition(Vec2(winSize.width - 120, scrollView->getInnerContainerSize().height - imageHeight*j + imageHeight / 3));
			scrollView->addChild(button);
		}
	}
	auto btn = ui::Button::create("close1.png", "close2.png", "close2.png");
	btn->setEnabled(true);
	btn->addClickEventListener(CC_CALLBACK_1(EquimentLayer::close, this));
	btn->setPosition(Vec2(winSize.width - 60, winSize.height / 2 + 300));
	m_pUILayer->addChild(btn);
}

void EquimentLayer::Shengji(Ref *sender)
{

}

void EquimentLayer::menuPauseCallback(Ref *sender)
{

}

void EquimentLayer::close(Ref *sender)
{

}