//
//  CustomMath.cpp
//  puzzlezip
//
//  Created by bae ju baeck on 2015. 1. 5..
//
//

#include "CustomMath.h"

int getPtDistance( Vec2 pt1, Vec2 pt2 )
{
    return getPtDistance(pt1.x, pt1.y, pt2.x, pt2.y);
}

int getPtDistance( int ptx, int pty, int pt2x, int pt2y )
{
    return sqrt( fabsf((ptx - pt2x))*fabsf((ptx - pt2x)) + fabsf((pty - pt2y))*fabsf((pty - pt2y)) );
}

