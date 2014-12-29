//
//  MainLayer.cpp
//  SkipSeven
//
//  Created by wang haibo on 14-9-23.
//
//

#include "MainLayer.h"
#include "CardSprite.h"
#include "SimpleAudioEngine.h"
#include "CommonHelper.h"
#include "NativeBridge.h"
USING_NS_CC;
using namespace CocosDenshion;
#define MAX_WAIT_TIME 5

Scene* MainLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = MainLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(COLOR_BG) )
    {
        return false;
    }
    
    auto touchListener=EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan=CC_CALLBACK_2(MainLayer::onTouchBegan,this);
    touchListener->onTouchEnded=CC_CALLBACK_2(MainLayer::onTouchEnded,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
    auto keyboardListener=EventListenerKeyboard::create();
    keyboardListener->onKeyReleased=CC_CALLBACK_2(MainLayer::onKeyReleased,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,this);
    
    beginX = beginY = endX = endY = -1;
    
    cocos2d::Size visibleSize = Director::getInstance()->getWinSize();
    m_fCardWidth = visibleSize.width*0.6f;
    m_fCardHeight = m_fCardWidth;
    m_BirthPoint = Vec2(visibleSize.width*0.5f, visibleSize.height*0.5f);
    
    addMenuLayer();
    return true;
}

void MainLayer::onEnter()
{
    Layer::onEnter();
    scheduleUpdate();
}
void MainLayer::onExit()
{
    unscheduleUpdate();
    Layer::onExit();
}
void MainLayer::update(float delta)
{
    if (m_bOver)
        return;
    if (m_bStart) {
        m_fTotalTime += delta;
        m_fSecondTimer += delta;
        if(m_fSecondTimer < MAX_WAIT_TIME)
        {
            adjustCurCardColor(m_fSecondTimer);
        }
        else
        {
            m_fSecondTimer = 0.0f;
            gameOver();
        }
    }
}
void MainLayer::gameStart()
{
    removeCardSprite(m_pCurCard);
    addCardSprite();
    log("gameStart");
    if(m_pLabelStart)
    {
        m_pLabelStart->stopAllActions();
        EaseSineOut* easeOut1 = EaseSineOut::create(ScaleTo::create(0.3f, 2));
        EaseSineOut* easeOut2 = EaseSineOut::create(FadeOut::create(0.3f));
        Spawn* spawn = Spawn::createWithTwoActions(easeOut1, easeOut2);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MainLayer::removeStartLabel,this));
        Sequence* sequence = Sequence::createWithTwoActions(spawn, callFunc);
        m_pLabelStart->runAction(sequence);
    }
    m_bStart = true;
}
void MainLayer::removeStartLabel()
{
    if(m_pLabelStart)
    {
        this->removeChild(m_pLabelStart);
        m_pLabelStart = nullptr;
    }
}
void MainLayer::adjustCurCardColor(float escapeTime)
{
    //log("adjustCardColor");
    float percent = m_fSecondTimer/MAX_WAIT_TIME;
    if(m_pCurCard)
        m_pCurCard->setOpacity(255*(1.0f - percent));
}
bool MainLayer::checkValidity(bool notSeven)
{
    bool ret = false;
    std::string strNum = String::createWithFormat("%d",m_nCurrentNum)->getCString();
    if(notSeven)
    {
        if((m_nCurrentNum % 7 != 0) && strNum.find("7") == std::string::npos)
            ret = true;
        else
            ret = false;
    }
    else
    {
        if((m_nCurrentNum % 7 == 0) || strNum.find("7") != std::string::npos)
            ret = true;
        else
            ret = false;
    }
    return ret;
}
void MainLayer::gameOver()
{
    NativeBridge::getInstance()->showAdsView();
    m_bOver = true;
    log("gameOver");
    removeStartLabel();
    removeCardSprite(m_pCurCard);
    bool newRecord = isNewRecord();
    addGameOverLayer(newRecord);
}
bool MainLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    if(!m_bStart || m_bOver)
        return true;
    cocos2d::Point touchPoint = touch->getLocation();
    touch->getLocationInView();
    beginX = touchPoint.x;
    beginY = touchPoint.y;
    
    return true;
}
void MainLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    if(!m_bStart || m_bOver || beginY < 0)
        return;
    
    cocos2d::Point touchPoint=touch->getLocation();
    endX = touchPoint.x;
    endY = touchPoint.y;

    if(endY < beginY)
        doDown();
    else if(endY > beginY+10)
        doUp();
    else
        doClick();
}
void MainLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event)
{
    Director::getInstance()->end();
}
void MainLayer::doUp()
{
    log("doUp");
    if (checkValidity(false))
    {
//        ////----debug
//        //截屏后的回调函数
//        auto callback = [&](const std::string& fullPath){
//            CCLOG("Image saved %s", fullPath.c_str());
//        };
//        
//        //调用Director的截屏功能
//        CommonHelper::screenshot("MainLayer3.png", callback);
//        ///----

        SimpleAudioEngine::getInstance()->playEffect("god7.wav");
        caculateRecord();
        m_fSecondTimer = 0.0f;
        endCardSprite(true, m_pCurCard);
        addCardSprite();
    }
    else
        gameOver();
}

