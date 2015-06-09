#ifndef _APP_HOMELAYER_H__
#define _APP_HOMELAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class HomeLayer : public Layer
{
public:
	HomeLayer();
	~HomeLayer();
	virtual bool init();
	bool isBeingUsed;
	MenuItemImage *item1;
	MenuItemImage *item2;
	MenuItemImage *item3;
	MenuItemImage *item4;
	void updateControl();
	void update(float dt);
	ProgressTimer *healthBar;
	void healthBarLogic(Ref *sender);
	LabelTTF *barLabel;
	LabelTTF *xpLabel;
	LabelTTF *moneyLabel;
	LabelTTF *coinLabel;
	void menuPauseCallback(Ref *sender);
	void menuCallback(Ref *sender);
	int getExp(float x, float n);
	int mlevel;
	int mxp;

private:
	virtual void onExit();
	int coinNum;
	int diamondsNum;
	LabelTTF *_coins;
	LabelTTF *_zuanshi;
	Label *levellabel;
	void updateCoin();
	void OnGetMoney();
};

#endif // !_APP_HOMELAYER_H__
