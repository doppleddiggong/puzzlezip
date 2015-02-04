//
//  CreateStageScene.h
//  puzzlezip
//
//  Created by bae ju baeck on 2015. 2. 2..
//
//

#ifndef __puzzlezip__CreateStageScene__
#define __puzzlezip__CreateStageScene__

#include "../../HeaderList.h"

class CellLayer;
class CreateStageScene : public BaseScene
{
public:
    CreateStageScene();
    virtual ~CreateStageScene();
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(CreateStageScene);
    
    void (CreateStageScene::*pFunc)(int index);
    typedef void (CreateStageScene::*Func)(int);
    typedef std::map<cocos2d::Sprite*, Func> MAP_FUNC_LIST;
    
    MAP_FUNC_LIST           m_touchMap;
    MAP_FUNC_LIST::iterator m_Iterator;
    
    void buttonSetTouched( int nTag );
    void buttonTouchBegan( int nTag );
    void buttonTouchEnded( int nTag );
    bool onTouchBegan( Touch* pTouch, Event* pEvent );
    void onTouchMoved( Touch* pTouch, Event* pEvent );
    void onTouchEnded( Touch* pTouch, Event* pEvent );
    
private:
    ValueMap    m_valueMap;
    
    Label*      m_pTitleLabel;
    
    std::vector<CellLayer*>     m_vecCellLayer;
    
    Sprite*     m_pButtonSetButton[BUTTON_MAX_NUM];
    
    void initLoadData();
    void initTouchEvent();
    void initBg();
    void initCellLayer();
    
    void initButtonSet();
};

#endif