void MainLayer::doDown()
{
    log("doDown");
    if (checkValidity(true))
    {
//        ////----debug
//        //截屏后的回调函数
//        auto callback = [&](const std::string& fullPath){
//            CCLOG("Image saved %s", fullPath.c_str());
//        };
//        
//        //调用Director的截屏功能
//        CommonHelper::screenshot("MainLayer2.png", callback);
//        ///----

        
        SimpleAudioEngine::getInstance()->playEffect("no7.wav");
        caculateRecord();
        m_fSecondTimer = 0.0f;
        endCardSprite(false, m_pCurCard);
        addCardSprite();
    }
    else
        gameOver();
}

void MainLayer::doClick()
{
    log("doClick");
    if (checkValidity(true))
    {
        SimpleAudioEngine::getInstance()->playEffect("no7.wav");
        caculateRecord();
        m_fSecondTimer = 0.0f;
        endCardSprite(false, m_pCurCard);
        addCardSprite();
    }
    else
        gameOver();
}

void MainLayer::reset()
{
    this->stopAllActions();
    m_fFrezonTime = 0.5f;
    m_bStart = false;
    m_bOver = false;
    m_fSecondTimer = 0.0f;
    m_fTotalTime = 0.0f;
    m_nScore = 0;
    m_nCurrentNum = 0;
    m_pLabelStart = Label::createWithTTF(CommonHelper::getLocalString("Start"), CommonHelper::getLocalString("MainFont"), m_fCardWidth*0.35f);
    if(m_pLabelStart)
    {
        m_pLabelStart->setPosition(m_BirthPoint);
        m_pLabelStart->enableOutline(Color4B::GRAY, 4);
        m_pLabelStart->setColor(COLOR_TEXT);
        this->addChild(m_pLabelStart, 10);
    }
    DelayTime* delatTime = DelayTime::create(m_fFrezonTime);
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MainLayer::gameStart,this));
    Sequence* sequence = Sequence::createWithTwoActions(delatTime, callFunc);
    this->runAction(sequence);
    NativeBridge::getInstance()->hideAdsView();
}

