#ifndef __TestSelectScene_SCENE_H__
#define __TestSelectScene_SCENE_H__

#include "../HeaderList.h"

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
