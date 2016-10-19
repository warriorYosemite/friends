//
//  Transformation.hpp
//  Friends
//
//  Created by Machintosh on 19/10/16.
//
//

#ifndef Transformation_hpp
#define Transformation_hpp

#include <stdio.h>


#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "extensions/cocos-ext.h"
#include "ui/UIPageView.h"
#include "commonClasses.h"

using namespace cocos2d::ui;
USING_NS_CC;


class Transformation : public cocos2d::Layer,public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
    
    cocos2d::Size visibleSize;
    
    cocos2d::EventListenerTouchOneByOne *listener;
    cocos2d::EventListenerKeyboard *m_keyboardListener;
    
    LayerColor* m_backgroundLayer;

    int m_tableSize;
    float tableWidth;
    float tableHeight;
    float rowHeight;
    
    
    int m_cellTableSize;
    float cellTableWidth;
    float cellTableHeight;
    float cellRowHeight;
    float cellRowWidth;
    
    
    cocos2d::extension::TableView* m_tableView;
//    cocos2d::extension::TableView* m_cellTableView;
    
    std::vector<TransformationStruct*> m_transformationVector;
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Transformation* createLayer();
    
    
    void createBackground();
    void createTableView();
    void fillTransformationVector();
    
    CREATE_FUNC(Transformation);
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent);
    
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
};


#endif /* Transformation_hpp */