bool MainLayer::isNewRecord()
{
    int maxScore = UserDefault::getInstance()->getIntegerForKey("MaxScore", 0);
    if (m_nScore > maxScore) {
        UserDefault::getInstance()->setIntegerForKey("MaxScore", m_nScore);
        UserDefault::getInstance()->flush();
        return true;
    }
    return false;
}
void MainLayer::caculateRecord()
{
    m_nScore = m_nCurrentNum*(10 + (MAX_WAIT_TIME - m_fSecondTimer)*(MAX_WAIT_TIME - m_fSecondTimer));
}
void MainLayer::addCardSprite()
{
    m_pCurCard = CardSprite::create(m_nCurrentNum+1, m_fCardWidth, m_fCardHeight, m_BirthPoint.x, m_BirthPoint.y, COLOR_BTN_BG, COLOR_NUM);
    if(m_pCurCard)
    {
        this->addChild(m_pCurCard);
        m_nCurrentNum++;
        std::string strNum = String::createWithFormat("%d",m_nCurrentNum)->getCString();
        size_t length = strNum.length();
        if(length > 3)
        {
            float scale = 1.0f - (length - 3)*0.1f;
            m_pCurCard->getCardNumberLabel()->setScale(scale);
        }
    }
}
void MainLayer::beginCardSprite()
{
}
void MainLayer::endCardSprite(bool bSuccess, CardSprite* removeCard)
{
    if(m_pCurCard)
    {
        m_pCurCard->setZOrder(1);
        if(bSuccess)
        {
            Vec2 cardPos = m_pCurCard->getPosition();
            
            Sprite* godSprite = Sprite::create("god.png");
            if(godSprite)
            {
                godSprite->setPosition(m_fCardWidth*0.5f, m_fCardHeight*0.5f);
                godSprite->setScale(m_fCardWidth*1.6f/godSprite->getContentSize().width, m_fCardHeight*1.6f/godSprite->getContentSize().height);
                m_pCurCard->addChild(godSprite);
            }
            m_pCurCard->enableCardNumberCascadeOpacity(false);
            EaseSineOut* easeOut1 = EaseSineOut::create(MoveTo::create(1.0f, Vec2(cardPos.x,cardPos.y + 350)));
            EaseSineOut* easeOut2 = EaseSineOut::create(FadeOut::create(1.0f));
            Spawn* spawn = Spawn::createWithTwoActions(easeOut1, easeOut2);
            CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MainLayer::removeCardSprite,this, removeCard));
            Sequence* sequence = Sequence::createWithTwoActions(spawn, callFunc);
            m_pCurCard->runAction(sequence);
            
            Label* numLabel = m_pCurCard->getCardNumberLabel();
            if(numLabel)
            {
                Action* scale = ScaleTo::create(0.5f, 1.2f);
                godSprite->runAction(scale);
                numLabel->runAction(scale);
            }
        }
        else
        {
            float deltaX = (endX - beginX)*5.0f;
            float deltaY = (endY - beginY)*5.0f;
            float length = Vec2(deltaX, deltaY).length();
            if(abs(deltaY)<500.0f)
                deltaY -= 500.0f;
            float deltaRot = 0.0f;
            if(beginX > m_BirthPoint.x)
            {
                deltaRot =  length * 0.5f;
            }
            else if(beginX < m_BirthPoint.x)
            {
                deltaRot =  -length * 0.5f;
            }
            else
            {
                if(endX > 0)
                {
                    deltaRot =  length * 0.5f;
                }
                else if(endX < 0)
                {
                    deltaRot =  -length * 0.5f;
                }
            }
            m_pCurCard->enableCardNumberCascadeOpacity(true);
            EaseSineOut* easeOut1 = EaseSineOut::create(MoveBy::create(1.0f, Vec2(deltaX, deltaY)));
            EaseSineOut* easeOut2 = EaseSineOut::create(FadeOut::create(0.5f));
            EaseSineOut* easeOut3 = EaseSineOut::create(RotateBy::create(1.0f, deltaRot));
            Spawn* spawn = Spawn::create(easeOut1, easeOut2, easeOut3, NULL);
            CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MainLayer::removeCardSprite,this, removeCard));
            Sequence* sequence = Sequence::createWithTwoActions(spawn, callFunc);
            m_pCurCard->runAction(sequence);
        }
    }
}
void MainLayer::removeCardSprite(CardSprite* removeCard)
{
    if(removeCard)
    {
        this->removeChild(removeCard);
        removeCard = nullptr;
    }
}

