//
//  MainLayer.h
//  SkipSeven
//
//  Created by wang haibo on 14-9-23.
//
//

#ifndef __SkipSeven__MainLayer__
#define __SkipSeven__MainLayer__

#include "cocos2d.h"
#include "CardSprite.h"
#include "GameOverLayer.h"
#include "MainMenuLayer.h"
#include "RankLayer.h"
#include "HelpLayer.h"

#define COLOR_BG cocos2d::Color4B(127,199,239,255)
#define COLOR_BTN_BG cocos2d::Color4B(255,228,96,255)
#define COLOR_LAYER_BG_SUCCESSED cocos2d::Color4B(234,85,41,255)
#define COLOR_LAYER_BG_FAILED cocos2d::Color4B(194,217,78,255)
#define COLOR_TEXT cocos2d::Color3B(255,248,165)
#define COLOR_NUM cocos2d::Color3B(234,85,41)
class MainLayer : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainLayer);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event);
    
    void reset();
private:
    void doUp();
    void doDown();
    void doClick();
    
    void gameStart();
    void removeStartLabel();
    void adjustCurCardColor(float escapeTime);
    bool checkValidity(bool notSeven);
    void gameOver();

    bool isNewRecord();
    void caculateRecord();
public:
    void addCardSprite();
    void beginCardSprite();
    void endCardSprite(bool bSuccess, CardSprite* removeCard);
    void removeCardSprite(CardSprite* removeCard);
    
    void addMenuLayer();
    void beginMenuLayer();
    void endMenuLayer(bool start);
    void removeMenuLayer(bool start);
    
    void addGameOverLayer(bool bNewRecord);
    void beginGameOverLayer();
    void endGameOverLayer(bool restart);
    void removeGameOverLayer(bool restart);
    
    void addRankLayer();
    void beginRankLayer();
    void endRankLayer();
    void removeRankLayer();
    
    void addHelpLayer();
    void beginHelpLayer();
    void endHelpLayer();
    void removeHelpLayer();
private:
    int beginX, beginY, endX, endY;
    CardSprite*      m_pCurCard;
    bool    m_bStart;
    bool    m_bOver;
    float   m_fFrezonTime;
    float   m_fTotalTime;
    float   m_fSecondTimer;
    int     m_nScore;
    int     m_nCurrentNum;

    cocos2d::Vec2       m_BirthPoint;
    float               m_fCardWidth;
    float               m_fCardHeight;
    
    cocos2d::Label*     m_pLabelStart;
    
    GameOverLayer*      m_pGameOverLayer;
    MainMenuLayer*      m_pMainMenuLayer;
    RankLayer*          m_pRankLayer;
    HelpLayer*          m_pHelpLayer;
};


#endif /* defined(__SkipSeven__MainLayer__) */
