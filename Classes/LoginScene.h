#ifndef __APP_LOGINSCENE_H__
#define __APP_LOGINSCENE_H__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "document.h"
#include "writer.h"
#include "reader.h"
#include "stringbuffer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LoginScene : public Layer
{
public:
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(LoginScene);
private:
	void readJson();
	void showNextMsg();
	void saveZhuangBei();
	void saveKaPai();
	int m_iCurMsgIndex;

	std::string content;  //JSONÎÄ¼þÄÚÈÝ
	cocos2d::ValueMap row;
	cocos2d::ValueVector list;
};

#endif // !__APP_LOGINSCENE_H__
