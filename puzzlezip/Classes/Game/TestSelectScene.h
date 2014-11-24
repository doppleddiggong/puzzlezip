#ifndef __TestSelectScene_SCENE_H__
#define __TestSelectScene_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

#include "../HeaderList.h"

USING_NS_CC;
USING_NS_CC_EXT;

class TestSelectScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(TestSelectScene);

private:
	Label*	m_pTitleLabel;
	Sprite*	m_pBg;
    
    void initLoadData();

    void initBg();
    void initCCS();
};

#endif // __TestSelectScene_SCENE_H__
