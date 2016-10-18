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
#include "Mask.h"

USING_NS_CC_EXT;
using namespace std;

int curPageIndex;


#define FONT_SIZE_MENUITEM                  27

#define CELL_BG_TAG                         201
#define CELL_NAME_TAG                       202


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
    countImage = 0;
    
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
    
    createSeasonInfoList();
    
    createBackground();
    
    createOtherLayers();

    createUpperLayerItems();
    
    createTable();
    
    createMiddleLayerContent();
    
    Node::onEnter();
    this->schedule(CC_SCHEDULE_SELECTOR(MainScene::updateCharacterImage), 3.5);

}

void MainScene::updateCharacterImage(float dt){

//    CCLOG("inside image update");
    
    if (playerImage){
        countImage++;
        
        if (countImage > m_flipImages.size() - 1){
            countImage = 0;
        }
        
        std::string imagePath = m_flipImages.at(countImage);
        Sprite* tempImage = Sprite::create(imagePath);
        playerImage->setTexture(tempImage->getTexture());
    }

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

void MainScene::createSeasonInfoList(){
    
    ItemsDetailStruct* item1 = new ItemsDetailStruct();
    item1->m_heading = "SEASON 1";
    item1->m_imageURL = IMAGE_PATH"icon1.jpg";
    m_seasonList.push_back(item1);
    
    ItemsDetailStruct* item2 = new ItemsDetailStruct();
    item2->m_heading = "SEASON 2";
    item2->m_imageURL = IMAGE_PATH"icon2.jpg";
    m_seasonList.push_back(item2);
    
    ItemsDetailStruct* item3 = new ItemsDetailStruct();
    item3->m_heading = "SEASON 3";
    item3->m_imageURL = IMAGE_PATH"icon3.jpg";
    m_seasonList.push_back(item3);
    
    ItemsDetailStruct* item4 = new ItemsDetailStruct();
    item4->m_heading = "SEASON 4";
    item4->m_imageURL = IMAGE_PATH"icon6.jpg";
    m_seasonList.push_back(item4);
    
    ItemsDetailStruct* item5 = new ItemsDetailStruct();
    item5->m_heading = "SEASON 5";
    item5->m_imageURL = IMAGE_PATH"icon5.jpg";
    m_seasonList.push_back(item5);
    
    ItemsDetailStruct* item6 = new ItemsDetailStruct();
    item6->m_heading = "SEASON 6";
    item6->m_imageURL = IMAGE_PATH"icon4.jpg";
    m_seasonList.push_back(item6);
    
    ItemsDetailStruct* item7 = new ItemsDetailStruct();
    item7->m_heading = "SEASON 7";
    item7->m_imageURL = IMAGE_PATH"icon7.jpg";
    m_seasonList.push_back(item7);
    
    ItemsDetailStruct* item8 = new ItemsDetailStruct();
    item8->m_heading = "SEASON 8";
    item8->m_imageURL = IMAGE_PATH"icon8.jpg";
    m_seasonList.push_back(item8);
    
    ItemsDetailStruct* item9 = new ItemsDetailStruct();
    item9->m_heading = "SEASON 9";
    item9->m_imageURL = IMAGE_PATH"icon9.jpg";
    m_seasonList.push_back(item9);
    
    ItemsDetailStruct* item10 = new ItemsDetailStruct();
    item10->m_heading = "SEASON 10";
    item10->m_imageURL = IMAGE_PATH"icon10.jpg";
    m_seasonList.push_back(item10);
    
    
    
    m_flipImages.push_back(FLIP_IMAGES"flip1.jpg");
    m_flipImages.push_back(FLIP_IMAGES"flip2.jpg");
    m_flipImages.push_back(FLIP_IMAGES"flip3.jpeg");
    m_flipImages.push_back(FLIP_IMAGES"flip4.jpg");
    m_flipImages.push_back(FLIP_IMAGES"flip5.jpg");
    m_flipImages.push_back(FLIP_IMAGES"flip6.jpg");
    m_flipImages.push_back(FLIP_IMAGES"flip7.jpg");
    m_flipImages.push_back(FLIP_IMAGES"flip8.jpg");
    m_flipImages.push_back(FLIP_IMAGES"flip9.jpg");
    m_flipImages.push_back(FLIP_IMAGES"flip10.png");
    m_flipImages.push_back(FLIP_IMAGES"flip11.jpg");
    m_flipImages.push_back(FLIP_IMAGES"flip12.jpg");
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
    
    DrawNode* verLine1 = DrawNode::create();
    verLine1->setLineWidth(5);
    verLine1->setColor(Color3B::WHITE);
    verLine1->drawLine(Vec2(m_middleLayer->getContentSize().width*0.5, 0), Vec2(m_middleLayer->getContentSize().width * 0.5, m_middleLayer->getContentSize().height),Color4F::WHITE);
    m_middleLayer->addChild(verLine1);
    
    m_lowerLayer = LayerColor::create(Color4B::BLACK, visibleSize.width, availableHeight * 0.2);
    m_lowerLayer->setPosition(Vec2(0, visibleSize.height - visibleSize.height * 0.1 - availableHeight * 1));
    this->addChild(m_lowerLayer);

}

void MainScene::createMiddleLayerContent(){


    //for save me game
    auto clipper = Mask::getInstance()->getCircularMask(60);
    std::string imagePath = m_flipImages.at(countImage);
    
    playerImage = Sprite::create(imagePath);
    
    int scaleBounds = 130;
    if(playerImage)
    {
        
        float scaleX = scaleBounds/playerImage->getContentSize().width;
        float scaleY = scaleBounds/playerImage->getContentSize().height;
        playerImage->setScale(MIN(scaleX, scaleY));
        clipper->setPosition(Vec2(m_middleLayer->getContentSize().width * 0.62, m_middleLayer->getContentSize().height * 0.735));
        clipper->addChild(playerImage);
        m_middleLayer->addChild(clipper);
        
    }
    
    Label* gameName = Label::createWithTTF("SAVE ME", FONT_AFTON_JAMES, 40);
    gameName->setPosition(Vec2(m_middleLayer->getContentSize().width * 0.85, m_middleLayer->getContentSize().height * 0.9));
    m_middleLayer->addChild(gameName);
    
    std::string description = "Select a character to save and save it till all other characters die.";
    Label* gameDescription = Label::createWithTTF(description, FONT_DOSIS, 20);
    gameDescription->setWidth(m_middleLayer->getContentSize().width * 0.3);
    gameDescription->setPosition(Vec2(m_middleLayer->getContentSize().width * 0.875, m_middleLayer->getContentSize().height * 0.675));
    m_middleLayer->addChild(gameDescription);
    
    UserDefault* userDef =  UserDefault::getInstance();
    int value = userDef->getIntegerForKey(GAME_HIGH_SCORE_KEY_SAVE_GAME, 0);
    
    std::string highScore = "HIGH SCORE :  " + std::to_string(value);
    
    highScoreTextSaveGame = Label::createWithTTF(highScore, FONT_HEADLINE, 19);
    highScoreTextSaveGame->setAnchorPoint(Vec2(0.5, 0.5));
    highScoreTextSaveGame->setPosition(Vec2(m_middleLayer->getContentSize().width * 0.75, m_middleLayer->getContentSize().height * 0.45));
    m_middleLayer->addChild(highScoreTextSaveGame);
    
    int level = userDef->getIntegerForKey(GAME_SAVE_ME_LEVEL, 1);
    
    std::string userLevel = "LEVEL :  " + std::to_string(level);
    
    levelSaveMeGame = Label::createWithTTF(userLevel, FONT_HEADLINE, 19);
    levelSaveMeGame->setAnchorPoint(Vec2(0.5, 0.5));
    levelSaveMeGame->setPosition(Vec2(m_middleLayer->getContentSize().width * 0.75, m_middleLayer->getContentSize().height * 0.35));
    m_middleLayer->addChild(levelSaveMeGame);
    
    Sprite* playButton = Sprite::create("rectangle.png");
    playButton->setScaleY(0.8);
    Label* play = Label::createWithTTF("I wanna Play", FONT_HEADLINE, 25);
    play->setColor(Color3B::BLACK);
    play->setPosition(Vec2(playButton->getContentSize().width * 0.5, playButton->getContentSize().height * 0.5));
    playButton->addChild(play);
    
    
    Sprite* playButtonPressed = Sprite::create("rectangle.png");
    playButtonPressed->setScaleY(0.8);
    playButtonPressed->setScaleX(0.95);
    
    Label* playPressed = Label::createWithTTF("I wanna Play", FONT_HEADLINE, 23);
    playPressed->setColor(Color3B::BLACK);
    playPressed->setPosition(Vec2(playButtonPressed->getContentSize().width * 0.5, playButtonPressed->getContentSize().height * 0.5));
    playButtonPressed->addChild(playPressed);
    
    MenuItemSprite* playItemSaveMe = MenuItemSprite::create(playButton, playButtonPressed, CC_CALLBACK_1(MainScene::playSaveMeCallback, this));
    playItemSaveMe->setPosition(Vec2(m_middleLayer->getContentSize().width* 0.75, playItemSaveMe->getContentSize().height * 0.75));
    
    auto playMenuSaveMe = Menu::create(playItemSaveMe,NULL);
    playMenuSaveMe->setPosition(Vec2(0,0));
    m_middleLayer->addChild(playMenuSaveMe);
    
    
    //for QUIZ GAME
    Label* gameNameQuiz = Label::createWithTTF("FRIENDS QUIZ", FONT_AFTON_JAMES, 40);
    gameNameQuiz->setPosition(Vec2(m_middleLayer->getContentSize().width * 0.25, m_middleLayer->getContentSize().height * 0.9));
    m_middleLayer->addChild(gameNameQuiz);
    
    std::string descriptionQuiz = "Do you think you know it all about F.R.I.E.N.D.S? \n Take this challenge & prove it !";
    Label* quizDescription = Label::createWithTTF(descriptionQuiz, FONT_DOSIS, 21);
    quizDescription->setWidth(m_middleLayer->getContentSize().width * 0.4);
    quizDescription->setPosition(Vec2(m_middleLayer->getContentSize().width * 0.25, m_middleLayer->getContentSize().height * 0.67));
    m_middleLayer->addChild(quizDescription);
    
    int value2 = userDef->getIntegerForKey(GAME_HIGH_SCORE_KEY_QUIZ_GAME, 0);
    
    std::string highScoreQuiz = "HIGH SCORE :  " + std::to_string(value2);
    
    highScoreQuizGame = Label::createWithTTF(highScoreQuiz, FONT_HEADLINE, 19);
    highScoreQuizGame->setAnchorPoint(Vec2(0.5, 0.5));
    highScoreQuizGame->setPosition(Vec2(m_middleLayer->getContentSize().width * 0.25, m_middleLayer->getContentSize().height * 0.45));
    m_middleLayer->addChild(highScoreQuizGame);
    
    
    int levelQuiz = userDef->getIntegerForKey(GAME_QUIZ_LEVEL, 1);
    
    std::string userLevelQuiz = "LEVEL :  " + std::to_string(levelQuiz);
    
    levelQuizGame = Label::createWithTTF(userLevelQuiz, FONT_HEADLINE, 19);
    levelQuizGame->setAnchorPoint(Vec2(0.5, 0.5));
    levelQuizGame->setPosition(Vec2(m_middleLayer->getContentSize().width * 0.25, m_middleLayer->getContentSize().height * 0.35));
    m_middleLayer->addChild(levelQuizGame);
    
    Sprite* playButtonQuiz = Sprite::create("rectangle.png");
    playButtonQuiz->setScaleY(0.8);
    
    Label* playQuiz = Label::createWithTTF("Let's Quiz", FONT_HEADLINE, 25);
    playQuiz->setColor(Color3B::BLACK);
    playQuiz->setPosition(Vec2(playButtonQuiz->getContentSize().width * 0.5, playButtonQuiz->getContentSize().height * 0.5));
    playButtonQuiz->addChild(playQuiz);
    
    
    Sprite* playButtonQuizPressed = Sprite::create("rectangle.png");
    playButtonQuizPressed->setScaleY(0.8);
    playButtonQuizPressed->setScaleX(0.95);
    
    Label* playQuizPressed = Label::createWithTTF("Let's Quiz", FONT_HEADLINE, 23);
    playQuizPressed->setColor(Color3B::BLACK);
    playQuizPressed->setPosition(Vec2(playButtonQuizPressed->getContentSize().width * 0.5, playButtonQuizPressed->getContentSize().height * 0.5));
    playButtonQuizPressed->addChild(playQuizPressed);
    
    MenuItemSprite* playItemQuiz = MenuItemSprite::create(playButtonQuiz,playButtonQuizPressed,CC_CALLBACK_1(MainScene::playQuizCallback, this));
    playItemQuiz->setPosition(Vec2(m_middleLayer->getContentSize().width* 0.25, playItemSaveMe->getContentSize().height * 0.75));
    
    auto playMenuQuiz = Menu::create(playItemQuiz,NULL);
    playMenuQuiz->setPosition(Vec2(0,0));
    m_middleLayer->addChild(playMenuQuiz);
    
    userDef->flush();
}

//#pragma TableView
void MainScene::createTable()
{

    //create Table View within lower layer
    
    tableWidth = m_lowerLayer->getContentSize().width;
    tableHeight = m_lowerLayer->getContentSize().height;
    
    Vec2 tablePosition = Vec2(0,0);
    
    m_tableView = cocos2d::extension::TableView::create(this, Size(tableWidth,tableHeight));
    m_tableView->setDirection(cocos2d::extension::TableView::Direction::HORIZONTAL);
    m_tableView->setPosition(tablePosition);
    m_tableView->setDelegate(this);
    m_tableView->setVerticalFillOrder(cocos2d::extension::TableView::VerticalFillOrder::TOP_DOWN);
    m_lowerLayer->addChild(m_tableView);
    
}

void MainScene::updateHighScoreAfterGame(){
    
    
    UserDefault* userDef =  UserDefault::getInstance();
    int value = userDef->getIntegerForKey(GAME_HIGH_SCORE_KEY_SAVE_GAME, 0);
    std::string highScore = "HIGH SCORE :  " + std::to_string(value);
    highScoreTextSaveGame->setString(highScore);
}

TableViewCell* MainScene::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    std::string name = m_seasonList.at(idx)->m_heading;
    std::string imagePath = m_seasonList.at(idx)->m_imageURL;
    
    TableViewCell *cell = table->dequeueCell();
    if (cell){
        cell->removeAllChildrenWithCleanup(true);
    }
    else{
        cell = new TableViewCell();
        cell->autorelease();
    }
    
    Sprite* tempImage = Sprite::create(imagePath);
    
    Sprite* cellBg = Sprite::create(CHARACTERS"chandler.jpg");
    cellBg->setAnchorPoint(Vec2(0.5, 1));
    cellBg->setScaleY(0.75);
    cellBg->setPosition(Vec2(rowWidth * 0.5 , rowHeight * 0.975));
    cellBg->setTag(CELL_BG_TAG);
    cell->addChild(cellBg);
    
    Label* nameLabel = Label::createWithTTF(name, FONT_DOSIS, 22);
    nameLabel->setPosition(rowWidth * 0.5, rowHeight * 0.1);
    nameLabel->setColor(Color3B::WHITE);
    nameLabel->setTag(CELL_NAME_TAG);
    cell->addChild(nameLabel);
    
    cellBg->setTexture(tempImage->getTexture());
    
    return cell;
}

