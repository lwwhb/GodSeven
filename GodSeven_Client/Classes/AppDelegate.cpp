#include "AppDelegate.h"
#include "MainLayer.h"

USING_NS_CC;
using namespace cn::sharesdk;
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    //初始化ShareSDK
    C2DXShareSDK::open("480cac77c908", false);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    //初始化ShareSDK
    C2DXShareSDK::open("480c57be861e", false);
    
#endif
    
    //初始化社交平台信息
    this->initPlatformConfig();
    
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    std::vector<std::string> searchPaths;
    searchPaths.push_back("fonts");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
#endif
#if COCOS2D_DEBUG
    // turn on display FPS
    director->setDisplayStats(true);
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = MainLayer::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
void AppDelegate::initPlatformConfig()
{
    //新浪微博
    CCDictionary *sinaConfigDict = CCDictionary::create();
    sinaConfigDict -> setObject(CCString::create("1200571693"), "app_key");
    sinaConfigDict -> setObject(CCString::create("49631b789a534a4d2e2d3063e827a9d7"), "app_secret");
    sinaConfigDict -> setObject(CCString::create("http://www.wanaxgame.com/game/auth_callback"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeSinaWeibo, sinaConfigDict);
    
    //微信
    CCDictionary *wcConfigDict = CCDictionary::create();
    wcConfigDict -> setObject(CCString::create("wx1d8e061c7948475b"), "app_id");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeWeixiSession, wcConfigDict);
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeWeixiTimeline, wcConfigDict);
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeWeixiFav, wcConfigDict);
    
    //Facebook
    CCDictionary *fbConfigDict = CCDictionary::create();
    fbConfigDict -> setObject(CCString::create("667421830043877"), "api_key");
    fbConfigDict -> setObject(CCString::create("d3d041ad03f8d9beeb394d728033588a"), "app_secret");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeFacebook, fbConfigDict);
    
    //Twitter
    CCDictionary *twConfigDict = CCDictionary::create();
    twConfigDict -> setObject(CCString::create("sMRgFEUjmICX1FjjELqT2zc33"), "consumer_key");
    twConfigDict -> setObject(CCString::create("qC0wGr9A5KN4DRf3ZGd9MkuNDtvcZqkhIcZWszcrMhtQ01O6EP"), "consumer_secret");
    twConfigDict -> setObject(CCString::create("http://www.wanaxgame.com/game/auth_callback"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeTwitter, twConfigDict);
}
