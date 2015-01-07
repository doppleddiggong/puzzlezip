//
//  CharacterLayer.h
//  puzzlezip
//
//  Created by bae ju baeck on 2014. 12. 19..
//
//

#ifndef __puzzlezip__CharacterLayer__
#define __puzzlezip__CharacterLayer__

#include "../../HeaderList.h"

class CharacterLayer : public Node
{
private:
    int     m_nPosIndex;
    
    Sprite* m_pCharacterCell;
    
public:
    CharacterLayer();
    virtual ~CharacterLayer();
    static CharacterLayer* create( int nPosIndex );
    
    bool init( int nPosIndex );
};
#endif /* defined(__puzzlezip__CharacterLayer__) */
