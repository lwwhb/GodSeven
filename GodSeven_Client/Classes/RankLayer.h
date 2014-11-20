//
//  RankLayer.h
//  SkipSeven
//
//  Created by wang haibo on 14-9-23.
//
//

#ifndef __SkipSeven__RankLayer__
#define __SkipSeven__RankLayer__

#include "cocos2d.h"
#include "ColorButton.h"
class RankLayer : public cocos2d::Layer
{
public:
    static RankLayer* create(int score, const cocos2d::Color4B& bgColor, const cocos2d::Color3B& textColor);
    
    void setEnable(bool bEnable);
protected:
    virtual bool initWithColor(int score, const cocos2d::Color4B& bgColor, const cocos2d::Color3B& textColor);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    void clickRestartBtn();
private:
    cocos2d::LayerColor*    layerColorBG;
    cocos2d::Color4B        colorBG;
    cocos2d::Label*         labelTitle;
    ColorButton*            restartBtn;
    bool                    m_bEnable;
};


#endif /* defined(__SkipSeven__RankLayer__) */
