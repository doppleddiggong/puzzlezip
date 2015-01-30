//
//  CustomMath.h
//  puzzlezip
//
//  Created by bae ju baeck on 2015. 1. 5..
//
//

#ifndef __puzzlezip__CustomMath__
#define __puzzlezip__CustomMath__

#include "cocos2d.h"

USING_NS_CC;

typedef enum
{
    DIR_NONE, DIR_UP, DIR_RIGHT, DIR_LEFT, DIR_DOWN
} DIRECTION;

int     getPtDistance( Vec2 pt1, Vec2 pt2 );
int     getPtDistance( float ptx, float pty, float pt2x, float pt2y );

int     getAngleDirection( float ptx, float pty, float pt2x, float pt2y );
int     getAngle( float ptx, float pty, float pt2x, float pt2y );
double  getRadian( float ptx, float pty, float pt2x, float pt2y );

bool    isPointInCircle( Vec2 ptPoint, Vec2 ptCircle, float fRadius );
int     getDirDirection( Vec2 pt1, Vec2 pt2, float radius );

#endif /* defined(__puzzlezip__CustomMath__) */
