//
//  BaseLayer.h
//  puzzlezip
//
//  Created by bae ju baeck on 2015. 1. 5..
//
//

#ifndef __puzzlezip__BaseLayer__
#define __puzzlezip__BaseLayer__

#include "cocos2d.h"
USING_NS_CC;

class BaseScene : public cocos2d::Layer
{
protected:
    Sprite*	m_pBg;

    virtual void initTouchEvent(){};
    virtual void initLoadData(){};
    virtual void initBg(){};
    
public:
    int     m_nTouchTag;
    Vec2    m_pTouchBegan;
    bool    m_bTouchMoved;
    Vec2    m_pTouchEnded;

public:
    BaseScene();
    virtual ~BaseScene();
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(BaseScene);
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    
    void onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event );
};

#endif /* defined(__puzzlezip__BaseLayer__) */
