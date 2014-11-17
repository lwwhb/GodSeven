//
//  CommonHelper.cpp
//  GodSeven
//
//  Created by wang haibo on 14/11/12.
//
//

#include "CommonHelper.h"
USING_NS_CC;

std::string CommonHelper::getLocalString(const char* key)
{
    ValueMap dict;
    LanguageType lt= CCApplication::getInstance()->getCurrentLanguage();
    switch (lt) {
        case LanguageType::CHINESE:
            dict = FileUtils::getInstance()->getValueMapFromFile("chinese.plist");
            CCASSERT(!dict.empty(), "cannot create dictionary");
            break;
            
        default:
            dict = FileUtils::getInstance()->getValueMapFromFile("english.plist");
            CCASSERT(!dict.empty(), "cannot create dictionary");
            break;
    }
    
    Value ret = dict[key];
    
    return ret.asString();
}