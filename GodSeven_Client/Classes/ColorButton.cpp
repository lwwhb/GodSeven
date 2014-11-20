//
//  ColorButton.cpp
//  GodSeven
//
//  Created by wang haibo on 14-9-26.
//
//

#include "ColorButton.h"
#include "CommonHelper.h"
USING_NS_CC;

ColorButton* ColorButton::create(const std::string& text, int width,int height, int x, int y, const Color4B& bgColor, const Color3B& textColor)
{
    ColorButton* btn = new ColorButton();
    if(btn && btn->init(text, width, height, x, y, bgColor, textColor))
    {
        btn->autorelease();
        
        return btn;
    }
    CC_SAFE_DELETE(btn);
    return nullptr;

}
bool ColorButton::init(const std::string& text,int width,int height, int x, int y, const Color4B& bgColor, const Color3B& textColor)
{
    if(!Sprite::init())
        return false;
    setCascadeOpacityEnabled(true);
    
    LayerColor* layerColorOutline = LayerColor::create(Color4B::GRAY,width,height);
    layerColorOutline->setCascadeOpacityEnabled(true);
    layerColorOutline->setPosition(Vec2(4,-4));
    this->addChild(layerColorOutline);
    
    layerColorBG = LayerColor::create(bgColor,width,height);
    this->addChild(layerColorBG);
    labelText = Label::createWithTTF(text, CommonHelper::getLocalString("MainFont"), height*0.45f);
    labelText->setPosition(Vec2(layerColorBG->getContentSize().width*0.5f,layerColorBG->getContentSize().height*0.5f));
    labelText->setColor(textColor);
    labelText->enableOutline(Color4B::GRAY, 2);
    layerColorBG->addChild(labelText);
    layerColorBG->setCascadeOpacityEnabled(true);
    this->setContentSize(layerColorBG->getContentSize());
    this->setPosition(Vec2(x,y));
    return true;
}