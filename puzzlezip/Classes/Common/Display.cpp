//
//  Display.cpp
//  puzzlezip
//
//  Created by bae ju baeck on 2014. 11. 21..
//
//

#include "Display.h"

float ex_fScale;
float ex_fPositionSacleX;
float ex_fPositionSacleY;

float ex_fNormalFontSize = 24.0f;

// 실제 화면의 X
float getWindowX(float fPosX)
{
    float fReturnPosX = fPosX * ex_fPositionSacleX;
    return fReturnPosX;
}

// 실제 화면의 Y
float getWindowY(float fPosY)
{
    float fReturnPosY = fPosY * ex_fPositionSacleY;
    return fReturnPosY;
}

Vec2 centerPos()
{
    return Vec2( DEFAULT_DISPLAY_WIDTH/2, DEFAULT_DISPLAY_HEIGHT/2 );
}

// todo. 예외처리
Sprite* createSprite( Node* pNode, const char* strFilePath, Vec2 posPt )
{
    Sprite* pSprite = Sprite::create(strFilePath);
    pSprite->setPosition(posPt);
    pNode->addChild(pSprite);
    
    return pSprite;
}

// todo. 예외처리
Label* createLabel( Node* pNode, float fFontSize, Vec2 posPt )
{
    Label* pLabel = Label::createWithTTF("", FONT_PATH, fFontSize );
    pLabel->setPosition( posPt );
    pNode->addChild(pLabel);
    
    return pLabel;
}