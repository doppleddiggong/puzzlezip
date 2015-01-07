//
//  CellLayer.cpp
//  puzzlezip
//
//  Created by bae ju baeck on 2014. 12. 19..
//
//

#include "CellLayer.h"

CellLayer::CellLayer()
{}

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
        m_nType = nType;
        m_nPosIndex = nPosIndex;

        m_pCell = createSprite( this, "Game/common_slot_lock.png", getPosByPosIndex( nPosIndex ) );
        m_pCell->setAnchorPoint(Vec2(0, 1));

        // 이미지의 크기를 정의한 값으로 만들어준다
        m_pCell->setScale(ex_fScale * CELL_SIZE/m_pCell->getContentSize().width);
        
        if( nType == CELL_TYPE_WALL )
        {
            m_pCell->setVisible(true);
        }
        else
        {
            m_pCell->setVisible(false);
        }
        
    }
    return bRet;
}