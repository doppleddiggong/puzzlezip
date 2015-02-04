//
//  MainStageScene.cpp
//  puzzlezip
//
//  Created by bae ju baeck on 2014. 12. 19..
//
//

#include "MainStageScene.h"

MainStageScene::MainStageScene()
{
    m_vecCellLayer.clear();
}

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
    CCLOG("MainStageScene::initLoadData()");
    
    int nCurStage = 3;
    this->loadStageData( nCurStage );
    
    this->initTouchEvent();
    this->initBg();
    this->initCellLayer();
    this->initArrowButton();
}

void MainStageScene::loadStageData( int nStage )
{
    // 저장소에서 XML데이터를 읽어 온다
    m_valueMap = getPushGameDataValueMap();
    
    // 현재 스테이지에 해당하는 데이터를 읽어온다
    __String strStageKey;
    strStageKey.initWithFormat("stage%d", nStage );
    __String stageInfo = m_valueMap[strStageKey.getCString()].asString();
 
    for( int i = 0 ; i < stageInfo.length(); i++ )
    {
        STAGE_DATA_MAP[i] = Value( stageInfo._string.substr(i,1) ).asInt();
    }
}

void MainStageScene::initTouchEvent()
{
    EventListenerTouchOneByOne* pEventListener = EventListenerTouchOneByOne::create();
    pEventListener->onTouchBegan = CC_CALLBACK_2(MainStageScene::onTouchBegan, this);
    pEventListener->onTouchMoved = CC_CALLBACK_2(MainStageScene::onTouchMoved, this);
    pEventListener->onTouchEnded = CC_CALLBACK_2(MainStageScene::onTouchEnded, this);
    pEventListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithFixedPriority(pEventListener, TOUCH_PRIORITY_SCENE );
}

void MainStageScene::initBg()
{
    m_pBg = createSprite( this, "Game/guild_bg.png", centerPos() );
    m_pBg->setOpacity(150);

    m_pTitleLabel = createLabel( this, ex_fNormalFontSize, centerPos() );
    m_pTitleLabel->setColor( Color3B::RED );
}

void MainStageScene::initCellLayer()
{
    m_nCellWidth = DEFAULT_DISPLAY_WIDTH/CELL_SIZE;
    m_nCellHeight = DEFAULT_DISPLAY_HEIGHT/CELL_SIZE;
    
    for( int i = 0; i < STAGE_DATA_MAP_MAX_NUM; i++ )
    {
        CellLayer* pCellLayer = CellLayer::create(STAGE_DATA_MAP[i], i);
        this->addChild(pCellLayer);
        
        m_vecCellLayer.push_back( pCellLayer );
    }
}

void MainStageScene::initArrowButton()
{
    int nPosX   = 400;
    int nPosY   = 450;
    int nWidth  = 100;
    
    for( int i = 0; i < ARROW_MAX_NUM; i ++ )
    {
        int nTag = TOUCH_TAG_ARROW_LEFT + i;
        Vec2 vecPos = Vec2( getWindowX(nPosX + nWidth*i ), getWindowY(nPosY) );
        
        createButton(this, m_pArrowButton[i], "Game/arrow_left.png", vecPos, nTag  );
        m_touchMap.insert(MAP_FUNC_LIST::value_type(m_pArrowButton[i][NORMAL_IMAGE], &MainStageScene::arrowTouched));
        m_touchMap.insert(MAP_FUNC_LIST::value_type(m_pArrowButton[i][PRESS_IMAGE], &MainStageScene::arrowTouched));
        
        if( nTag == TOUCH_TAG_ARROW_RIGHT )
        {
            m_pArrowButton[i][NORMAL_IMAGE]->setFlippedX(true);
            m_pArrowButton[i][PRESS_IMAGE]->setFlippedX(true);
        }
        else if( nTag == TOUCH_TAG_ARROW_UP )
        {
            m_pArrowButton[i][NORMAL_IMAGE]->setRotation( 90 );
            m_pArrowButton[i][PRESS_IMAGE]->setRotation( 90 );
        }
        else if( nTag == TOUCH_TAG_ARROW_DOWN )
        {
            m_pArrowButton[i][NORMAL_IMAGE]->setRotation( -90 );
            m_pArrowButton[i][PRESS_IMAGE]->setRotation( -90 );
        }
    }
}

