//
//  NetworkMgr.h
//  GodSeven
//
//  Created by wang haibo on 14/11/24.
//
//

#ifndef __GodSeven__NetworkMgr__
#define __GodSeven__NetworkMgr__

#include "cocos2d.h"
class NetworkMgr : public cocos2d::Ref
{
    NetworkMgr();
public:
    static NetworkMgr* getInstance();
    virtual ~NetworkMgr();
    
    
    void requestForGlobalBank();
    void responseForGlobalBank();
    
    void requestForUpdateMyselfBank();
    void responseForUpdateMyselfBank();
};

#endif /* defined(__GodSeven__NetworkMgr__) */
