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

extern float ex_fNormalFontSize;

extern int ex_nSceneWidth;
extern int ex_nSceneHeight;
extern float ex_fScale;
extern float ex_fPositionSacleX;
extern float ex_fPositionSacleY;
extern int ex_nSceneWidthOffset;
extern int ex_nSceneHeightOffset;

float getWindowX(float fPosX);
float getWindowY(float fPosY);
Vec2  centerPos();

bool isVisibleTouchEnable( Sprite* pSprite );
bool isSpriteRectTouched( Sprite* pSprite, Vec2 vecLocation );

Sprite* createSprite( Node* pNode, const char* strFilePath, Vec2 posPt );
Label* createLabel( Node* pNode, float fFontSize, Vec2 posPt );

Vec2 getPosByPosIndex( int nPosIndex );

#endif /* defined(__puzzlezip__Display__) */
