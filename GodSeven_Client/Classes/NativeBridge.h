//
//  NativeBridge.h
//  GodSeven
//
//  Created by wang haibo on 14/11/17.
//
//

#ifndef __GodSeven__NativeBridge__
#define __GodSeven__NativeBridge__
#include "cocos2d.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    #import "RootViewController.h"
#endif
class NativeBridge : public cocos2d::Ref
{
    NativeBridge();
public:
    static NativeBridge* getInstance();
    virtual ~NativeBridge();
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    void setRootViewController(RootViewController* viewController);
#endif
    void showAdsView();
    void hideAdsView();
    void showRateAppView();
    
private:
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    RootViewController* mViewController;
#endif
    
};

#endif /* defined(__GodSeven__NativeBridge__) */