void MainStageScene::refreshCell()
{
    for( int i = 0; i < STAGE_DATA_MAP_MAX_NUM; i++ )
    {
        m_vecCellLayer[i]->refreshCellType(STAGE_DATA_MAP[i]);
    }
}

bool MainStageScene::isMapOut( int nTag, int nTargetIndex )
{
    bool bRet = false;

    if( nTag == TOUCH_TAG_ARROW_LEFT )
    {
        if( nTargetIndex%m_nCellWidth == 0 )
        {
            bRet = true;
        }
    }
    else if( nTag == TOUCH_TAG_ARROW_RIGHT )
    {
        if( nTargetIndex%m_nCellWidth == m_nCellWidth-1 )
        {
            bRet = true;
        }
    }
    else if( nTag == TOUCH_TAG_ARROW_UP )
    {
        if( nTargetIndex/m_nCellWidth == 0 )
        {
            bRet = true;
        }
    }
    else if( nTag == TOUCH_TAG_ARROW_DOWN )
    {
        if( nTargetIndex/m_nCellWidth == m_nCellHeight-1 )
        {
            bRet = true;
        }
    }
    
    return bRet;
}

int MainStageScene::getCharacterPosIndex()
{
    for( int i = 0 ; i < STAGE_DATA_MAP_MAX_NUM; i++ )
    {
        if( STAGE_DATA_MAP[i] == CELL_TYPE_CHARACTER )
        {
            return i;
        }
    }
    
    return ERROR;
}

void MainStageScene::cellDataMove( int nCurPosIdx, int nNextPosIdx )
{
    int nCurCellType = STAGE_DATA_MAP[nCurPosIdx];
    int nNextCellType = STAGE_DATA_MAP[nNextPosIdx];
    
    STAGE_DATA_MAP[nNextPosIdx] = nCurCellType;
    STAGE_DATA_MAP[nCurPosIdx] = nNextCellType;
}

int MainStageScene::getNextPosIdx( int nTag, int nCurPosIdx )
{
    int nRetNextPosIdx = 0;
    
    if( nTag == TOUCH_TAG_ARROW_LEFT )
    {
        nRetNextPosIdx = nCurPosIdx - 1;
    }
    else if( nTag == TOUCH_TAG_ARROW_RIGHT )
    {
        nRetNextPosIdx = nCurPosIdx + 1;
    }
    else if( nTag == TOUCH_TAG_ARROW_UP )
    {
        nRetNextPosIdx = nCurPosIdx - m_nCellWidth;
    }
    else if( nTag == TOUCH_TAG_ARROW_DOWN )
    {
        nRetNextPosIdx = nCurPosIdx + m_nCellWidth;
    }
    
    return nRetNextPosIdx;
}

// nCurPosIdx 에 있는 물체가 nTag 방향으로 이동하려고 하는데 이동이 가능한가?
int MainStageScene::isBallMoveEnable( int nTag, int nCurPosIdx )
{
    int nNextPosIdx = getNextPosIdx(nTag, nCurPosIdx);
    
    if( isMapOut( nTag, nCurPosIdx ))
    {
        return ERROR;
    }

    if( STAGE_DATA_MAP[nNextPosIdx] == CELL_TYPE_OPEN )
    {
        return nNextPosIdx;
    }
    
    return ERROR;
}

int MainStageScene::getMoveShakeType( int nTag )
{
    if( nTag == TOUCH_TAG_ARROW_LEFT )
    {
        return CellLayer::SHAKE_TYPE_WIDTH;
    }
    else if( nTag == TOUCH_TAG_ARROW_RIGHT )
    {
        return CellLayer::SHAKE_TYPE_WIDTH;
    }
    else if( nTag == TOUCH_TAG_ARROW_UP )
    {
        return CellLayer::SHAKE_TYPE_HEIGHT;
    }
    else if( nTag == TOUCH_TAG_ARROW_DOWN )
    {
        return CellLayer::SHAKE_TYPE_HEIGHT;
    }

    return CellLayer::SHAKE_TYPE_WIDTH;
}

