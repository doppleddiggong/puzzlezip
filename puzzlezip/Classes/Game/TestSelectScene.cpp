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
    if ( !Layer::init() )
    {
        return false;
    }
    
    return true;
}

void TestSelectScene::initLoadData()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	CCLOG("size.width : %3.1f. size.height : %3.1f", visibleSize.width, visibleSize.height);
	CCLOG("origin.x : %3.1f. origin.y : %3.1f", origin.x, origin.y);

	m_pBg = Sprite::create("Game/character_backgroud.png");
	m_pBg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(m_pBg);

	char stringBuffer[12] = { 0 };
	sprintf(stringBuffer, "%d TestSelectScene", 0);
	m_pTitleLabel = Label::createWithTTF(stringBuffer, ex_strFontName, ex_fFontSize);
	m_pTitleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - m_pTitleLabel->getContentSize().height));
	this->addChild(m_pTitleLabel);
}