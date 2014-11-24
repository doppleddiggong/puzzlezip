#include "HeaderList.h"
#include "AppDelegate.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
	Director* pDirector = Director::getInstance();
	GLView*   pGlview = pDirector->getOpenGLView();

    this->initDisplayValue();
    
	if ( pGlview == NULL)
	{
		Rect rect = Rect(0, 0, DEFAULT_DISPLAY_WIDTH, DEFAULT_DISPLAY_HEIGHT);
		float frameZoomFactor = 1.0f;

		pGlview = GLViewImpl::createWithRect("puzzleZIP", rect, frameZoomFactor);
		pDirector->setOpenGLView(pGlview);
	}
    
    pGlview->setDesignResolutionSize(DEFAULT_DISPLAY_WIDTH, DEFAULT_DISPLAY_HEIGHT, ResolutionPolicy::SHOW_ALL );

	pDirector->setDisplayStats(false);
	pDirector->setAnimationInterval(1.0 / 60);

	auto pScene = TestSelectScene::createScene();
	pDirector->runWithScene(pScene);

    return true;
}

void AppDelegate::initDisplayValue()
{
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    CCLOG("size.width : %3.1f. size.height : %3.1f", size.width, size.height);
    CCLOG("origin.x : %3.1f. origin.y : %3.1f", origin.x, origin.y);
}

void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
}
