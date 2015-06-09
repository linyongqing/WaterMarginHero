#ifndef _APP_GAMEDATA_H__
#define _APP_GAMEDATA_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "document.h"
#include "writer.h"
#include "reader.h"
#include "stringbuffer.h"

#define LEVELXP 300
class Config;

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

typedef struct
{
	int ap;//����
	int type;
	int level;
	int star;
	string textureName;
	string name;
	int index;
}SwordType;

typedef struct
{
	int defender;//����
	int magicdefender;//ħ��
	int type;
	int hp;
	int level;
	int star;
	string textureName;
	string name;
	int index;
}ClothType;

typedef struct
{
	int magicdefender;//ħ��
	int defender;//���
	int type;
	int hp;
	int level;
	int star;
	string textureName;
	string name;
	int index;
}HeadType;

typedef struct
{
	int type;
	int hp;
	int ap;
	int level;
	int star;
	string textureName;
	string name;
	int index;
}HorseType;

typedef struct
{
	int type;
	int defender;
	int level;
	int star;
	string textureName;
	string name;
	int index;
}JieZhiType;

typedef struct
{
	int type;
	int ap;
	int level;
	int star;
	string textureName;
	string name;
	int index;
}BaowuType;

typedef struct
{
	int type;
	int index;
	int level;
	int exlevel;
	int defender;
	int magicdefender;
	int ap;
	int hp;
	int star;
	string name;
	string textureName;
	int user;
	int money;
}ZhuangBeiType;

typedef struct
{
	int type;//����
	string textureName;//ͼƬ
	string name;
	string exname;
	string starname;
	string skillsname;
	int index;
	int pos;//λ��
	int hp;//���Ƶ�Ѫ
	int ap;//���ƹ���
	int totalhp;//�ܵ�Ѫ��
	int totalap;//�ܵĹ���
	int defend;
	int magicdefend;
	int totalmagicdefend;//��ħ��
	int totaldefend;//�ܵķ���
	int attackid;//������ʽ
	int skillsid;//����
	int level;
	int exlevel;//Ʒ��
	int xp;//����
	int card;//��1����2��÷3����4
	int number;//2 j11 Q12 k13 A14 ��14,����15
	int swordid;//����id;
	int baowuid;//����;
	ZhuangBeiType zhuang[6];
	string des;
}HeroType;

typedef struct {
	int type;
	string textureName;
	string name;
	string exname;
	string starname;
	string skillsname;
	int hp;
	int ap;
	int attackid;
	int skillsid;
	int level;
	int card;//��ɫ
	int number;//����
	int magic;
	string des;
	int defend;
	int magicdefend;
}EnemyType;

class GameData{
public:
	GameData();
	~GameData();
	vector<HeroType> m_Heros;
	vector<ZhuangBeiType> m_ZhuangBeis;
	int mlevel;
	int mxp;
	int mMoney;
	int mCoin;
	__Dictionary * dic;
	std::string scoredata;
	int userID;
	int charId;
	int mapId;
	int subMapId;
	int speed;
	std::string  str;
	static GameData * shareGameData();
	__Dictionary * roleDic;
public:
	void readJson();
	void saveHero();
	void saveDefault();
	std::vector<HeroType> getHeros();
	std::vector<ZhuangBeiType> getZhuangbei();

	bool addHero(HeroType hero);
	bool setHero(HeroType hero, HeroType kapai);
	void removeKapai(HeroType hero);
	void updateHero(HeroType hero);

	void QianghuaHero(HeroType kapai, HeroType hero);
	void setHero(HeroType hero);
	bool addKapai(HeroType hero);
	void changeHero(HeroType oldhero, HeroType changehero);
	void changePos();

	bool changeZhuangBei(HeroType herodata, ZhuangBeiType zhuang, int index);
	bool addZhuangBei(ZhuangBeiType zhuang);
	void updateZhuang(ZhuangBeiType zhuang);
	void updateHeros();
	void saveZhuangBei();

	void readZhuangbei();

	bool IsSort(int arr[], int length);
	void setMoney(int money);
	void setCoin(int coin);
	void setData(int money, int xp);
	int getexp(float x, int n);
};

#endif // !_APP_GAMEDATA_H__
