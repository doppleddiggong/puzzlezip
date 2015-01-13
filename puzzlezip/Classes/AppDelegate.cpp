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
	GLView* pGlview = pDirector->getOpenGLView();

	if ( pGlview == NULL)
	{
        pGlview = GLViewImpl::create("puzzleZIP");
        pDirector->setOpenGLView(pGlview);
	}
    
    // 기존에 사용하던 멀티해상도 지원에 대한 코드
//    this->initDisplayValue();
    
    pGlview->setDesignResolutionSize(DEFAULT_DISPLAY_WIDTH, DEFAULT_DISPLAY_HEIGHT, ResolutionPolicy::SHOW_ALL );
    
	pDirector->setDisplayStats(false);
	pDirector->setAnimationInterval(1.0 / 60);

	auto pScene = START_SCENE;
	pDirector->runWithScene(pScene);

    return true;
}

void AppDelegate::initDisplayValue()
{
    Size winSize = Director::getInstance()->getWinSize();
    Size winSizePixel = Director::getInstance()->getWinSizeInPixels();
    
    ex_nSceneWidth = winSize.width;
    ex_nSceneHeight = winSize.height;
    
    // 스케일 값
    ex_fScale = (float)ex_nSceneWidth/DEFAULT_DISPLAY_WIDTH;
    
    // 만약 기준 길이가 세로 길이를 넘어 갈 경우 ex_fScale을 세로에 맞추어서 ex_fScale값을 다시 구해준다.
    if((ex_nSceneHeight - (DEFAULT_DISPLAY_HEIGHT * ex_fScale)) < 0)
    {
        ex_fScale = (float)ex_nSceneHeight/DEFAULT_DISPLAY_HEIGHT;
    }
    
    ex_nSceneWidthOffset = (int)( winSizePixel.width - (int)( DEFAULT_DISPLAY_WIDTH * ex_fScale ) ) / 2;
    ex_nSceneHeightOffset = (int)( winSizePixel.height - (int)( DEFAULT_DISPLAY_HEIGHT * ex_fScale ) ) / 2;

    ex_nSceneWidth = winSize.width;
    ex_nSceneHeight = winSize.height;
    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    ex_fScale = 1.0f;
//    ex_nSceneWidthOffset = 0;
//    ex_nSceneHeightOffset = 0;
//#else
//    Size winSizePixel = Director::getInstance()->getWinSizeInPixels();
//
//    // 스케일 값
//    ex_fScale = (float)ex_nSceneWidth/DEFAULT_DISPLAY_WIDTH;
//    
//    // 만약 기준 길이가 세로 길이를 넘어 갈 경우 ex_fScale을 세로에 맞추어서 ex_fScale값을 다시 구해준다.
//    if((ex_nSceneHeight - (DEFAULT_DISPLAY_HEIGHT * ex_fScale)) < 0)
//    {
//        ex_fScale = (float)ex_nSceneHeight/DEFAULT_DISPLAY_HEIGHT;
//    }
//    
//    ex_nSceneWidthOffset = (int)( winSizePixel.width - (int)( DEFAULT_DISPLAY_WIDTH * ex_fScale ) ) / 2;
//    ex_nSceneHeightOffset = (int)( winSizePixel.height - (int)( DEFAULT_DISPLAY_HEIGHT * ex_fScale ) ) / 2;
//#endif
}

void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
}
