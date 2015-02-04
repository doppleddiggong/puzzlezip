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

#define ARROW_MAX_NUM  4

class CellLayer;
class MainStageScene : public BaseScene
{
public:
    MainStageScene();
    virtual ~MainStageScene();
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainStageScene);
    
    void (MainStageScene::*pFunc)(int index);
    typedef void (MainStageScene::*Func)(int);
    typedef std::map<cocos2d::Sprite*, Func> MAP_FUNC_LIST;
    
    MAP_FUNC_LIST           m_touchMap;
    MAP_FUNC_LIST::iterator m_Iterator;

    void arrowTouched( int nTag );
    
    void buttonTouchBegan( int nTag );
    void buttonTouchEnded( int nTag );    
    bool onTouchBegan( Touch* pTouch, Event* pEvent );
    void onTouchMoved( Touch* pTouch, Event* pEvent );
    void onTouchEnded( Touch* pTouch, Event* pEvent );

private:
    enum
    {
        TOUCH_TAG_ARROW_LEFT    = 0,
        TOUCH_TAG_ARROW_RIGHT   = 1,
        TOUCH_TAG_ARROW_UP      = 2,
        TOUCH_TAG_ARROW_DOWN    = 3,
    };
    
    int         m_nCellCnt;
    int         m_nCellWidth;
    int         m_nCellHeight;
    
    ValueMap    m_valueMap;
    
    Label*      m_pTitleLabel;

    Sprite*     m_pArrowButton[ARROW_MAX_NUM][BUTTON_MAX_NUM];
    std::vector<CellLayer*>     m_vecCellLayer;
    
    void loadStageData( int nStage );

    void initLoadData();
    void initTouchEvent();
    void initBg();
    void initCellLayer();
    void initArrowButton();
    
    void refreshCell();

    bool isMapOut( int nTag, int nTargetIndex );
    int  getCharacterPosIndex();
    void cellDataMove( int nCurPosIdx, int nNextPosIdx );
    // nCurPosIdx 에 있는 물체가 nTag 방향으로 이동하려고 하는데 이동이 가능한가?
    int  isBallMoveEnable( int nTag, int nCurPosIdx );
    int  getMoveShakeType( int nTag );
    int  getNextPosIdx( int nTag, int nCurPosIdx );
};

#endif /* defined(__puzzlezip__MainStageScene__) */
