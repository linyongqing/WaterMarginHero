#ifndef _APP_CONFIG_H__
#define _APP_CONFIG_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameData.h"

USING_NS_CC;
USING_NS_CC_EXT;

extern cocos2d::__Array *play_bullet;
extern cocos2d::__Array *enemy_bullet;
extern cocos2d::__Array *enemy_items;
extern cocos2d::__Array *add_Sprites;

typedef struct Enemies
{
	std::string showType;
	int showTime;
	int types[3];
	Enemies()
	{
		showType = "Repeate";
		showTime = 0;
		types[0] = 0;
		types[1] = 0;
		types[2] = 0;

	}
}EnemyInfo;

class Config : public Ref
{
private:
	map<int, EnemyType> m_enemyTypes;
	map<int, HeroType>m_HeroTypes;

	map<int, ZhuangBeiType>m_ZhuangTypes;
	int m_scoreValue;
	int m_life;
	bool m_isAudioOn;
	int m_money;
	Config();
public:
	~Config();
	static Config* sharedConfig();
	map<int, EnemyType> getEnemyType();
	map<int, HeroType> getHerosType();
	map<int, ZhuangBeiType> getZhuangBei();

	int getLifeCount();
	void setMoney(int money);
	int getMoney();
	//bool getAudioState();
	void setTypeCount(int type);
	//void updateAudioState(bool isOn);
	int getScoreValue();
	void updateLifeCount();
	void setScoreValue(int score);
	void resetConfig();
	void ReadZhuangBei();
	void ReadEnemy();
	void ReadHero();
};

#endif // !_APP_CONFIG_H__
