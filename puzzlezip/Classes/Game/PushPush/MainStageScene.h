//
//  MainStageScene.h
//  puzzlezip
//
//  Created by bae ju baeck on 2014. 12. 19..
//
//

#ifndef __puzzlezip__MainStageScene__
#define __puzzlezip__MainStageScene__

#include "../../HeaderList.h"

class MainStageScene : public BaseScene
{
public:
    MainStageScene();
    virtual ~MainStageScene();
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainStageScene);
    
    void bgTouched( int nTag );

    void buttonTouchBegan( int nTag );
    void buttonTouchEnded( int nTag );
    
    bool onTouchBegan(Touch* pTouch, Event* pEvent);
    void onTouchMoved(Touch* pTouch, Event* pEvent);
    void onTouchEnded(Touch* pTouch, Event* pEvent);

private:
    Label* m_pTitleLabel;
    
    void initLoadData();
    void initTouchEvent();

    void initBg();
    void initCellLayer();
    void initArrow();
    
    void (MainStageScene::*pFunc)(int index);
    typedef void (MainStageScene::*Func)(int);
    typedef std::map<cocos2d::Sprite*, Func> MAP_FUNC_LIST;
    
    MAP_FUNC_LIST           m_touchMap;
    MAP_FUNC_LIST::iterator m_Iterator;
};

#endif /* defined(__puzzlezip__MainStageScene__) */
