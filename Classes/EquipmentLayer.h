#ifndef _APP_EQUIPMENTLAYER_H__
#define _APP_EQUIPMENTLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameData.h"
#include "ui\UIImageView.h"

USING_NS_CC;
USING_NS_CC_EXT;

class EquimentLayer : public Layer
{
public:
	bool init(HeroType hero, int type, ZhuangBeiType zhuang);
	void Zhuangupdate();
	ZhuangBeiType m_zhuangtype;
public:
	HeroType m_hero;
	int m_type;
	void setData(HeroType hero, int type, ZhuangBeiType zhuangtype);
	void menuPauseCallback(Ref *sender);
	void Shengji(Ref *sender);
	void close(Ref *sender);
	int getExp(int ap, float x, int n);
};
#endif // !_APP_EQUIPMENTLAYER_H__
