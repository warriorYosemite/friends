//
//  MainScene.cpp
//  AimSSB
//
//  Created by Machintosh on 27/09/16.
//
//

#include "MainScene.hpp"
#include "AppDelegate.h"
#include "constant.h"

USING_NS_CC_EXT;
using namespace std;

int curPageIndex;


#define FONT_SIZE_MENUITEM                  27


Scene* MainScene::createScene()
{
    
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    return true;
}

void MainScene::onEnter()
{
    
    Layer::onEnter();
    
    m_keyboardListener = NULL;
    
    visibleSize = Director::getInstance()->getVisibleSize();

    auto dispatcher = Director::getInstance()->getEventDispatcher();
    listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event){
        return true;
    };
    listener->setSwallowTouches(true);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    listener->retain();

    m_keyboardListener = EventListenerKeyboard::create();
    m_keyboardListener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_keyboardListener, this);
    
    createBackground();
//    createMenuItems();
    
    createOtherLayers();

    createUpperLayerItems();
}



void MainScene::createBackground(){

    m_backgroundLayer = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);
    m_backgroundLayer->setPosition(Vec2(0,0));
    this->addChild(m_backgroundLayer);
    
    LayerColor* headerLayer = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height * 0.1);
    headerLayer->setPosition(Vec2(0, visibleSize.height - visibleSize.height * 0.1));
    this->addChild(headerLayer);
    
    Sprite* headerSprite = Sprite::create("name.jpg");
    headerSprite->setPosition(Vec2(headerLayer->getContentSize().width * 0.5, headerLayer->getContentSize().height * 0.5));
    headerSprite->setScale(1.25);
    headerLayer->addChild(headerSprite);
    
    Sprite* listSprite =  Sprite::create("list.png");
    MenuItemSprite* listItem = MenuItemSprite::create(listSprite, listSprite,CC_CALLBACK_1(MainScene::listItemCallback, this));
    
    auto listMenu = Menu::create(listItem, NULL);
    listMenu->setPosition(Vec2(listItem->getContentSize().width, headerLayer->getContentSize().height * 0.5));
    headerLayer->addChild(listMenu);
    

}


void MainScene::createUpperLayerItems(){

    //character1
    Sprite* chandler = Sprite::create(CHARACTERS"chandler.jpg");

    //character2
    Sprite* ross = Sprite::create(CHARACTERS"chandler.jpg");

    auto temp = Sprite::create(CHARACTERS"ross.png");
    ross->setTexture(temp->getTexture());
    
    //character3
    Sprite* joey = Sprite::create(CHARACTERS"chandler.jpg");
    
    auto temp2 = Sprite::create(CHARACTERS"joey.jpg");
    joey->setTexture(temp2->getTexture());
    
    //character4
    Sprite* rachel = Sprite::create(CHARACTERS"chandler.jpg");
    
    auto temp3 = Sprite::create(CHARACTERS"rachel.jpg");
    rachel->setTexture(temp3->getTexture());
    
    //character5
    Sprite* pheobe = Sprite::create(CHARACTERS"chandler.jpg");
    
    auto temp6 = Sprite::create(CHARACTERS"pheobe.jpg");
    pheobe->setTexture(temp6->getTexture());
    
    //character6
    Sprite* monica = Sprite::create(CHARACTERS"chandler.jpg");
    
    auto temp5 = Sprite::create(CHARACTERS"monica.jpg");
    monica->setTexture(temp5->getTexture());
    
    
    MenuItemSprite* chandlerItem = MenuItemSprite::create(chandler, chandler,CC_CALLBACK_1(MainScene::chandlerItemCallback, this));
    chandlerItem->setPosition(Vec2(chandler->getContentSize().width * 0.75, m_upperLayer->getContentSize().height - chandler->getContentSize().height * 0.6));
    
    MenuItemSprite* rossItem = MenuItemSprite::create(ross, ross,CC_CALLBACK_1(MainScene::rossItemCallback, this));
    rossItem->setPosition(Vec2(m_upperLayer->getContentSize().width * 0.5, m_upperLayer->getContentSize().height - ross->getContentSize().height * 0.6));
    
    MenuItemSprite* joeyItem = MenuItemSprite::create(joey, joey,CC_CALLBACK_1(MainScene::joeyItemCallback, this));
    joeyItem->setPosition(Vec2(m_upperLayer->getContentSize().width - joey->getContentSize().width * 0.75, m_upperLayer->getContentSize().height - joey->getContentSize().height * 0.6));
    
    MenuItemSprite* rachelItem = MenuItemSprite::create(rachel, rachel,CC_CALLBACK_1(MainScene::rachelItemCallback, this));
    rachelItem->setPosition(Vec2(rachel->getContentSize().width * 0.75, rachel->getContentSize().height * 0.6));
    
    MenuItemSprite* pheobeItem = MenuItemSprite::create(pheobe, pheobe, CC_CALLBACK_1(MainScene::pheobeItemCallback, this));
    pheobeItem->setPosition(Vec2(m_upperLayer->getContentSize().width * 0.5, pheobe->getContentSize().height * 0.6));
    
    MenuItemSprite* monicaItem = MenuItemSprite::create(monica, monica, CC_CALLBACK_1(MainScene::monicaItemCallback, this));
    monicaItem->setPosition(Vec2(m_upperLayer->getContentSize().width - monica->getContentSize().width * 0.75, monica->getContentSize().height * 0.6));
    
    auto listMenu = Menu::create(chandlerItem,rossItem,joeyItem,rachelItem,pheobeItem, monicaItem,NULL);
    listMenu->setPosition(Vec2(0,0));
    m_upperLayer->addChild(listMenu);
    
}

