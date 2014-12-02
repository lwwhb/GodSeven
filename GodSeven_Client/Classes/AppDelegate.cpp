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
    
    //初始化ShareSDK
    C2DXShareSDK::open(CCString::create("api20"), false);
    
    //初始化社交平台信息
    this->initPlatformConfig();
    
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    director->setDisplayStats(true);

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
    sinaConfigDict -> setObject(CCString::create("568898243"), "app_key");
    sinaConfigDict -> setObject(CCString::create("38a4f8204cc784f81f9f0daaf31e02e3"), "app_secret");
    sinaConfigDict -> setObject(CCString::create("http://www.sharesdk.cn"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeSinaWeibo, sinaConfigDict);
    
    //微信
//    CCDictionary *wcConfigDict = CCDictionary::create();
//    wcConfigDict -> setObject(CCString::create("wx4868b35061f87885"), "app_id");
//    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeWeixiSession, wcConfigDict);
//    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeWeixiTimeline, wcConfigDict);
//    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeWeixiFav, wcConfigDict);
    
    //Facebook
    CCDictionary *fbConfigDict = CCDictionary::create();
    fbConfigDict -> setObject(CCString::create("107704292745179"), "api_key");
    fbConfigDict -> setObject(CCString::create("38053202e1a5fe26c80c753071f0b573"), "app_secret");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeFacebook, fbConfigDict);
    
    //Twitter
    CCDictionary *twConfigDict = CCDictionary::create();
    twConfigDict -> setObject(CCString::create("mnTGqtXk0TYMXYTN7qUxg"), "consumer_key");
    twConfigDict -> setObject(CCString::create("ROkFqr8c3m1HXqS3rm3TJ0WkAJuwBOSaWhPbZ9Ojuc"), "consumer_secret");
    twConfigDict -> setObject(CCString::create("http://www.sharesdk.cn"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeTwitter, twConfigDict);
    
    
//    //LinkedIn
//    CCDictionary *liConfigDict = CCDictionary::create();
//    liConfigDict -> setObject(CCString::create("ejo5ibkye3vo"), "api_key");
//    liConfigDict -> setObject(CCString::create("cC7B2jpxITqPLZ5M"), "secret_key");
//    liConfigDict -> setObject(CCString::create("http://sharesdk.cn"), "redirect_url");
//    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeLinkedIn, liConfigDict);
}
