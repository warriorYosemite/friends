//
//  LevelDetails.cpp
//  Friends
//
//  Created by Machintosh on 18/10/16.
//
//

#include "LevelDetails.hpp"
#include "constant.h"
#include "QuizGame.hpp"

using namespace cocos2d::extension;
using namespace std;

LevelDetails* LevelDetails::createLayer()
{
    
    // 'layer' is an autorelease object
    auto layer = LevelDetails::create();
    
    
    // return the layer
    return layer;
}

// on "init" you need to initialize your instance
bool LevelDetails::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    return true;
}

void LevelDetails::onEnter()
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
    m_keyboardListener->onKeyReleased = CC_CALLBACK_2(LevelDetails::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_keyboardListener, this);
    
    setLevelDetailsList();
    
    createBackground();
    
    createTableView();
    
//    runEnterAnimation();
}

void LevelDetails::createTableView(){
    
    tableWidth = this->getContentSize().width;
    tableHeight = this->getContentSize().height;
    
    
    m_tableView = cocos2d::extension::TableView::create(this, Size(tableWidth,tableHeight));
    m_tableView->setDirection(cocos2d::extension::TableView::Direction::VERTICAL);
    m_tableView->setPosition(Vec2(0,0));
    m_tableView->setDelegate(this);
    m_tableView->setVerticalFillOrder(cocos2d::extension::TableView::VerticalFillOrder::TOP_DOWN);
    this->addChild(m_tableView);
    
}

void LevelDetails::setLevelDetailsList(){
    
    LevelDetailStruct* item1 = new LevelDetailStruct();
    item1->m_level = "Level 1";
    item1->m_levelName = "The Pilot";
    item1->m_totalQestions = 5;
    item1->isLocked = false;
    m_levelDetails.push_back(item1);
    
    LevelDetailStruct* item2 = new LevelDetailStruct();
    item2->m_level = "Level 2";
    item2->m_levelName = "The One with the Thanksgiving";
    item2->m_totalQestions = 10;
    m_levelDetails.push_back(item2);
    
    LevelDetailStruct* item3 = new LevelDetailStruct();
    item3->m_level = "Level 3";
    item3->m_levelName = "The One with Mac and C.H.E.E.S.E";
    item3->m_totalQestions = 15;
    m_levelDetails.push_back(item3);
    
    LevelDetailStruct* item4 = new LevelDetailStruct();
    item4->m_level = "Level 4";
    item4->m_levelName = "The One Where They All Turn Thirty";
    item4->m_totalQestions = 30;
    m_levelDetails.push_back(item4);
    
    LevelDetailStruct* item5 = new LevelDetailStruct();
    item5->m_level = "Level 5";
    item5->m_levelName = "The One with Unagi";
    item5->m_totalQestions = 50;
    m_levelDetails.push_back(item5);
    
    LevelDetailStruct* item6 = new LevelDetailStruct();
    item6->m_level = "Level 6";
    item6->m_levelName = "The One With the Dinosaurs";
    item6->m_totalQestions = 75;
    m_levelDetails.push_back(item6);
    
    LevelDetailStruct* item7 = new LevelDetailStruct();
    item7->m_level = "Level 7";
    item7->m_levelName = "The Last One";
    item7->m_totalQestions = 100;
    m_levelDetails.push_back(item7);
    
    
}
TableViewCell* LevelDetails::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell *cell = table->dequeueCell();
    if (cell)
    {
        cell->removeAllChildrenWithCleanup(true);
    }
    else
    {
        cell = new TableViewCell();
        cell->autorelease();
        
    }
    
    std::string level = m_levelDetails.at(idx)->m_level;
    std::string levelName = m_levelDetails.at(idx)->m_levelName;
    int questionsDone = m_levelDetails.at(idx)->m_currentQuestions;
    int totalQuestions = m_levelDetails.at(idx)->m_totalQestions;
    bool isLocked = m_levelDetails.at(idx)->isLocked;
    
    Scale9Sprite* cellBg = Scale9Sprite::create("board_9patch.png");
    cellBg->setContentSize(Size(tableWidth * 0.95, rowHeight * 0.9));
    cellBg->setPosition(Vec2(tableWidth * 0.5, rowHeight * 0.5));
    cell->addChild(cellBg);
    
    Label* nameLabel = Label::createWithTTF(level, FONT_DOSIS, 35);
    nameLabel->setAnchorPoint(Vec2(0.5, 0.5));
    nameLabel->setColor(Color3B::BLACK);
    nameLabel->setPosition(Vec2(cellBg->getContentSize().width * 0.5, cellBg->getContentSize().height * 0.8));
    cellBg->addChild(nameLabel);
    
    
    if (isLocked){
    
        Sprite* lockImage = Sprite::create(ICON_PATH"lock.png");
        lockImage->setPosition(Vec2(lockImage->getContentSize().width, cellBg->getContentSize().height * 0.5));
        cellBg->addChild(lockImage);
    }
    
    Label* cellDetail = Label::createWithTTF(levelName, FONT_ARIAL, 25);
    cellDetail->setPosition(Vec2(cellBg->getContentSize().width * 0.5, cellBg->getContentSize().height * 0.5));
    cellDetail->setColor(Color3B::BLACK);
    cellBg->addChild(cellDetail);
    
    std::string questionProgress = "Progress  " + std::to_string(questionsDone) + "/" + std::to_string(totalQuestions);
    
    Label* qProgressLabel = Label::createWithTTF(questionProgress, FONT_ARIAL, 25);
    qProgressLabel->setPosition(Vec2(cellBg->getContentSize().width * 0.5, cellBg->getContentSize().height * 0.2));
    qProgressLabel->setColor(Color3B::BLACK);
    cellBg->addChild(qProgressLabel);
    
    if (!isLocked){
    
        qProgressLabel->setColor(Color3B(0,128,0));
    }
    
    return cell;
}

Size LevelDetails::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    rowHeight = tableHeight / 7;
    return Size(tableWidth, rowHeight);
}

void LevelDetails::tableCellTouched(TableView *table, TableViewCell *cell)
{
    CCLOG("CELL %zd ", cell->getIdx());
    int cellId = cell->getIdx();
    
    bool isLocked = m_levelDetails.at(cellId)->isLocked;
    if (isLocked){
    
        //do nothing as that level is locked for user
        CCLOG("returning as level is locked");
        return;
    }else{
    
        CCLOG("calling game scene from level detail layer");
        Scene* gameScene = QuizGame::createGameScene();
        Director::getInstance()->replaceScene(gameScene);
    }
    
}

ssize_t LevelDetails::numberOfCellsInTableView(TableView *table)
{
    int size = (int)m_levelDetails.size();
    return size;
}

void LevelDetails::createBackground(){
    
    m_backgroundLayer = LayerColor::create(Color4B(0,0,0,255), visibleSize.width, visibleSize.height);
    m_backgroundLayer->setPosition(Vec2(0,0));
    this->addChild(m_backgroundLayer);
    
}

void LevelDetails::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent)
{
    pEvent->stopPropagation();
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        this->removeFromParentAndCleanup(true);
    }
}

void LevelDetails::onExit()
{
    CCLOG("On exit Level Details called");
    listener->release();
    
    Layer::onExit();
    
}
