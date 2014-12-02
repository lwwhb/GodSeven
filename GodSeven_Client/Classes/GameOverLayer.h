//
//  GameOverLayer.h
//  SkipSeven
//
//  Created by wang haibo on 14-9-23.
//
//

#ifndef __SkipSeven__GameOverLayer__
#define __SkipSeven__GameOverLayer__

#include "cocos2d.h"
#include "ColorButton.h"
class GameOverLayer : public cocos2d::Layer
{
public:
    static GameOverLayer* create(bool success, float totalTime, int score, const cocos2d::Color4B& bgColor, const cocos2d::Color3B& textColor);
    
    void setEnable(bool bEnable);
protected:
    virtual bool initWithColor(bool success, float totalTime, int score, const cocos2d::Color4B& bgColor, const cocos2d::Color3B& textColor);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    
    void clickRestartBtn();
    void clickRankBtn();
    void clickShareBtn();
private:
    cocos2d::LayerColor*    layerColorBG;
    cocos2d::Color4B        colorBG;
    cocos2d::Label*         labelTitle;
    ColorButton*            restartBtn;
    ColorButton*            rankBtn;
    ColorButton*            shareBtn;
    bool                    m_bEnable;
};

#endif /* defined(__SkipSeven__GameOverLayer__) */
