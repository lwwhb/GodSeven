//
//  RankLayer.cpp
//  SkipSeven
//
//  Created by wang haibo on 14-9-23.
//
//

#include "RankLayer.h"
#include "MainLayer.h"
#include "SimpleAudioEngine.h"
#include "CommonHelper.h"
using namespace CocosDenshion;
USING_NS_CC;

RankLayer* RankLayer::create(int score, const cocos2d::Color4B& bgColor, const cocos2d::Color3B& textColor)
{
    RankLayer* layer = new RankLayer();
    if(layer && layer->initWithColor(score, bgColor, textColor))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

void RankLayer::setEnable(bool bEnable)
{
    m_bEnable = bEnable;
}

bool RankLayer::initWithColor(int score, const cocos2d::Color4B& bgColor, const cocos2d::Color3B& textColor)
{
    if ( !Layer::init() )
        return false;
    
    setCascadeOpacityEnabled(true);
    
    auto touchListener=EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan=CC_CALLBACK_2(RankLayer::onTouchBegan,this);
    touchListener->onTouchEnded=CC_CALLBACK_2(RankLayer::onTouchEnded,this);
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
    
    
    float titleWidth =  visibleSize.width*0.1f;
    labelTitle = Label::createWithTTF(CommonHelper::getLocalString("GlobalRank"), CommonHelper::getLocalString("MainFont"),titleWidth);

    labelTitle->setAlignment(TextHAlignment::CENTER);
    labelTitle->setColor(textColor);
    labelTitle->enableOutline(Color4B::GRAY, 2);
    labelTitle->setPosition(visibleSize.width*0.5f, visibleSize.height*0.85f);
    this->addChild(labelTitle);
    
    float btnWidth = size.width*0.4f;
    float btnHeight = size.height*0.12f;
    restartBtn = ColorButton::create(CommonHelper::getLocalString("Restart"), btnWidth, btnHeight, visibleSize.width*0.4f, visibleSize.height*(-0.08f), bgColor, textColor);
    layerColorBG->addChild(restartBtn);

    return true;
}

bool RankLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return true;
}
void RankLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    if(!m_bEnable)
        return;
    if(touch)
    {
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
    }
}

void RankLayer::clickRestartBtn()
{
    log("clickRestartBtn");
    SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
    MainLayer* mainLayer = dynamic_cast<MainLayer*>(this->getParent());
    if(mainLayer)
        mainLayer->endRankLayer();
}