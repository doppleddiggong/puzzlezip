 #include "TestSelectScene.h"

USING_NS_CC;

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
    m_pBg = createSprite( this, "Game/guild_bg.png", centerPos() );
    m_pTitleLabel = createLabel( this, ex_fNormalFontSize, centerPos() );
    
    __String strBuff;
    strBuff.initWithFormat("%d TestSelectScene", 0);
    m_pTitleLabel->setString( strBuff.getCString());
    m_pTitleLabel->setColor( Color3B::RED );
}