void MainLayer::addMenuLayer()
{
    if(!m_pMainMenuLayer)
    {
        m_pMainMenuLayer = MainMenuLayer::create(COLOR_BTN_BG, COLOR_TEXT);
        m_pMainMenuLayer->setPosition(Vec2(0,-100));
        m_pMainMenuLayer->setOpacity(0);
        this->addChild(m_pMainMenuLayer, 20);

        EaseSineOut* easeOut1 = EaseSineOut::create(MoveTo::create(0.5f, Vec2::ZERO));
        EaseSineOut* easeOut2 = EaseSineOut::create(FadeIn::create(1.0f));
        Spawn* spawn = Spawn::createWithTwoActions(easeOut1, easeOut2);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MainLayer::beginMenuLayer,this));
        Sequence* sequence = Sequence::createWithTwoActions(spawn, callFunc);
        m_pMainMenuLayer->runAction(sequence);
    }
}
void MainLayer::beginMenuLayer()
{
    if(m_pMainMenuLayer)
    {
        m_pMainMenuLayer->stopAllActions();
        m_pMainMenuLayer->setEnable(true);
    }
}
void MainLayer::endMenuLayer(bool start)
{
    if(m_pMainMenuLayer)
    {
        m_pMainMenuLayer->setEnable(false);
        EaseSineOut* easeOut1 = EaseSineOut::create(MoveTo::create(0.5f, Vec2(0,100)));
        EaseSineOut* easeOut2 = EaseSineOut::create(FadeOut::create(0.5f));
        Spawn* spawn = Spawn::createWithTwoActions(easeOut1, easeOut2);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MainLayer::removeMenuLayer,this, start));
        Sequence* sequence = Sequence::createWithTwoActions(spawn, callFunc);
        m_pMainMenuLayer->runAction(sequence);
    }

}
void MainLayer::removeMenuLayer(bool start)
{
    if(m_pMainMenuLayer)
    {
        m_pMainMenuLayer->stopAllActions();
        this->removeChild(m_pMainMenuLayer);
        m_pMainMenuLayer = nullptr;
        if(start)
            reset();
    }
}
void MainLayer::addGameOverLayer(bool bNewRecord)
{
    if(!m_pGameOverLayer)
    {
        if(bNewRecord)
        {
            SimpleAudioEngine::getInstance()->playEffect("win.wav");
            m_pGameOverLayer = GameOverLayer::create(true, m_nCurrentNum, m_fTotalTime, m_nScore, COLOR_LAYER_BG_SUCCESSED, COLOR_TEXT);
        }
        else
        {
            SimpleAudioEngine::getInstance()->playEffect("lose.wav");
            m_pGameOverLayer = GameOverLayer::create(false, m_nCurrentNum, m_fTotalTime, m_nScore, COLOR_LAYER_BG_FAILED, COLOR_TEXT);
        }
        m_pGameOverLayer->setPosition(Vec2(0, -100));
        m_pGameOverLayer->setOpacity(0);
        this->addChild(m_pGameOverLayer, 20);
        
        EaseSineOut* easeOut1 = EaseSineOut::create(MoveTo::create(0.5f, Vec2::ZERO));
        EaseSineOut* easeOut2 = EaseSineOut::create(FadeIn::create(1.0f));
        Spawn* spawn = Spawn::createWithTwoActions(easeOut1, easeOut2);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MainLayer::beginGameOverLayer,this));
        Sequence* sequence = Sequence::createWithTwoActions(spawn, callFunc);
        m_pGameOverLayer->runAction(sequence);
    }
}
void MainLayer::beginGameOverLayer()
{
    if(m_pGameOverLayer)
    {
        m_pGameOverLayer->stopAllActions();
        m_pGameOverLayer->setEnable(true);
    }
}
void MainLayer::endGameOverLayer(bool restart)
{
    if(m_pGameOverLayer)
    {
        m_pGameOverLayer->setEnable(false);
        EaseSineOut* easeOut1 = EaseSineOut::create(MoveTo::create(0.5f, Vec2(0,100)));
        EaseSineOut* easeOut2 = EaseSineOut::create(FadeOut::create(0.5f));
        Spawn* spawn = Spawn::createWithTwoActions(easeOut1, easeOut2);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MainLayer::removeGameOverLayer,this, restart));
        Sequence* sequence = Sequence::createWithTwoActions(spawn, callFunc);
        m_pGameOverLayer->runAction(sequence);
    }
}
void MainLayer::removeGameOverLayer(bool restart)
{
    if(m_pGameOverLayer)
    {
        m_pGameOverLayer->stopAllActions();
        this->removeChild(m_pGameOverLayer);
        m_pGameOverLayer = nullptr;
        if(restart)
            reset();
    }
}