//tableView
Size MainScene::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    rowHeight = tableHeight;
    rowWidth = tableWidth / 3.75;
    return Size(rowWidth, rowHeight);
}


void MainScene::tableCellTouched(TableView *table, TableViewCell *cell)
{
    
    CCLOG("CELL %zd ", cell->getIdx());
//    Label* label = (Label*)cell->getChildByTag(CELL_BG_TAG)->getChildByTag(CELL_NAME_TAG);
//    std::string nameStr = label->getString();
//    
//    LatestLayer* latestLayer = LatestLayer::createLayer();
//    if (nameStr.compare(LATEST) == 0)
//    {
//        CCLOG("Latest button clicked");
//        latestLayer->setCategory(LATEST);
//        
//    }
//    else if (nameStr.compare(TRENDING) == 0)
//    {
//        CCLOG("Trending button clicked");
//        latestLayer->setCategory(TRENDING);
//    }
//    else if (nameStr.compare(EDITOR_CHOICE) == 0)
//    {
//        CCLOG("Editors Choice button clicked");
//        latestLayer->setCategory(EDITOR_CHOICE);
//    }
//    else if (nameStr.compare(TOP_RATED) == 0)
//    {
//        CCLOG("Top Rated button clicked");
//        latestLayer->setCategory(TOP_RATED);
//    }
//    else if (nameStr.compare(TV_SHOWS) == 0)
//    {
//        CCLOG("TV SHOWS button clicked");
//        latestLayer->setCategory(TV_SHOWS);
//    }
//    else{
//        CCLOG("No pre defined category selected");
//        latestLayer->setCategory(LATEST);
//    }
//    
//    this->addChild(latestLayer);
    
}

ssize_t MainScene::numberOfCellsInTableView(TableView *table)
{
    auto size = m_seasonList.size();
    return size;
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

void MainScene::playQuizCallback(Ref* pSender){

    CCLOG("inside quiz call back");
}

void MainScene::playSaveMeCallback(Ref* pSender){

    CCLOG("play save me game");
    AppDelegate::getDelegate()->PlaySaveMeGame();
    

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