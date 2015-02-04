//
//  CreateStageScene.cpp
//  puzzlezip
//
//  Created by bae ju baeck on 2015. 2. 2..
//
//

#include "CreateStageScene.h"

CreateStageScene::CreateStageScene()
{
    m_vecCellLayer.clear();
}

CreateStageScene::~CreateStageScene()
{}

Scene* CreateStageScene::createScene()
{
    Scene* pScene = Scene::create();
    CreateStageScene* pLayer = CreateStageScene::create();
    pLayer->initLoadData();
    pScene->addChild(pLayer);
    return pScene;
}

bool CreateStageScene::init()
{
    return Layer::init();
}

void CreateStageScene::initLoadData()
{
    CCLOG("CreateStageScene::initLoadData()");
    this->initTouchEvent();

    this->initBg();
    this->initCellLayer();

    this->initButtonSet();

}

void CreateStageScene::initTouchEvent()
{
    EventListenerTouchOneByOne* pEventListener = EventListenerTouchOneByOne::create();
    pEventListener->onTouchBegan = CC_CALLBACK_2(CreateStageScene::onTouchBegan, this);
    pEventListener->onTouchMoved = CC_CALLBACK_2(CreateStageScene::onTouchMoved, this);
    pEventListener->onTouchEnded = CC_CALLBACK_2(CreateStageScene::onTouchEnded, this);
    pEventListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithFixedPriority(pEventListener, TOUCH_PRIORITY_SCENE );
}

void CreateStageScene::initBg()
{
    m_pBg = createSprite( this, "Game/guild_bg.png", centerPos() );
    m_pBg->setOpacity(150);
    
    m_pTitleLabel = createLabel( this, ex_fNormalFontSize, centerPos() );
    m_pTitleLabel->setColor( Color3B::RED );
}

void CreateStageScene::initCellLayer()
{
    for( int i = 0; i < STAGE_DATA_MAP_MAX_NUM; i++ )
    {
        CellLayer* pCellLayer = CellLayer::create(CELL_TYPE_WALL, i, true );
        this->addChild(pCellLayer);
        
        m_vecCellLayer.push_back( pCellLayer );
    }
}

void CreateStageScene::initButtonSet()
{
    createButton(this, m_pButtonSetButton, "Game/plus_button.png", Vec2(getWindowX(775), getWindowY(25)), 0  );
    m_touchMap.insert(MAP_FUNC_LIST::value_type(m_pButtonSetButton[NORMAL_IMAGE], &CreateStageScene::buttonSetTouched));
    m_touchMap.insert(MAP_FUNC_LIST::value_type(m_pButtonSetButton[PRESS_IMAGE], &CreateStageScene::buttonSetTouched));
}

void CreateStageScene::buttonSetTouched( int nTag )
{
    CCLOG("CreateStageScene::buttonSetTouched( %d )", nTag );
    
    ValueMap valueMap = getPushGameDataValueMap();
    int nSize = (int)valueMap.size();
    __String strNewStageKey;
    strNewStageKey.initWithFormat("stage%d", nSize+1);
    
    int nGoalCnt = 0;
    int nBallCnt = 0;
    int nCharacterCnt = 0;
    
    std::string strCellMap;
    for( int i = 0 ; i < STAGE_DATA_MAP_MAX_NUM; i ++)
    {
        int nCellType = m_vecCellLayer[i]->getCellType();
        
        if( nCellType == CELL_TYPE_CHARACTER )
        {
            nCharacterCnt++;
        }
        if( nCellType == CELL_TYPE_BALL )
        {
            nBallCnt++;
            nGoalCnt++;
        }
        
        __String strMap;
        strMap.initWithFormat("%d", nCellType );
        strCellMap.append( strMap.getCString() );
    }
    __String strNewStageValue;
    strNewStageValue.initWithFormat("%s", strCellMap.c_str() );
    
    // 정상적인 맵인지 검사한다
    if( nCharacterCnt != 1 )
    {
        CCLOG("캐릭터는 오직 한명만 존재합니다");
        return;
    }

    if( nBallCnt != nGoalCnt )
    {
        CCLOG("골의 수와 볼의 수가 일치하지 않습니다");
        return;
    }
    CCLOG("현재 셀 데이터를 저장합니다(key : %s)", strNewStageKey.getCString() );

    writeStageData(getPushGameDataXmlFullPath(), valueMap, strNewStageKey, strNewStageValue);
}

void CreateStageScene::buttonTouchBegan( int nTag )
{
    CCLOG("CreateStageScene::buttonTouchBegan(%d)", nTag);
}

void CreateStageScene::buttonTouchEnded( int nTag )
{
    CCLOG("CreateStageScene::buttonTouchEnded(%d)", nTag);
}

bool CreateStageScene::onTouchBegan(Touch* pTouch, Event* pEvent)
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
    
    return false;
}

void CreateStageScene::onTouchMoved(Touch* pTouch, Event* pEvent)
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

void CreateStageScene::onTouchEnded(Touch* pTouch, Event* pEvent)
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
