//
//  NativeBridge.mm
//  GodSeven
//
//  Created by wang haibo on 14/11/17.
//
//

#include "NativeBridge.h"
USING_NS_CC;
static NativeBridge *s_NativeBridge = nullptr;
NativeBridge::NativeBridge()
{
}
NativeBridge* NativeBridge::getInstance()
{
    if (! s_NativeBridge)
    {
        s_NativeBridge = new NativeBridge();
    }
    
    return s_NativeBridge;
}
NativeBridge::~NativeBridge()
{
}
void NativeBridge::setRootViewController(RootViewController* viewController)
{
    mViewController = viewController;
}
void NativeBridge::showAdsView()
{
    log("showAdsView");
    if(mViewController != nil)
       [mViewController showAdsView];
}
void NativeBridge::hideAdsView()
{
    log("hideAdsView");
    if(mViewController != nil)
        [mViewController hideAdsView];
}
void NativeBridge::showRateAppView()
{
    log("showRateAppView");
    if(mViewController != nil)
    {
        LanguageType lt= CCApplication::getInstance()->getCurrentLanguage();
        switch (lt) {
            case LanguageType::CHINESE:
                [mViewController showRateAppViewCH];
                break;
                
            default:
                [mViewController showRateAppViewEN];
                break;
        }
    }
}