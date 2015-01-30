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
    bool    m_bAnimationIng;
    
    Sprite* m_pCell;
    
public:
    enum
    {
        SHAKE_TYPE_WIDTH    = 0,
        SHAKE_TYPE_HEIGHT   = 1,
    };
    
    CellLayer();
    virtual ~CellLayer();
    static CellLayer* create( int nType, int nPosIndex );

    bool init( int nType, int nPosIndex );
    
    void refreshCellType( int nType );
    
    void startCharacterAnimation();
    void startShakeAnimation( int nShakeType );
    void endAnimation();
};


#endif
