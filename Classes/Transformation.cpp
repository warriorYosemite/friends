//
//  Transformation.cpp
//  Friends
//
//  Created by Machintosh on 19/10/16.
//
//

#include "Transformation.hpp"
#include "constant.h"

using namespace cocos2d::extension;
using namespace std;

#define MAIN_TABLE_VIEW_TAG                         300
#define CELL_TABLE_VIEW_TAG                         301

Transformation* Transformation::createLayer()
{
    
    // 'layer' is an autorelease object
    auto layer = Transformation::create();
    
    
    // return the layer
    return layer;
}

// on "init" you need to initialize your instance
bool Transformation::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    return true;
}

void Transformation::onEnter()
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
    m_keyboardListener->onKeyReleased = CC_CALLBACK_2(Transformation::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_keyboardListener, this);
    
    fillTransformationVector();
    
    createBackground();
    
    createTableView();
}


void Transformation::createTableView(){
    
    tableWidth = this->getContentSize().width;
    tableHeight = this->getContentSize().height;
    
    
    m_tableView = cocos2d::extension::TableView::create(this, Size(tableWidth,tableHeight));
    m_tableView->setDirection(cocos2d::extension::TableView::Direction::VERTICAL);
    m_tableView->setPosition(Vec2(0,0));
    m_tableView->setDelegate(this);
    m_tableView->setTag(MAIN_TABLE_VIEW_TAG);
    m_tableView->setVerticalFillOrder(cocos2d::extension::TableView::VerticalFillOrder::TOP_DOWN);
    this->addChild(m_tableView);
    
}

TableViewCell* Transformation::tableCellAtIndex(TableView *table, ssize_t idx)
{
    int tag = table->getTag();
    
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
    
    
    if (tag == CELL_TABLE_VIEW_TAG){
        
        
        Label* nameLabel = Label::createWithTTF("1", FONT_DOSIS, 30);
        nameLabel->setAnchorPoint(Vec2(0.5, 0.5));
        nameLabel->setColor(Color3B::BLACK);
        nameLabel->setPosition(Vec2(cellRowWidth * 0.5, cellRowHeight * 0.5));
        cell->addChild(nameLabel);
        
    }else{
    
        std::string name = m_transformationVector.at(idx)->m_characterName;
        
        std::transform(name.begin(), name.end(),name.begin(), ::toupper);
        
        Scale9Sprite* cellBg = Scale9Sprite::create("board_9patch.png");
        cellBg->setContentSize(Size(tableWidth * 0.95, rowHeight * 0.9));
        cellBg->setPosition(Vec2(tableWidth * 0.5, rowHeight * 0.5));
        cell->addChild(cellBg);
        
        std::string seasonName = "SEASON  " + std::to_string(idx + 1);
        
        Label* nameLabel = Label::createWithTTF(name, FONT_DOSIS, 30);
        nameLabel->setAnchorPoint(Vec2(0, 0.5));
        nameLabel->setColor(Color3B::BLACK);
        nameLabel->setPosition(Vec2(20, cellBg->getContentSize().height * 0.9));
        cellBg->addChild(nameLabel);
        
        
        cellTableWidth = tableWidth;
        cellTableHeight = rowHeight * 0.85;
        
        cocos2d::extension::TableView* m_cellTableView = cocos2d::extension::TableView::create(this, Size(tableWidth,tableHeight));
        m_cellTableView->setDirection(cocos2d::extension::TableView::Direction::HORIZONTAL);
        m_cellTableView->setTag(CELL_TABLE_VIEW_TAG);
        m_cellTableView->setPosition(Vec2(0,0));
        m_cellTableView->setDelegate(this);
        m_cellTableView->setVerticalFillOrder(cocos2d::extension::TableView::VerticalFillOrder::TOP_DOWN);
        cell->addChild(m_cellTableView);
    
    }
    return cell;
    
    
}

Size Transformation::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    int tag = table->getTag();
    
    if (tag == CELL_TABLE_VIEW_TAG){
    
        cellRowHeight = cellTableHeight;
        cellRowWidth = cellTableWidth/3;
        return Size(cellRowWidth, cellRowHeight);
    
    }else{
    
        rowHeight = tableHeight/3.25;
        return Size(tableWidth, rowHeight);
        
    }
    
    
}

void Transformation::tableCellTouched(TableView *table, TableViewCell *cell)
{
    
    CCLOG("CELL %zd ", cell->getIdx());
    
    int idx = (int)cell->getIdx();
    
}

ssize_t Transformation::numberOfCellsInTableView(TableView *table)
{
    int size;
    int tag = table->getTag();
    
    if (tag == CELL_TABLE_VIEW_TAG){
        
        size = 10;
        
    }else{
    
        size = 6;
    }
    return size;
}

void Transformation::createBackground(){
    
    m_backgroundLayer = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);
    m_backgroundLayer->setPosition(Vec2(0,0));
    this->addChild(m_backgroundLayer);
    
}

void Transformation::fillTransformationVector(){

    for (int i = 0; i <6; i++){
        std::string name = "";
        
        if (i == 0){
        
            name = "Chandler Bing";
            
        }else if (i == 1){
        
            name = "Monica Geller";
            
        }else if (i == 2){
            
            name = "Ross Geller";
            
        }else if (i == 3){
            
            name = "Rachel Green";
            
        }else if (i == 4){
            
            name = "Joey Tribbiani";
            
        }else if (i == 5){
            
            name = "Pheobe Buffay";
            
        }
        
        TransformationStruct* item1 = new TransformationStruct();
        item1->m_characterName = name;
        m_transformationVector.push_back(item1);
    }

}

void Transformation::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent)
{
    pEvent->stopPropagation();
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        
    }
}

void Transformation::onExit()
{
    CCLOG("On exit TransformationLayer called");
    listener->release();
    
    Layer::onExit();
    
}
