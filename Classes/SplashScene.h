#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace cocos2d::ui;

class SplashScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    
    Size visibleSize;
    Sprite* m_logo;
    bool isSplash;
    
    void runLogoAnimation();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);
};

#endif // __SPLASH_SCENE_H__
