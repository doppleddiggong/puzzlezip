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

CellLayer* CellLayer::create( int nType, int nPosIndex )
{
    CellLayer* pRet = new CellLayer();
    if (pRet && pRet->init( nType, nPosIndex ) )
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


bool CellLayer::init( int nType, int nPosIndex )
{
    bool bRet = Node::init();
    
    if( bRet )
    {
        m_nPosIndex = nPosIndex;

        m_pCell = createSprite( this, "Game/common_slot_lock.png", getPosByPosIndex( nPosIndex ) );
        m_pCell->setAnchorPoint(Vec2(0, 1));

        // 이미지의 크기를 정의한 값으로 만들어준다
        m_pCell->setScale( CELL_SIZE/m_pCell->getContentSize().width);
        this->refreshCellType( nType );
        
    }
    return bRet;
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