//
//  MainMenuLayer.cpp
//  GodSeven
//
//  Created by wang haibo on 14-9-28.
//
//

#include "MainMenuLayer.h"
#include "MainLayer.h"
#include "SimpleAudioEngine.h"
#include "CommonHelper.h"
using namespace CocosDenshion;
USING_NS_CC;

MainMenuLayer* MainMenuLayer::create(const Color4B& bgColor, const Color3B& textColor)
{
    MainMenuLayer* layer = new MainMenuLayer();
    if(layer && layer->initWithColor(bgColor, textColor))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}
void MainMenuLayer::setEnable(bool bEnable)
{
    m_bEnable = bEnable;
}
bool MainMenuLayer::initWithColor(const Color4B& bgColor, const Color3B& textColor)
{
    if ( !Layer::init() )
        return false;
    
    m_bEnable = false;
    
    setCascadeOpacityEnabled(true);
    
    auto touchListener=EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan=CC_CALLBACK_2(MainMenuLayer::onTouchBegan,this);
    touchListener->onTouchEnded=CC_CALLBACK_2(MainMenuLayer::onTouchEnded,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    
    float titleWidth =  visibleSize.width*0.25f;
    labelTitle = Label::createWithTTF(CommonHelper::getLocalString("MainTitle"), CommonHelper::getLocalString("MainFont"), titleWidth);
    labelTitle->setAlignment(TextHAlignment::CENTER);
    labelTitle->setColor(textColor);
    labelTitle->enableOutline(Color4B::GRAY, 4);
    labelTitle->setPosition(visibleSize.width*0.5f, visibleSize.height*0.7f);
    this->addChild(labelTitle);
    
    float btnWidth = visibleSize.width*0.4f;
    float btnHeight = btnWidth*0.35f;
    startBtn = ColorButton::create(CommonHelper::getLocalString("Start"), btnWidth, btnHeight, visibleSize.width*0.5f, visibleSize.height*0.4f, bgColor, textColor);
    this->addChild(startBtn);
    
    helpBtn = ColorButton::create(CommonHelper::getLocalString("Help"), btnWidth, btnHeight,  visibleSize.width*0.5f, visibleSize.height*0.25f, bgColor, textColor);
    this->addChild(helpBtn);
    return true;
}
bool MainMenuLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return true;
}
void MainMenuLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    if(!m_bEnable)
        return;
    if(touch)
    {
        if(startBtn)
        {
            Vec2 locationInNode = startBtn->convertToNodeSpace(touch->getLocation());
            cocos2d::Size st = startBtn->getContentSize();
            cocos2d::Rect rect = cocos2d::Rect(0, 0, st.width, st.height);
            if(rect.containsPoint(locationInNode))
            {
                clickStartBtn();
                return;
            }
        }
        if(helpBtn)
        {
            Vec2 locationInNode = helpBtn->convertToNodeSpace(touch->getLocation());
            cocos2d::Size st = helpBtn->getContentSize();
            cocos2d::Rect rect = cocos2d::Rect(0, 0, st.width, st.height);
            if(rect.containsPoint(locationInNode))
            {
                clickHelpBtn();
                return;
            }
        }
    }
}
void MainMenuLayer::clickStartBtn()
{
    log("clickStartBtn");
    SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
    MainLayer* mainLayer = dynamic_cast<MainLayer*>(this->getParent());
    if(mainLayer)
        mainLayer->endMenuLayer(true);
}
void MainMenuLayer::clickHelpBtn()
{
    log("clickHelpBtn");
    SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
    MainLayer* mainLayer = dynamic_cast<MainLayer*>(this->getParent());
    if(mainLayer)
    {
        mainLayer->addHelpLayer();
        mainLayer->endMenuLayer(false);
    }
}