void MainLayer::addRankLayer()
{
    if(!m_pRankLayer)
    {
        m_pRankLayer = RankLayer::create(m_nScore, COLOR_LAYER_BG_SUCCESSED, COLOR_TEXT);
        m_pRankLayer->setPosition(Vec2(0, -100));
        m_pRankLayer->setOpacity(0);
        this->addChild(m_pRankLayer, 20);
        
        EaseSineOut* easeOut1 = EaseSineOut::create(MoveTo::create(0.5f, Vec2::ZERO));
        EaseSineOut* easeOut2 = EaseSineOut::create(FadeIn::create(1.0f));
        Spawn* spawn = Spawn::createWithTwoActions(easeOut1, easeOut2);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MainLayer::beginRankLayer,this));
        Sequence* sequence = Sequence::createWithTwoActions(spawn, callFunc);
        m_pRankLayer->runAction(sequence);
    }

}
void MainLayer::beginRankLayer()
{
    if(m_pRankLayer)
    {
        m_pRankLayer->stopAllActions();
        m_pRankLayer->setEnable(true);
    }
}
void MainLayer::endRankLayer()
{
    if(m_pRankLayer)
    {
        m_pRankLayer->setEnable(false);
        EaseSineOut* easeOut1 = EaseSineOut::create(MoveTo::create(0.5f, Vec2(0,100)));
        EaseSineOut* easeOut2 = EaseSineOut::create(FadeOut::create(0.5f));
        Spawn* spawn = Spawn::createWithTwoActions(easeOut1, easeOut2);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MainLayer::removeRankLayer,this));
        Sequence* sequence = Sequence::createWithTwoActions(spawn, callFunc);
        m_pRankLayer->runAction(sequence);
    }

}
void MainLayer::removeRankLayer()
{
    if(m_pRankLayer)
    {
        m_pRankLayer->stopAllActions();
        this->removeChild(m_pRankLayer);
        m_pRankLayer = nullptr;
        reset();
    }
}
void MainLayer::addHelpLayer()
{
    if(!m_pHelpLayer)
    {
        m_pHelpLayer = HelpLayer::create(COLOR_BTN_BG, COLOR_TEXT);
        m_pHelpLayer->setPosition(Vec2(0, -100));
        m_pHelpLayer->setOpacity(0);
        this->addChild(m_pHelpLayer, 20);
        
        EaseSineOut* easeOut1 = EaseSineOut::create(MoveTo::create(0.5f, Vec2::ZERO));
        EaseSineOut* easeOut2 = EaseSineOut::create(FadeIn::create(1.0f));
        Spawn* spawn = Spawn::createWithTwoActions(easeOut1, easeOut2);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MainLayer::beginHelpLayer,this));
        Sequence* sequence = Sequence::createWithTwoActions(spawn, callFunc);
        m_pHelpLayer->runAction(sequence);
    }
}
void MainLayer::beginHelpLayer()
{
    if(m_pHelpLayer)
    {
        m_pHelpLayer->stopAllActions();
        m_pHelpLayer->setEnable(true);
    }
}
void MainLayer::endHelpLayer()
{
    if(m_pHelpLayer)
    {
        m_pHelpLayer->setEnable(false);
        EaseSineOut* easeOut1 = EaseSineOut::create(MoveTo::create(0.5f, Vec2(0,100)));
        EaseSineOut* easeOut2 = EaseSineOut::create(FadeOut::create(0.5f));
        Spawn* spawn = Spawn::createWithTwoActions(easeOut1, easeOut2);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MainLayer::removeHelpLayer,this));
        Sequence* sequence = Sequence::createWithTwoActions(spawn, callFunc);
        m_pHelpLayer->runAction(sequence);
    }
}
void MainLayer::removeHelpLayer()
{
    if(m_pHelpLayer)
    {
        m_pHelpLayer->stopAllActions();
        this->removeChild(m_pHelpLayer);
        m_pHelpLayer = nullptr;
        reset();
    }
}