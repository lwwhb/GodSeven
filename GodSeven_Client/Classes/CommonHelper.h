//
//  CommonHelper.h
//  GodSeven
//
//  Created by wang haibo on 14/11/12.
//
//

#ifndef __GodSeven__CommonHelper__
#define __GodSeven__CommonHelper__

#include "cocos2d.h"
class CommonHelper
{
public:
    static std::string getLocalString(const char* key);
    static void screenshot(const std::string& fileName,const std::function<void(const std::string&)>& callback);
};

#endif /* defined(__GodSeven__CommonHelper__) */
