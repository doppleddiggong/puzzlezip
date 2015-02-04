//
//  CellLayer.cpp
//  puzzlezip
//
//  Created by bae ju baeck on 2014. 12. 19..
//
//

#include "CellLayer.h"

const char* CELL_IMAGE[] =
{
    "Game/cell_block.png",
    "Game/cell_open.png",
    "Game/cell_character.png",
    "Game/joystick_thumb.png"
};

#define CELL_SHAKE_MOVE_OFFSET 3

CellLayer::CellLayer()
{
    m_bAnimationIng = false;
}

CellLayer::~CellLayer()
{}

CellLayer* CellLayer::create( int nType, int nPosIndex, bool bTouchEnable )
{
    CellLayer* pRet = new CellLayer();
    if (pRet && pRet->init( nType, nPosIndex, bTouchEnable ) )
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool CellLayer::init( int nType, int nPosIndex, bool bTouchEnable )
{
    bool bRet = Node::init();
    
    if( bRet )
    {
        m_nPosIndex = nPosIndex;

        m_pCell = createSprite( this, CELL_IMAGE[0], getPosByPosIndex( nPosIndex ) );
        m_pCell->setAnchorPoint(Vec2(0, 1));
        
        m_pPosIdxLabel = createLabel( this, 20, Vec2( getPosByPosIndex( nPosIndex ).x+CELL_SIZE/2, getPosByPosIndex( nPosIndex ).y-CELL_SIZE/2 ) );
        __String strPosIdx;
        strPosIdx.initWithFormat("%d", nPosIndex );
        m_pPosIdxLabel->setString(strPosIdx.getCString());
        m_pPosIdxLabel->setColor(Color3B::GRAY);

        // 이미지의 크기를 정의한 값으로 만들어준다
        m_pCell->setScale( CELL_SIZE/m_pCell->getContentSize().width);
        this->refreshCellType( nType );
        
        if( bTouchEnable )
        {
            this->initTouchEvent();
        }
    }
    return bRet;
}

void CellLayer::initTouchEvent()
{
    EventListenerTouchOneByOne* pEventListener = EventListenerTouchOneByOne::create();
    pEventListener->onTouchBegan = CC_CALLBACK_2(CellLayer::onTouchBegan, this);
    pEventListener->onTouchMoved = CC_CALLBACK_2(CellLayer::onTouchMoved, this);
    pEventListener->onTouchEnded = CC_CALLBACK_2(CellLayer::onTouchEnded, this);
    pEventListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithFixedPriority(pEventListener, TOUCH_PRIORITY_LAYER );
}

void CellLayer::refreshCellType( int nType )
{
    m_nType = nType;
    m_pCell->setTexture( CELL_IMAGE[m_nType] );

    // 이미지의 크기를 정의한 값으로 만들어준다
    m_pCell->setScale( CELL_SIZE/m_pCell->getContentSize().width);
    
    if( nType == CELL_TYPE_CHARACTER )
    {
        this->startCharacterAnimation();
    }
    else
    {
        m_pCell->stopAllActions();
    }
}

void CellLayer::startCharacterAnimation()
{
    CCLOG("애니메이션이 마땅치 않다.");
}

void CellLayer::startShakeAnimation( int nShakeType )
{
    if( m_bAnimationIng )
        return;
    
    m_pCell->stopAllActions();
    
    ActionInterval* actionMove;
    ActionInterval* actionMoveRev;
    
    m_bAnimationIng = true;
    Vec2 vecPos = m_pCell->getPosition();
    if( nShakeType == SHAKE_TYPE_WIDTH )
    {
        actionMove = MoveTo::create(0.05f, Vec2( vecPos.x + CELL_SHAKE_MOVE_OFFSET, vecPos.y) );
        actionMoveRev = MoveTo::create(0.05f, Vec2( vecPos.x - CELL_SHAKE_MOVE_OFFSET, vecPos.y) );
    }
    else
    {
        actionMove = MoveTo::create(0.05f, Vec2( vecPos.x, vecPos.y + CELL_SHAKE_MOVE_OFFSET) );
        actionMoveRev = MoveTo::create(0.05f, Vec2( vecPos.x, vecPos.y - CELL_SHAKE_MOVE_OFFSET) );
    }
    
    ActionInterval* actionMoveStop   = MoveTo::create(0.05f, Vec2( vecPos.x, vecPos.y) );
    FiniteTimeAction* actionEnd      = CallFunc::create( CC_CALLBACK_0(CellLayer::endAnimation, this));
    m_pCell->runAction( Sequence::create( actionMove, actionMoveRev, actionMoveStop, actionEnd, NULL));
}

void CellLayer::endAnimation()
{
    m_bAnimationIng = false;
}

void CellLayer::cellTouched( int nTag )
{
    CCLOG("CellLayer::cellTouched( %d )", m_nPosIndex );
    
    m_nType++;
    if( m_nType >= CELL_TYPE_MAX_NUM )
    {
        m_nType = CELL_TYPE_WALL;
    }
    
    refreshCellType( m_nType );
}

bool CellLayer::onTouchBegan( Touch* pTouch, Event* pEvent )
{
    Vec2 loc = pTouch->getLocation();
    m_pTouchBegan = loc;
    m_bTouchMoved = false;

    if( isSpriteRectTouched( m_pCell, m_pTouchBegan ))
    {
        m_bIsPressed = true;
        return true;
    }
    
    return false;
}

void CellLayer::onTouchMoved( Touch* pTouch, Event* pEvent )
{
    Vec2 loc = pTouch->getLocation();
    
    if( getPtDistance(m_pTouchBegan, loc ) > TOUCH_MOVED_OFFSET )
    {
        m_bTouchMoved = true;
    }
}

void CellLayer::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    Vec2 loc = pTouch->getLocation();

    if( m_bTouchMoved )
    {
        m_bTouchMoved = false;
        return;
    }
    
    if( m_bIsPressed )
    {
        if( isSpriteRectTouched( m_pCell, m_pTouchBegan ))
        {
            this->cellTouched(-1);
        }
    }
    
    m_bIsPressed = false;
}
