//
//  HelpLayer.cpp
//  SkipSeven
//
//  Created by wang haibo on 14-9-23.
//
//

#include "HelpLayer.h"
#include "MainLayer.h"
#include "CommonHelper.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

HelpLayer* HelpLayer::create(const cocos2d::Color4B& bgColor, const cocos2d::Color3B& textColor)
{
    HelpLayer* layer = new HelpLayer();
    if(layer && layer->initWithColor(bgColor, textColor))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

void HelpLayer::setEnable(bool bEnable)
{
    m_bEnable = bEnable;
}

bool HelpLayer::initWithColor(const Color4B& bgColor, const Color3B& textColor)
{
    if ( !Layer::init() )
        return false;
    
    setCascadeOpacityEnabled(true);
    
    auto touchListener=EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan=CC_CALLBACK_2(HelpLayer::onTouchBegan,this);
    touchListener->onTouchEnded=CC_CALLBACK_2(HelpLayer::onTouchEnded,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Size size = cocos2d::Size(visibleSize.width*0.8f, visibleSize.width*1.1f);
    
    LayerColor* layerColorOutline = LayerColor::create(Color4B::GRAY, size.width, size.height);
    layerColorOutline->setPosition((visibleSize.width-size.width)*0.5f + 4, (visibleSize.height - size.height)*0.75f - 4);
    layerColorOutline->setCascadeOpacityEnabled(true);
    this->addChild(layerColorOutline);
    
    layerColorBG = LayerColor::create(bgColor, size.width, size.height);
    layerColorBG->setPosition((visibleSize.width-size.width)*0.5f, (visibleSize.height - size.height)*0.75f);
    layerColorBG->setCascadeOpacityEnabled(true);
    this->addChild(layerColorBG);
    
    
    float titleWidth =  visibleSize.width*0.1f;
    labelTitle = Label::createWithTTF(CommonHelper::getLocalString("HelpTitle"), CommonHelper::getLocalString("MainFont"),titleWidth);
    labelTitle->setAlignment(TextHAlignment::CENTER);
    labelTitle->setColor(textColor);
    labelTitle->enableOutline(Color4B::GRAY, 2);
    labelTitle->setPosition(visibleSize.width*0.5f, visibleSize.height*0.85f);
    this->addChild(labelTitle);
    
    labelHelpInfo1 = Label::createWithTTF(CommonHelper::getLocalString("HelpInfo1"), CommonHelper::getLocalString("MainFont"), titleWidth*0.6f);
    labelHelpInfo1->setAlignment(TextHAlignment::CENTER);
    labelHelpInfo1->setColor(textColor);
    labelHelpInfo1->enableOutline(Color4B::GRAY, 2);
    labelHelpInfo1->setPosition(visibleSize.width*0.5f, visibleSize.height*0.7f);
    labelHelpInfo1->setMaxLineWidth(size.width*0.8f);
    this->addChild(labelHelpInfo1);
    
    labelHelpInfo2 = Label::createWithTTF(CommonHelper::getLocalString("HelpInfo2"), CommonHelper::getLocalString("MainFont")/*"minicatoon.ttf"*/, titleWidth*0.6f);
    labelHelpInfo2->setAlignment(TextHAlignment::CENTER);
    labelHelpInfo2->setColor(textColor);
    labelHelpInfo2->enableOutline(Color4B::GRAY, 2);
    labelHelpInfo2->setPosition(visibleSize.width*0.5f, visibleSize.height*0.45f);
    labelHelpInfo2->setMaxLineWidth(size.width*0.8f);
    this->addChild(labelHelpInfo2);
    
    float btnWidth = size.width*0.4f;
    float btnHeight = size.height*0.12f;
    startBtn = ColorButton::create(CommonHelper::getLocalString("Start"), btnWidth, btnHeight, visibleSize.width*0.4f, visibleSize.height*(-0.08f), bgColor, textColor);
    layerColorBG->addChild(startBtn);

    
    return true;
}

bool HelpLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return true;
}
void HelpLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
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
    }
}
void HelpLayer::clickStartBtn()
{
    log("clickStartBtn");
    SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
    MainLayer* mainLayer = dynamic_cast<MainLayer*>(this->getParent());
    if(mainLayer)
        mainLayer->endHelpLayer();
}