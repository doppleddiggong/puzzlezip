//
//  Display.cpp
//  puzzlezip
//
//  Created by bae ju baeck on 2014. 11. 21..
//
//

#include "DefineData.h"
#include "Display.h"

int     ex_nSceneWidth;
int     ex_nSceneHeight;
float   ex_fScale;
float   ex_fPositionSacleX;
float   ex_fPositionSacleY;
int     ex_nSceneWidthOffset;
int     ex_nSceneHeightOffset;

float ex_fNormalFontSize = 24.0f;

// 실제 화면의 X
float getWindowX(float fPosX)
{
    return fPosX;
}

// 실제 화면의 Y
float getWindowY(float fPosY)
{
    return (DEFAULT_DISPLAY_HEIGHT - fPosY);
}

Vec2 centerPos()
{
    return Vec2( getWindowX(DEFAULT_DISPLAY_WIDTH/2), getWindowY(DEFAULT_DISPLAY_HEIGHT/2) );
}

bool isVisibleTouchEnable( Sprite* pSprite )
{
    if( pSprite->isVisible() && pSprite->getOpacity() > 0 )
        return true;
    
    return false;
}

bool isSpriteRectTouched( Sprite* pSprite, Vec2 vecLocation )
{
    Vec2 touchPoint = pSprite->convertToNodeSpace(vecLocation);
    Vec2 pos = pSprite->getPosition();
    Size size = pSprite->getContentSize();
    Rect rect = Rect(pos.x-size.width, pos.y-size.height, size.width, size.height);
    rect.origin = Vec2::ZERO;
    
    return rect.containsPoint(touchPoint);
}

Sprite* createSprite( Node* pNode, const char* strFilePath, Vec2 posPt )
{
    Sprite* pSprite = Sprite::create(strFilePath);
    pSprite->setPosition(posPt);
    pNode->addChild(pSprite);
    
    return pSprite;
}

Label* createLabel( Node* pNode, float fFontSize, Vec2 posPt )
{
    Label* pLabel = Label::createWithTTF("", FONT_PATH, fFontSize );
    pLabel->setPosition( posPt );
    pNode->addChild(pLabel);
    
    return pLabel;
}

Vec2 getPosByPosIndex( int nPosIndex )
{
    int nWidth = DEFAULT_DISPLAY_WIDTH/CELL_SIZE;
    int nPosX = (nPosIndex % nWidth)*CELL_SIZE;
    int nPosY = (nPosIndex / nWidth)*CELL_SIZE;
    
    return Vec2( getWindowX(nPosX), getWindowY(nPosY));
}
