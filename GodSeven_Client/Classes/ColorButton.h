//
//  ColorButton.h
//  GodSeven
//
//  Created by wang haibo on 14-9-26.
//
//

#ifndef __GodSeven__ColorButton__
#define __GodSeven__ColorButton__
#include "cocos2d.h"

class ColorButton : public cocos2d::Sprite
{
public:
    static ColorButton* create(const std::string& text,int width,int height, int x, int y, const cocos2d::Color4B& bgColor, const cocos2d::Color3B& textColor);
    bool init(const std::string& text,int width,int height, int x, int y, const cocos2d::Color4B& bgColor, const cocos2d::Color3B& textColor);
    
private:
    cocos2d::Label*         labelText;
    cocos2d::LayerColor*    layerColorBG;
};

#endif /* defined(__GodSeven__ColorButton__) */
