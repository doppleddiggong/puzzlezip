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

	if (pGlview == NULL)
	{
		Rect rect = Rect(0, 0, ex_fDisplayWidth, ex_fDisplayHeight);
		float frameZoomFactor = 1.0f;

		pGlview = GLViewImpl::createWithRect("puzzleZIP", rect, frameZoomFactor);
		pDirector->setOpenGLView(pGlview);
	}

	pDirector->setDisplayStats(false);
	pDirector->setAnimationInterval(1.0 / 60);



	auto pScene = TestSelectScene::createScene();
	pDirector->runWithScene(pScene);

    return true;
}

void AppDelegate::initApplicationView()
{

}


void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
}
