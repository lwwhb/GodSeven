//
//  MainMenuLayer.h
//  GodSeven
//
//  Created by wang haibo on 14-9-28.
//
//

#ifndef __GodSeven__MainMenuLayer__
#define __GodSeven__MainMenuLayer__

#include "cocos2d.h"
#include "ColorButton.h"
class MainMenuLayer : public cocos2d::Layer
{
public:
    static MainMenuLayer* create(const cocos2d::Color4B& bgColor, const cocos2d::Color3B& textColor);
    
    void setEnable(bool bEnable);
protected:
    virtual bool initWithColor(const cocos2d::Color4B& bgColor, const cocos2d::Color3B& textColor);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
private:
    void clickStartBtn();
    void clickHelpBtn();
private:
    cocos2d::Color4B        colorBG;
    cocos2d::Label*         labelTitle;
    ColorButton*            startBtn;
    ColorButton*            helpBtn;
    bool                    m_bEnable;
};

#endif /* defined(__GodSeven__MainMenuLayer__) */
