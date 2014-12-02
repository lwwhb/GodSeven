//
//  NetworkMgr.cpp
//  GodSeven
//
//  Created by wang haibo on 14/11/24.
//
//

#include "NetworkMgr.h"
USING_NS_CC;

static NetworkMgr *s_NetworkMgr = nullptr;
NetworkMgr::NetworkMgr()
{
}
NetworkMgr* NetworkMgr::getInstance()
{
    if (!s_NetworkMgr)
    {
        s_NetworkMgr = new NetworkMgr();
    }
    
    return s_NetworkMgr;
}
NetworkMgr::~NetworkMgr()
{
}

void NetworkMgr::requestForGlobalBank()
{
}
void NetworkMgr::responseForGlobalBank()
{
}

void NetworkMgr::requestForUpdateMyselfBank()
{
}
void NetworkMgr::responseForUpdateMyselfBank()
{
}