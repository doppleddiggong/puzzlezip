//
//  CustomMath.cpp
//  puzzlezip
//
//  Created by bae ju baeck on 2015. 1. 5..
//
//

#include "CustomMath.h"
#include <math.h>

int getPtDistance( Vec2 pt1, Vec2 pt2 )
{
    return getPtDistance(pt1.x, pt1.y, pt2.x, pt2.y);
}

int getPtDistance( float ptx, float pty, float pt2x, float pt2y )
{
    return sqrt( std::fabsf((ptx - pt2x))*std::fabsf((ptx - pt2x)) + std::fabsf((pty - pt2y))*std::fabsf((pty - pt2y)) );
}

