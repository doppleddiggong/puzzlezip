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

int getAngleDirection( float ptx, float pty, float pt2x, float pt2y )
{
    int nDegree = getAngle(ptx, pty, pt2x, pt2y);

    if( -45 <= nDegree && nDegree < 45 )
    {
        return DIRECTION::DIR_UP;
    }
    else if( 45 <= nDegree && nDegree < 135 )
    {
        return DIRECTION::DIR_RIGHT;
    }
    else if( -135 <= nDegree && nDegree < -45 )
    {
        return DIRECTION::DIR_LEFT;
    }
    else if( -135 <= nDegree && nDegree < -180 )
    {
        return DIRECTION::DIR_DOWN;
    }
    else if( 135 <= nDegree && nDegree < 180 )
    {
        return DIRECTION::DIR_DOWN;
    }
    
    return DIRECTION::DIR_NONE;
}

int getAngle( float ptx, float pty, float pt2x, float pt2y )
{
    float fx = pt2x - ptx;
    float fy = pt2y - pty;
    
    double dRadian = atan2( fx, fy);
    double dDegree = ( dRadian * 180 ) / M_PI;
    
    return (int)dDegree;
}

double getRadian( float ptx, float pty, float pt2x, float pt2y )
{
    float fx = pt2x - ptx;
    float fy = pt2y - pty;
    
    return atan2( fx, fy);
}

bool isPointInCircle( Vec2 ptPoint, Vec2 ptCircle, float fRadius )
{
    float dx = (ptPoint.x - ptCircle.x);
    float dy = (ptPoint.y - ptCircle.y);
    
    return ( fRadius >= sqrt( (dx*dx) + (dy*dy) ) );
}

int getDirDirection( int nDegree )
{
    if( -45 <= nDegree && nDegree < 45 )
    {
        return DIRECTION::DIR_UP;
    }
    else if( 45 <= nDegree && nDegree < 135 )
    {
        return DIRECTION::DIR_RIGHT;
    }
    else if( -135 <= nDegree && nDegree < -45 )
    {
        return DIRECTION::DIR_LEFT;
    }
    else if( -135 <= nDegree && nDegree < -180 )
    {
        return DIRECTION::DIR_DOWN;
    }
    else if( 135 <= nDegree && nDegree < 180 )
    {
        return DIRECTION::DIR_DOWN;
    }
    
    return DIRECTION::DIR_NONE;
}