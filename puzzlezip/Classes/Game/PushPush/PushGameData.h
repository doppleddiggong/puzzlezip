//
//  PushGameData.h
//  puzzlezip
//
//  Created by bae ju baeck on 2014. 12. 19..
//
//

#ifndef __puzzlezip__PushGameData__
#define __puzzlezip__PushGameData__

#include "cocos2d.h"
USING_NS_CC;

#define STAGE_FILE_PATH             "push_stagedata.xml"
#define LOCAL_STAGE_FILE_PATH       "Data/push_stagedata.xml"

#define STAGE_DATA_MAP_MAX_NUM  60
extern int STAGE_DATA_MAP[STAGE_DATA_MAP_MAX_NUM];

std::string getPushGameDataXmlFullPath();
ValueMap getPushGameDataValueMap();
void writeStageData( __String strFilePath, ValueMap valueMap, __String strKey, __String strValue );

#endif
