//
//  GameOverLayer.cpp
//  SkipSeven
//
//  Created by wang haibo on 14-9-23.
//
//

#include "GameOverLayer.h"
#include "MainLayer.h"
#include "SimpleAudioEngine.h"
#include "CommonHelper.h"
#include "C2DXShareSDK.h"
#include "NativeBridge.h"
using namespace CocosDenshion;
using namespace cn::sharesdk;
USING_NS_CC;


void shareResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *shareInfo, CCDictionary *error)
{
    switch (state) {
        case C2DXResponseStateSuccess:
            CCLog("分享成功");
            SimpleAudioEngine::getInstance()->playEffect("god7.wav");
            break;
        case C2DXResponseStateFail:
            CCLog("分享失败");
            SimpleAudioEngine::getInstance()->playEffect("no7.wav");
            break;
        default:
            break;
    }
}
GameOverLayer* GameOverLayer::create(bool success, int number, float totalTime, int score, const Color4B& bgColor, const Color3B& textColor)
{
    GameOverLayer* layer = new GameOverLayer();
    if(layer && layer->initWithColor(success, number, totalTime, score, bgColor, textColor))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}
void GameOverLayer::setEnable(bool bEnable)
{
    m_bEnable = bEnable;
}
bool GameOverLayer::initWithColor(bool success, int number, float totalTime, int score, const Color4B& bgColor, const Color3B& textColor)
{
    if ( !Layer::init() )
        return false;
    
    NativeBridge::getInstance()->showRateAppView();
    setCascadeOpacityEnabled(true);
    
    auto touchListener=EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan=CC_CALLBACK_2(GameOverLayer::onTouchBegan,this);
    touchListener->onTouchEnded=CC_CALLBACK_2(GameOverLayer::onTouchEnded,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Size size = cocos2d::Size(visibleSize.width*0.8f, visibleSize.width*1.0f);
    Application::Platform platform = CCApplication::getInstance()->getTargetPlatform();
    if(platform == Application::Platform::OS_IPAD)
        size = size = cocos2d::Size(visibleSize.width*0.8f, visibleSize.width*0.9f);
    
    LayerColor* layerColorOutline = LayerColor::create(Color4B::GRAY, size.width, size.height);
    layerColorOutline->setPosition((visibleSize.width-size.width)*0.5f + 4, (visibleSize.height - size.height)*0.75f - 4);
    layerColorOutline->setCascadeOpacityEnabled(true);
    this->addChild(layerColorOutline);
    
    layerColorBG = LayerColor::create(bgColor, size.width, size.height);
    layerColorBG->setPosition((visibleSize.width-size.width)*0.5f, (visibleSize.height - size.height)*0.75f);
    layerColorBG->setCascadeOpacityEnabled(true);
    this->addChild(layerColorBG);
    
    
    float titleWidth =  visibleSize.width*0.13f;
    if(success)
    {
        labelTitle = Label::createWithTTF(CommonHelper::getLocalString("NewRecord"), CommonHelper::getLocalString("MainFont"),titleWidth);
        shareContent = CommonHelper::getLocalString("ShareContent");
    }
    else
    {
        labelTitle = Label::createWithTTF(CommonHelper::getLocalString("ComeOn"), CommonHelper::getLocalString("MainFont"),titleWidth);
        shareContent = CommonHelper::getLocalString("ShareContent2");
    }
    labelTitle->setAlignment(TextHAlignment::CENTER);
    labelTitle->setColor(textColor);
    labelTitle->enableOutline(Color4B::GRAY, 2);
    labelTitle->setPosition(visibleSize.width*0.5f, visibleSize.height*0.75f);
    this->addChild(labelTitle);
    
    std::string strCurNum = String::createWithFormat(CommonHelper::getLocalString("CurNum").c_str(), number)->getCString();
    std::string strUseTime = String::createWithFormat(CommonHelper::getLocalString("Time").c_str(), totalTime)->getCString();
    std::string strScore = String::createWithFormat(CommonHelper::getLocalString("Score").c_str(), score)->getCString();
    
    Label* labelCurNum = Label::createWithTTF(strCurNum, CommonHelper::getLocalString("MainFont"),titleWidth*0.6f);
    labelCurNum->setAlignment(TextHAlignment::CENTER);
    labelCurNum->setColor(textColor);
    labelCurNum->enableOutline(Color4B::GRAY, 2);
    labelCurNum->setPosition(visibleSize.width*0.5f, visibleSize.height*0.6f);
    this->addChild(labelCurNum);
    
    Label* labelUseTime = Label::createWithTTF(strUseTime, CommonHelper::getLocalString("MainFont"),titleWidth*0.6f);
    labelUseTime->setAlignment(TextHAlignment::CENTER);
    labelUseTime->setColor(textColor);
    labelUseTime->enableOutline(Color4B::GRAY, 2);
    labelUseTime->setPosition(visibleSize.width*0.5f, visibleSize.height*0.5f);
    this->addChild(labelUseTime);
        
    Label* labelScore = Label::createWithTTF(strScore, CommonHelper::getLocalString("MainFont"),titleWidth*0.6f);
    labelScore->setAlignment(TextHAlignment::CENTER);
    labelScore->setColor(textColor);
    labelScore->enableOutline(Color4B::GRAY, 2);
    labelScore->setPosition(visibleSize.width*0.5f, visibleSize.height*0.4f);
    this->addChild(labelScore);

    float btnWidth = size.width*0.4f;
    float btnHeight = size.height*0.12f;
//    restartBtn = ColorButton::create(CommonHelper::getLocalString("Restart"), btnWidth, btnHeight, visibleSize.width*0.2f, visibleSize.height*(-0.08f), bgColor, textColor);
//    layerColorBG->addChild(restartBtn);
    
//    rankBtn = ColorButton::create(CommonHelper::getLocalString("Rank"), btnWidth, btnHeight, visibleSize.width*0.6f, visibleSize.height*(-0.08f), bgColor, textColor);
//    layerColorBG->addChild(rankBtn);
    
    shareBtn = ColorButton::create(CommonHelper::getLocalString("Share"), btnWidth, btnHeight, visibleSize.width*0.2f, visibleSize.height*(-0.08f), bgColor, textColor);
    layerColorBG->addChild(shareBtn);
    
    restartBtn = ColorButton::create(CommonHelper::getLocalString("Restart"), btnWidth, btnHeight, visibleSize.width*0.6f, visibleSize.height*(-0.08f), bgColor, textColor);
    layerColorBG->addChild(restartBtn);
    return true;
}
bool GameOverLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return true;
}
void GameOverLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    if(!m_bEnable)
        return;
    if(touch)
    {
//        ////----debug
//        //截屏后的回调函数
//        auto callback = [&](const std::string& fullPath){
//            CCLOG("Image saved %s", fullPath.c_str());
//        };
//        
//        //调用Director的截屏功能
//        CommonHelper::screenshot("GameOver.png", callback);
//        ///----

        if(restartBtn)
        {
            Vec2 locationInNode = restartBtn->convertToNodeSpace(touch->getLocation());
            cocos2d::Size st = restartBtn->getContentSize();
            cocos2d::Rect rect = cocos2d::Rect(0, 0, st.width, st.height);
            if(rect.containsPoint(locationInNode))
            {
                clickRestartBtn();
                return;
            }
        }
//        if(rankBtn)
//        {
//            Vec2 locationInNode = rankBtn->convertToNodeSpace(touch->getLocation());
//            cocos2d::Size st = rankBtn->getContentSize();
//            cocos2d::Rect rect = cocos2d::Rect(0, 0, st.width, st.height);
//            if(rect.containsPoint(locationInNode))
//            {
//                clickRankBtn();
//                return;
//            }
//        }
        
        if(shareBtn)
        {
            Vec2 locationInNode = shareBtn->convertToNodeSpace(touch->getLocation());
            cocos2d::Size st = shareBtn->getContentSize();
            cocos2d::Rect rect = cocos2d::Rect(0, 0, st.width, st.height);
            if(rect.containsPoint(locationInNode))
            {
                clickShareBtn();
                return;
            }
        }
    }
}
void GameOverLayer::clickRestartBtn()
{
    log("clickRestartBtn");
    SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
    MainLayer* mainLayer = dynamic_cast<MainLayer*>(this->getParent());
    if(mainLayer)
        mainLayer->endGameOverLayer(true);
}
void GameOverLayer::clickRankBtn()
{
    log("clickRankBtn");
    SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
    MainLayer* mainLayer = dynamic_cast<MainLayer*>(this->getParent());
    if(mainLayer)
    {
        mainLayer->endGameOverLayer(false);
        mainLayer->addRankLayer();
    }
}
void GameOverLayer::clickShareBtn()
{
    log("clickShareBtn");
    SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
    
    //截屏后的回调函数
    auto callback = [&](const std::string& fullPath){
        CCLOG("Image saved %s", fullPath.c_str());
        //分享
        CCDictionary *content = CCDictionary::create();
        content -> setObject(CCString::create(shareContent), "content");
        content -> setObject(CCString::create(fullPath), "image");
        
        C2DXShareSDK::showShareMenu(NULL, content, CCPointMake(235, 800), C2DXMenuArrowDirectionDown, shareResultHandler);
    };
    
    //调用Director的截屏功能
    CommonHelper::screenshot("sharePic.png", callback);
}