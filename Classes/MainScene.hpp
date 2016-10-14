//
//  MainScene.hpp
//  FRIENDS
//
//  Created by Machintosh on 27/09/16.
//
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "extensions/cocos-ext.h"
#include "ui/UIPageView.h"
#include "SideLayer.hpp"
#include "commonClasses.h"


using namespace cocos2d::ui;
USING_NS_CC;

class MainScene : public cocos2d::Layer
{

    cocos2d::Size visibleSize;
    
    cocos2d::EventListenerTouchOneByOne *listener;
    cocos2d::EventListenerKeyboard *m_keyboardListener;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
   static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();

    LayerColor* m_backgroundLayer;
    LayerColor* m_upperLayer;
    LayerColor* m_middleLayer;
    LayerColor* m_lowerLayer;
    
    
    void createBackground();
    void createMenuItems();
    void createOtherLayers();

    void createUpperLayerItems();
    
    void listItemCallback(Ref* pSender);
    
    void chandlerItemCallback(Ref* pSender);
    void rossItemCallback(Ref* pSender);
    void joeyItemCallback(Ref* pSender);
    void rachelItemCallback(Ref* pSender);
    void pheobeItemCallback(Ref* pSender);
    void monicaItemCallback(Ref* pSender);
    
    CREATE_FUNC(MainScene);
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent);
};

#endif /* MainScene_hpp */
