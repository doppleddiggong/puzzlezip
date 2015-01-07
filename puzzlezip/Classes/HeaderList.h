#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

#include "Common/DefineData.h"
#include "Common/Display.h"
#include "Common/CustomMath.h"
#include "Common/BaseLayer.h"

#include "Game/TestSelectScene.h"

#include "Game/PushPush/PushGameData.h"
#include "Game/PushPush/CellLayer.h"
#include "Game/PushPush/CharacterLayer.h"
#include "Game/PushPush/MainStageScene.h"


#define START_SCENE		MainStageScene::createScene();