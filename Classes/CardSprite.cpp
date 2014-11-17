//
//  CardSprite.cpp
//  SkipSeven
//
//  Created by wang haibo on 14-9-23.
//
//

#include "CardSprite.h"
USING_NS_CC;

CardSprite* CardSprite::create(int numbers,int width,int height, int x, int y, const Color4B& bgColor, const Color3B& numColor)
{
    CardSprite* sprite = new CardSprite();
    if(sprite && sprite->init(numbers, width, height, x, y, bgColor, numColor))
    {
        sprite->autorelease();
        
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool CardSprite::init(int numbers,int width,int height, int x, int y, const Color4B& bgColor, const Color3B& numColor)
{
    if(!Sprite::init())
        return false;
    
    setCascadeOpacityEnabled(true);
    
    LayerColor* layerColorOutline = LayerColor::create(Color4B::ORANGE, width+14,height+14);
    layerColorOutline->setPosition(Vec2(-14,-14));
    layerColorOutline->setContentSize(Size(width+14, height+14));
    layerColorOutline->setCascadeOpacityEnabled(true);
    this->addChild(layerColorOutline);
    
    layerColorBG = LayerColor::create(bgColor,width-14,height-14);
    labelCardNumber = Label::createWithTTF(String::createWithFormat("%i",numbers)->getCString(), "bank.ttf", width*0.3f);
    labelCardNumber->setPosition(Vec2(layerColorBG->getContentSize().width*0.5f,layerColorBG->getContentSize().height*0.5f));
    labelCardNumber->enableOutline(Color4B::GRAY, 2);
    labelCardNumber->setColor(numColor);
    
    layerColorBG->setCascadeOpacityEnabled(true);
    layerColorBG->addChild(labelCardNumber);
    this->addChild(layerColorBG);
    
    this->setPosition(Vec2(x,y));
    this->setContentSize(Size(width, height));
    return true;
}
void CardSprite::enableCardNumberCascadeOpacity(bool bEnable)
{
    layerColorBG->setCascadeOpacityEnabled(bEnable);
}
cocos2d::Label* CardSprite::getCardNumberLabel() const
{
    return labelCardNumber;
}