#include "AppDelegate.h"
#include "LoginScene.h"
#include "GameScene.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		#ifdef WIN32
			glview = GLViewImpl::createWithRect("My Game", Rect(0, 0, 640, 960));
		#else
		glview = GLView::create("My Game");
		#endif // WIN32         
		director->setOpenGLView(glview);
    }
	glview->setFrameSize(480, 720);
	Size sceneSize = glview->getFrameSize();
	float x = sceneSize.height / sceneSize.width;
	Size densignSize = CCSizeMake(640, 640 * x);
	glview->setDesignResolutionSize(densignSize.width, densignSize.height, ResolutionPolicy::SHOW_ALL);	
	// turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	//是否第一次进入游戏
	bool bfirst = UserDefault::getInstance()->getBoolForKey("first", false);
	if (!bfirst)
	{
		UserDefault::getInstance()->setBoolForKey("first", true);
		UserDefault::getInstance()->flush();
		auto scene = LoginScene::createScene();
		director->runWithScene(scene);
	}
	else
	{
		CCScene *pScene = new GameScene(0);
		director->runWithScene(pScene);
	}

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