void MainStageScene::arrowTouched( int nTag )
{
    CCLOG("MainStageScene::bgTouched(%d)", nTag );
    
    int nCurCharacterPosIdx = getCharacterPosIndex();
    if( nCurCharacterPosIdx == ERROR )
    {
        CCLOG("캐릭터의 위치를 못찾았습니다.");
        return;
    }
    
    int nNextPosIdx = getNextPosIdx(nTag, nCurCharacterPosIdx);
    int nShakeType = getMoveShakeType( nTag );
   
    if( isMapOut( nTag, nCurCharacterPosIdx ))
    {
        m_vecCellLayer[nCurCharacterPosIdx]->startShakeAnimation( nShakeType );
    }
    else if( STAGE_DATA_MAP[nNextPosIdx] == CELL_TYPE_WALL )
    {
        m_vecCellLayer[nCurCharacterPosIdx]->startShakeAnimation( nShakeType );
    }
    else if( STAGE_DATA_MAP[nNextPosIdx] == CELL_TYPE_BALL )
    {
        int nBallNextPosIdx = isBallMoveEnable( nTag, nNextPosIdx );
        // 다음 위치에 있는 공은 내가 움직이려는 방향으로 이동이 가능한가?
        if( nBallNextPosIdx == ERROR )
        {
            m_vecCellLayer[nCurCharacterPosIdx]->startShakeAnimation( nShakeType );
        }
        else
        {
            // 이동이 가능하다
            // 볼을 먼저 이동해준다
            this->cellDataMove( nNextPosIdx, nBallNextPosIdx );
            // 내 캐릭터를 이동시킨다
            this->cellDataMove( nCurCharacterPosIdx, nNextPosIdx );
            // 화면을 갱신한다
            this->refreshCell();
        }
    }
    else if( STAGE_DATA_MAP[nNextPosIdx] == CELL_TYPE_OPEN )
    {
        // 이동 가능
        this->cellDataMove( nCurCharacterPosIdx, nNextPosIdx );
        this->refreshCell();
    }
}

void MainStageScene::buttonTouchBegan( int nTag )
{
    CCLOG("MainStageScene::buttonTouchBegan(%d)", nTag);
    
    switch( nTag )
    {
        case TOUCH_TAG_ARROW_LEFT:
        case TOUCH_TAG_ARROW_RIGHT:
        case TOUCH_TAG_ARROW_UP:
        case TOUCH_TAG_ARROW_DOWN:
        {
            int nIndex = nTag - TOUCH_TAG_ARROW_LEFT;
            m_pArrowButton[nIndex][PRESS_IMAGE]->setVisible(true);
        }
            break;
    }
}

void MainStageScene::buttonTouchEnded( int nTag )
{
    CCLOG("MainStageScene::buttonTouchEnded(%d)", nTag);

    switch( nTag )
    {
        case TOUCH_TAG_ARROW_LEFT:
        case TOUCH_TAG_ARROW_RIGHT:
        case TOUCH_TAG_ARROW_UP:
        case TOUCH_TAG_ARROW_DOWN:
        {
            int nIndex = nTag - TOUCH_TAG_ARROW_LEFT;
            m_pArrowButton[nIndex][PRESS_IMAGE]->setVisible(false);
        }
            break;
    }
}

bool MainStageScene::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    if(pTouch->getID() != SINGLE_TOUCH_ID)
        return true;
    
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
    if(pTouch->getID() != SINGLE_TOUCH_ID)
        return;

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
            if( isSpriteRectTouched( pSprite, loc ) == false )
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
    if(pTouch->getID() != SINGLE_TOUCH_ID)
        return;

    Vec2 loc = pTouch->getLocation();
    m_pTouchEnded = loc;
    this->buttonTouchEnded(m_nTouchTag);

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
