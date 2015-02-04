//
//  CellLayer.h
//  puzzlezip
//
//  Created by bae ju baeck on 2014. 12. 19..
//
//

#ifndef __puzzlezip__CellLayer__
#define __puzzlezip__CellLayer__

#include "../../HeaderList.h"

class CellLayer : public Layer
{
public:
    enum
    {
        SHAKE_TYPE_WIDTH    = 0,
        SHAKE_TYPE_HEIGHT   = 1,
    };


public:
    CellLayer();
    virtual ~CellLayer();
    static CellLayer* create( int nType, int nPosIndex, bool bTouchEnable = false );
    
    void (CellLayer::*pFunc)(int index);
    typedef void (CellLayer::*Func)(int);
    typedef std::map<cocos2d::Sprite*, Func> MAP_FUNC_LIST;
    
    MAP_FUNC_LIST           m_touchMap;
    MAP_FUNC_LIST::iterator m_Iterator;
    
    bool init( int nType, int nPosIndex, bool bTouchEnable );
    void initTouchEvent();
    
    void refreshCellType( int nType );

    void startCharacterAnimation();
    void startShakeAnimation( int nShakeType );
    void endAnimation();
    
    int getCellType() { return m_nType; }


    void cellTouched( int nTag );
    
    bool onTouchBegan( Touch* pTouch, Event* pEvent );
    void onTouchMoved( Touch* pTouch, Event* pEvent );
    void onTouchEnded( Touch* pTouch, Event* pEvent );
    
private:
    bool    m_bIsPressed;
    bool    m_bTouchMoved;
    
    Vec2    m_pTouchBegan;
    
    int     m_nType;
    int     m_nPosIndex;
    bool    m_bAnimationIng;
    
    Sprite* m_pCell;
    Label*  m_pPosIdxLabel;
};


#endif
