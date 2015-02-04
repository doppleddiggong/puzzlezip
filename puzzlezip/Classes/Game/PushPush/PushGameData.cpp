//
//  PushGameData.cpp
//  puzzlezip
//
//  Created by bae ju baeck on 2014. 12. 19..
//
//

#include "PushGameData.h"


int STAGE_DATA_MAP[60];

std::string getPushGameDataXmlFullPath()
{
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string retFullPath = writablePath + STAGE_FILE_PATH;
    
    return retFullPath;
}


ValueMap getPushGameDataValueMap()
{
    std::string xmlFullPath = getPushGameDataXmlFullPath();
    
    ValueMap retValueMap;
    
    bool bFileExist = FileUtils::getInstance()->isFileExist(xmlFullPath.c_str());
    if( bFileExist )
    {
        retValueMap = FileUtils::getInstance()->getValueMapFromFile(xmlFullPath.c_str());
    }
    else
    {
        retValueMap = FileUtils::getInstance()->getValueMapFromFile(LOCAL_STAGE_FILE_PATH);
    }
    
    return retValueMap;
}


void writeStageData( __String strFilePath, ValueMap valueMap, __String strKey, __String strValue )
{
    valueMap[strKey.getCString()] = Value(strValue.getCString());

    bool bRet = FileUtils::getInstance()->writeToFile(valueMap, strFilePath.getCString() );
    
    if( bRet == false )
    {
        CCLOG("writeToFile Failed");
    }
}
