#ifndef _APP_GAMESCENE_H__
#define _APP_GAMESCENE_H__

#include "cocos2d.h"
#include "HomeLayer.h"

USING_NS_CC;

#define HOMEGAG   101

class GameScene : public Scene
{
public:
	GameScene(int level);
	bool init(int level);
	~GameScene();

private:
	HomeLayer *mHudLayer;
	//GroupLayer *mGroupLayer;
	//HeroLayer *mHeroLayer;
	//GameMapLayer *mGameMapLayer;
	//TujianLayer *mTujianLayer;
	//shopLayer *mShopLayer;
	Sprite *m_map1;
	Sprite *m_map2;
	void broadcastInput(float dt);
	int mLevel;
	int scrollWidth;
	void setMenuVisible(Ref *sender);
	void menuPauseCallback(Ref*sender);
	void getCoin(Ref *sender);
};

#endif // !_APP_GAMESCENE_H__
