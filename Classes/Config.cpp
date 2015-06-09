#include "Config.h"

__Array *play_bullet;
__Array *enemy_bullet;
__Array *enemy_items;
__Array *add_Sprites;
static  Config *g_config = NULL;

Config::Config() :m_scoreValue(0), m_life(3), m_isAudioOn(false)
{
	ReadEnemy();
	ReadHero();
	ReadZhuangBei();
	m_money = 0;
}

Config::~Config()
{
	play_bullet->release();
	enemy_bullet->release();
	enemy_items->release();
	enemy_items = NULL;
	play_bullet = NULL;
	enemy_bullet = NULL;
	CCLOG("release config");
}

Config *Config::sharedConfig()
{
	if (!g_config) {
		g_config = new Config();
	}
	return g_config;
}

void Config::ReadEnemy()
{
	std::string path = FileUtils::getInstance()->fullPathForFilename("enemy.json");
	Data data = FileUtils::getInstance()->getDataFromFile(path.c_str());

	std::string content = std::string((const char*)data.getBytes(), 0, data.getSize());
	rapidjson::Document document;
	document.Parse<0>(content.c_str());

	const rapidjson::Value &redata = document["data"];

	for (unsigned int i = 0; i < redata.Size(); i++)
	{
		EnemyType enemyType;
		int type = redata[i]["type"].GetInt();
		enemyType.type = type;
		enemyType.name = redata[i]["name"].GetString();
		enemyType.textureName = redata[i]["picture"].GetString();
		enemyType.hp = redata[i]["hp"].GetInt();
		enemyType.ap = redata[i]["ap"].GetInt();
		enemyType.skillsid = redata[i]["skillsid"].GetInt();
		enemyType.attackid = redata[i]["attackid"].GetInt();
		enemyType.defend = redata[i]["defend"].GetInt();
		enemyType.magicdefend = redata[i]["magicdefend"].GetInt();

		m_enemyTypes.insert(map<int, EnemyType>::value_type(type, enemyType));
	}
}

void Config::ReadHero()
{
	std::string path = FileUtils::getInstance()->fullPathForFilename("hero.json");
	Data data = FileUtils::getInstance()->getDataFromFile(path.c_str());

	std::string content = std::string((const char*)data.getBytes(), 0, data.getSize());

	rapidjson::Document document;
	document.Parse<0>(content.c_str());

	rapidjson::Value &redata = document["data"];
	for (unsigned int i = 0; i < redata.Size(); i++)
	{
		HeroType heroType;
		HeroType enemyType;
		int type = redata[i]["type"].GetInt();
		enemyType.type = type;
		enemyType.name = redata[i]["name"].GetString();
		enemyType.exname = redata[i]["exname"].GetString();
		enemyType.starname = redata[i]["starname"].GetString();
		enemyType.textureName = redata[i]["picture"].GetString();
		enemyType.skillsname = redata[i]["skillsname"].GetString();
		enemyType.defend = 0;
		enemyType.magicdefend = 0;
		enemyType.hp = redata[i]["hp"].GetInt();
		enemyType.ap = redata[i]["ap"].GetInt();
		enemyType.skillsid = redata[i]["skillsid"].GetInt();
		enemyType.attackid = redata[i]["attackid"].GetInt();
		enemyType.des = redata[i]["des"].GetString();
		enemyType.number = redata[i]["number"].GetInt();
		enemyType.card = redata[i]["card"].GetInt();
		//printf("des===%s",enemyType.des.c_str());
		m_HeroTypes.insert(map <int, HeroType>::value_type(type, enemyType));
	}
}

void Config::ReadZhuangBei()
{
	std::string path = FileUtils::getInstance()->fullPathForFilename("cloth.json");
	Data data = FileUtils::getInstance()->getDataFromFile(path.c_str());
	std::string content = std::string((const char*)data.getBytes(), 0, data.getSize());

	rapidjson::Document document;
	document.Parse<0>(content.c_str());

	rapidjson::Value &heads = document["datas"];

	for (unsigned int i = 0; i < heads.Size(); i++)
	{
		ZhuangBeiType headType;
		int type = heads[i]["type"].GetInt();
		headType.type = type;
		headType.name = heads[i]["name"].GetString();
		headType.textureName = heads[i]["picture"].GetString();
		headType.defender = heads[i]["defend"].GetInt();
		headType.magicdefender = heads[i]["magic"].GetInt();
		headType.star = heads[i]["star"].GetInt();
		headType.hp = heads[i]["hp"].GetInt();
		headType.ap = heads[i]["ap"].GetInt();

		m_ZhuangTypes.insert(map<int, ZhuangBeiType>::value_type(type, headType));
	}
}

map<int, EnemyType> Config::getEnemyType()
{
	return m_enemyTypes;
}

map<int, HeroType> Config::getHerosType()
{
	return m_HeroTypes;
}

map<int, ZhuangBeiType> Config::getZhuangBei()
{
	return m_ZhuangTypes;
}

int Config::getScoreValue()
{
	return m_scoreValue;
}

void Config::setScoreValue(int score)
{
	m_scoreValue += score;
}

void Config::setMoney(int money)
{
	m_money += money;
}

int Config::getMoney()
{
	return m_money;
}

int Config::getLifeCount()
{
	return m_life;
}

void Config::updateLifeCount()
{
	m_life--;
}

void Config::resetConfig()
{
	m_scoreValue = 0;
	m_life = 3;
}