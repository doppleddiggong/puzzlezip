//
//  BaseLayer.cpp
//  puzzlezip
//
//  Created by bae ju baeck on 2015. 1. 5..
//
//

#include "CustomMath.h"
#include "DefineData.h"
#include "Display.h"

#include "BaseLayer.h"

BaseScene::BaseScene()
{}

BaseScene::~BaseScene()
{}

Scene* BaseScene::createScene()
{
    Scene* pScene = Scene::create();
    BaseScene* pLayer = BaseScene::create();
    pLayer->initLoadData();
    pScene->addChild(pLayer);
    return pScene;
}

bool BaseScene::init()
{
    return Layer::init();
}
