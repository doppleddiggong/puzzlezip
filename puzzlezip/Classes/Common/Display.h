//
//  Display.h
//  puzzlezip
//
//  Created by bae ju baeck on 2014. 11. 21..
//
//

#include "cocos2d.h"

USING_NS_CC;

#ifndef __puzzlezip__Display__
#define __puzzlezip__Display__

//기준 해상도
#define DEFAULT_DISPLAY_WIDTH   800
#define DEFAULT_DISPLAY_HEIGHT  480

#define FONT_PATH "fonts/Marker Felt.ttf"
extern float ex_fNormalFontSize;

extern float ex_fScale;
extern float ex_fPositionSacleX;
extern float ex_fPositionSacleY;

float getWindowX(float fPosX);
float getWindowY(float fPosY);
Vec2  centerPos();

Sprite* createSprite( Node* pNode, const char* strFilePath, Vec2 posPt );
Label* createLabel( Node* pNode, float fFontSize, Vec2 posPt );

#endif /* defined(__puzzlezip__Display__) */
