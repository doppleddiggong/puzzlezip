//
//  CellLayer.h
//  puzzlezip
//
//  Created by bae ju baeck on 2014. 12. 19..
//
//

#ifndef __puzzlezip__CellLayer__
#define __puzzlezip__CellLayer__

#include "../../HeaderList.h"

class CellLayer : public Node
{
private:
    int     m_nType;
    int     m_nPosIndex;
    
    Sprite* m_pCell;
    
public:
    enum
    {
    };
    
    CellLayer();
    virtual ~CellLayer();
    static CellLayer* create( int nType, int nPosIndex );

    bool init( int nType, int nPosIndex );
};


#endif /* defined(__puzzlezip__CellLayer__) */