void MainScene::createOtherLayers(){

    float availableHeight = visibleSize.height - visibleSize.height * 0.1;
    
    m_upperLayer = LayerColor::create(Color4B::BLACK, visibleSize.width, availableHeight * 0.5);
    m_upperLayer->setPosition(Vec2(0, visibleSize.height - visibleSize.height * 0.1 - availableHeight * 0.5));
    this->addChild(m_upperLayer);
    
    DrawNode* horLine1 = DrawNode::create();
    horLine1->setLineWidth(5);
    horLine1->setColor(Color3B::WHITE);
    horLine1->drawLine(Vec2(0, m_upperLayer->getContentSize().height), Vec2(m_upperLayer->getContentSize().width, m_upperLayer->getContentSize().height),Color4F::WHITE);
    m_upperLayer->addChild(horLine1);
    
    DrawNode* horLine = DrawNode::create();
    horLine->setLineWidth(10);
    horLine->setColor(Color3B::WHITE);
    horLine->drawLine(Vec2(0, 0), Vec2(m_upperLayer->getContentSize().width, 0),Color4F::WHITE);
    m_upperLayer->addChild(horLine);
    
    m_middleLayer = LayerColor::create(Color4B::BLACK, visibleSize.width, availableHeight * 0.3);
    m_middleLayer->setPosition(Vec2(0, visibleSize.height - visibleSize.height * 0.1 - availableHeight * 0.8));
    this->addChild(m_middleLayer);

    DrawNode* horLine2 = DrawNode::create();
    horLine2->setLineWidth(10);
    horLine2->setColor(Color3B::WHITE);
    horLine2->drawLine(Vec2(0, 0), Vec2(m_middleLayer->getContentSize().width, 0),Color4F::WHITE);
    m_middleLayer->addChild(horLine2);
    
    m_lowerLayer = LayerColor::create(Color4B::BLACK, visibleSize.width, availableHeight * 0.2);
    m_lowerLayer->setPosition(Vec2(0, visibleSize.height - visibleSize.height * 0.1 - availableHeight * 1));
    this->addChild(m_lowerLayer);

}

void MainScene::createMenuItems(){


}


void MainScene::chandlerItemCallback(Ref* pSender){

    CCLOG("inside chandler");
}

void MainScene::rossItemCallback(Ref* pSender){

    CCLOG("inside ross");

}

void MainScene::joeyItemCallback(Ref* pSender){

    CCLOG("inside joey");
}

void MainScene::rachelItemCallback(Ref* pSender){

    CCLOG("inside rachel");
}

void MainScene::pheobeItemCallback(Ref* pSender){

    CCLOG("inside pheobe");
}

void MainScene::monicaItemCallback(Ref* pSender){

    CCLOG("inside monica");
}


void MainScene::listItemCallback(Ref* pSender){

    CCLOG("inside list item callback");
    SideLayer* sideLayerE = SideLayer::createLayer();
    this->addChild(sideLayerE, 2);

}

void MainScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent)
{
    pEvent->stopPropagation();
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        Director::getInstance()->end();
    }
}

void MainScene::onExit()
{
    CCLOG("On exit Main Scene called");
    listener->release();
    
    Layer::onExit();
    
}