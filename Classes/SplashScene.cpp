#include "SplashScene.h"
#include "constant.h"
#include "MainScene.hpp"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    isSplash = true;
    
    return true;
}


void SplashScene::onEnter()
{
    Layer::onEnter();
    
    LayerColor* layerBg = LayerColor::create(Color4B(20,20,20,180), visibleSize.width, visibleSize.height);
    layerBg->setPosition(Vec2(0,0));
    this->addChild(layerBg);
    
    m_logo = Sprite::create("splashTwo.jpg");
    m_logo->setAnchorPoint(Vec2(0.5,1));
    m_logo->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height));
    m_logo->setOpacityModifyRGB(true);
    m_logo->setOpacity(0);
    this->addChild(m_logo);

    runLogoAnimation();
}

void SplashScene::runLogoAnimation(){
    
    CallFunc* callFun1 = CallFunc::create([=]{
        m_logo->runAction(FadeIn::create(4));
        
    });
    
    CallFunc* callFun3 = CallFunc::create([=]{
        
        isSplash = false;
        auto mainScene = MainScene::createScene();
        Director::getInstance()->replaceScene(mainScene);
        
    });

    //delay is implemented so as the current implementation will complete and then the main scene will populate
    this->runAction(Spawn::create(callFun1,NULL));
    this->runAction(Sequence::create(DelayTime::create(6),callFun3, NULL));
    
}

void SplashScene::onExit()
{
    Layer::onExit();
}

void SplashScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
