 #include "TestSelectScene.h"

Scene* TestSelectScene::createScene()
{
	Scene* pScene = Scene::create();
	TestSelectScene* pLayer = TestSelectScene::create();
	pLayer->initLoadData();
	pScene->addChild(pLayer);
	return pScene;
}

bool TestSelectScene::init()
{
    return Layer::init();
}

void TestSelectScene::initLoadData()
{
    this->initBg();
    this->initCCS();
}

void TestSelectScene::initBg()
{
    m_pBg = createSprite( this, "Game/guild_bg.png", centerPos() );
    m_pBg->setOpacity(150);
    m_pTitleLabel = createLabel( this, ex_fNormalFontSize, centerPos() );
    
    __String strBuff;
    strBuff.initWithFormat("%d TestSelectScene", 0);
    m_pTitleLabel->setString( strBuff.getCString());
    m_pTitleLabel->setColor( Color3B::RED );
}

void TestSelectScene::initCCS()
{
//    Node* pCCSNode = SceneReader::
}









