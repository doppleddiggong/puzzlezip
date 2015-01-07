//
//  MainStageScene.cpp
//  puzzlezip
//
//  Created by bae ju baeck on 2014. 12. 19..
//
//

#include "MainStageScene.h"

// todo
const int CELL_MAP[] =
{
    0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
    0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
    0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
    0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
    0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
    0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
    0,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
    0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};


MainStageScene::MainStageScene()
{}

MainStageScene::~MainStageScene()
{}

Scene* MainStageScene::createScene()
{
    Scene* pScene = Scene::create();
    MainStageScene* pLayer = MainStageScene::create();
    pLayer->initLoadData();
    pScene->addChild(pLayer);
    return pScene;
}

bool MainStageScene::init()
{
    return Layer::init();
}

void MainStageScene::initLoadData()
{
    this->initTouchEvent();
    this->initBg();
    this->initCellLayer();
    this->initArrow();
}

void MainStageScene::initTouchEvent()
{
    EventListenerTouchOneByOne* pEventListener = EventListenerTouchOneByOne::create();
    pEventListener->onTouchBegan = CC_CALLBACK_2(MainStageScene::onTouchBegan, this);
    pEventListener->onTouchMoved = CC_CALLBACK_2(MainStageScene::onTouchMoved, this);
    pEventListener->onTouchEnded = CC_CALLBACK_2(MainStageScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(pEventListener, this);
}

void MainStageScene::initBg()
{
    m_pBg = createSprite( this, "Game/guild_bg.png", centerPos() );
    m_pBg->setOpacity(150);
    m_pBg->setTag(100);
//    m_touchMap.insert(MAP_FUNC_LIST::value_type(m_pBg, &MainStageScene::bgTouched));

//    m_pTitleLabel = createLabel( this, ex_fNormalFontSize, centerPos() );
//    m_pTitleLabel->setColor( Color3B::RED );
//    __String strBuff;
//    strBuff.initWithFormat("%d MainStageScene", 0);
//    m_pTitleLabel->setString( strBuff.getCString());
}

void MainStageScene::initCellLayer()
{
    int nWidth = DEFAULT_DISPLAY_WIDTH/CELL_SIZE;
    int nHeight = DEFAULT_DISPLAY_HEIGHT/CELL_SIZE;
    int nCnt = nWidth* nHeight;
    
    for( int i = 0; i < nCnt; i++ )
    {
        CellLayer* pCellLayer = CellLayer::create(CELL_MAP[i], i);
        this->addChild(pCellLayer);
        
        if( CELL_MAP[i] == CELL_TYPE_CHARACTER )
        {
            CharacterLayer* pCharacterLayer = CharacterLayer::create( i );
            this->addChild(pCharacterLayer);
        }
    }
}

void MainStageScene::initArrow()
{
    
}


void MainStageScene::bgTouched( int nTag )
{
    CCLOG("MainStageScene::bgTouched(%d)", nTag );
}

void MainStageScene::buttonTouchBegan( int nTag )
{
    CCLOG("MainStageScene::buttonTouchBegan(%d)", nTag);
}

void MainStageScene::buttonTouchEnded( int nTag )
{
    CCLOG("MainStageScene::buttonTouchEnded(%d)", nTag);
}

bool MainStageScene::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    Vec2 loc = pTouch->getLocation();
    m_pTouchBegan = loc;
    m_bTouchMoved = false;
    
    for (m_Iterator = m_touchMap.begin(); m_Iterator != m_touchMap.end(); m_Iterator++)
    {
        Sprite* pSprite = m_Iterator->first;
        if( isVisibleTouchEnable( pSprite) )
        {
            int nIndex = pSprite->getTag();
            if( isSpriteRectTouched( pSprite, loc ))
            {
                m_nTouchTag = nIndex;
                buttonTouchBegan(m_nTouchTag);
                return true;
            }
        }
    }
    
    return true;
}

void MainStageScene::onTouchMoved(Touch* pTouch, Event* pEvent)
{
    Vec2 loc = pTouch->getLocation();
    
    if( getPtDistance(m_pTouchBegan, loc ) > TOUCH_MOVED_OFFSET )
    {
        m_bTouchMoved = true;
    }
    
    for (m_Iterator = m_touchMap.begin(); m_Iterator != m_touchMap.end(); m_Iterator++)
    {
        Sprite* pSprite = m_Iterator->first;
        if( isVisibleTouchEnable( pSprite) )
        {
            int nIndex = pSprite->getTag();
            if( isSpriteRectTouched( pSprite, loc ))
            {
                if( m_nTouchTag == nIndex )
                {
                    buttonTouchEnded(m_nTouchTag);
                    m_nTouchTag = TOUCH_CANCEL_TAG;
                }
            }
        }
    }
}

void MainStageScene::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    Vec2 loc = pTouch->getLocation();
    
    buttonTouchEnded(m_nTouchTag);
    
    if( m_bTouchMoved )
    {
        m_bTouchMoved = false;
        return;
    }
    
    for (m_Iterator = m_touchMap.begin(); m_Iterator != m_touchMap.end(); m_Iterator++)
    {
        Sprite* pSprite = m_Iterator->first;
        if( isVisibleTouchEnable( pSprite) )
        {
            int nIndex = pSprite->getTag();
            if( isSpriteRectTouched( pSprite, loc ))
            {
                if( m_nTouchTag == nIndex )
                {
                    pFunc = m_Iterator->second;
                    (this->*pFunc)(nIndex);
                    break;
                }
            }
        }
    }
    
    m_nTouchTag = TOUCH_CANCEL_TAG;
}