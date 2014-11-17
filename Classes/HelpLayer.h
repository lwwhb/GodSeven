//
//  HelpLayer.h
//  SkipSeven
//
//  Created by wang haibo on 14-9-23.
//
//

#ifndef __SkipSeven__HelpLayer__
#define __SkipSeven__HelpLayer__

#include "cocos2d.h"
#include "ColorButton.h"
class HelpLayer : public cocos2d::Layer
{
public:
    static HelpLayer* create(const cocos2d::Color4B& bgColor, const cocos2d::Color3B& textColor);
    
    void setEnable(bool bEnable);
protected:
    virtual bool initWithColor(const cocos2d::Color4B& bgColor, const cocos2d::Color3B& textColor);

    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    void clickStartBtn();
private:
    cocos2d::LayerColor*    layerColorBG;
    cocos2d::Color4B        colorBG;
    cocos2d::Label*         labelTitle;
    cocos2d::Label*         labelHelpInfo1;
    cocos2d::Label*         labelHelpInfo2;
    ColorButton*            startBtn;
    bool                    m_bEnable;
};

#endif /* defined(__SkipSeven__HelpLayer__) */
