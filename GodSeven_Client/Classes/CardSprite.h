//
//  CardSprite.h
//  SkipSeven
//
//  Created by wang haibo on 14-9-23.
//
//

#ifndef __SkipSeven__CardSprite__
#define __SkipSeven__CardSprite__

#include "cocos2d.h"

class CardSprite : public cocos2d::Sprite
{
public:
    static CardSprite* create(int numbers,int width,int height, int x, int y, const cocos2d::Color4B& bgColor, const cocos2d::Color3B& numColor);
    bool init(int numbers,int width,int height, int x, int y, const cocos2d::Color4B& bgColor, const cocos2d::Color3B& numColor);
    void enableCardNumberCascadeOpacity(bool bEnable);
    cocos2d::Label* getCardNumberLabel() const;
private:
    cocos2d::Label* labelCardNumber;
    cocos2d::LayerColor* layerColorBG;
};

#endif /* defined(__SkipSeven__CardSprite__) */
