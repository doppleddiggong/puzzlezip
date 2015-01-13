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
    m_pBg = Sprite::create("Game/guild_bg.png");
    m_pBg->setPosition(centerPos());
    this->addChild(m_pBg);

    m_pTitleLabel = Label::createWithTTF("", FONT_PATH, ex_fNormalFontSize );
    m_pTitleLabel->setPosition( centerPos() );

    __String strBuff;
    strBuff.initWithFormat("%d TestSelectScene", 0);
    m_pTitleLabel->setString( strBuff.getCString());
    m_pTitleLabel->setColor( Color3B::RED );
    this->addChild(m_pTitleLabel);
}

void TestSelectScene::initCCS()
{
//    Node* pCCSNode = SceneReader::
}









