//
//  CharacterLayer.cpp
//  puzzlezip
//
//  Created by bae ju baeck on 2014. 12. 19..
//
//

#include "CharacterLayer.h"

CharacterLayer::CharacterLayer()
{}

CharacterLayer::~CharacterLayer()
{}

CharacterLayer* CharacterLayer::create( int nPosIndex )
{
    CharacterLayer* pRet = new CharacterLayer();
    if (pRet && pRet->init( nPosIndex ) )
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

bool CharacterLayer::init( int nPosIndex )
{
    bool bRet = Node::init();
    
    if( bRet )
    {
        m_nPosIndex = nPosIndex;
        
        m_pCharacterCell = createSprite( this, "Game/Icon-180.png", getPosByPosIndex( nPosIndex ) );
        m_pCharacterCell->setAnchorPoint(Vec2(0, 1));
        
        // 이미지의 크기를 정의한 값으로 만들어준다
        m_pCharacterCell->setScale( CELL_SIZE/m_pCharacterCell->getContentSize().width);
    }
    return bRet;
}