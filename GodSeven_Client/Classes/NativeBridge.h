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
#import "RootViewController.h"
class NativeBridge : public cocos2d::Ref
{
    NativeBridge();
public:
    static NativeBridge* getInstance();
    virtual ~NativeBridge();
    
    void setRootViewController(RootViewController* viewController);
    void showAdsView();
    void hideAdsView();
    void showRateAppView();
    
private:
    RootViewController* mViewController;
};

#endif /* defined(__GodSeven__NativeBridge__) */
