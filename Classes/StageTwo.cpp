#include "StageTwo.h"
#include "extensions/cocos-ext.h"
#include "constant.h"
#include "MainScene.hpp"
#include "audio/include/AudioEngine.h"
#include "SimpleAudioEngine.h"
#include "AppDelegate.h"

USING_NS_CC;

using namespace std;

#define GRID_BASE_TAG               100
#define NUMBER_OF_GRIDS             8

#define TIME_DURATION               2

int myrandom (int i){
    return std::rand()%i;
}

using namespace cocos2d::experimental;

Scene* StageTwo::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StageTwo::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StageTwo::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    m_gridVector.clear();
    m_colorVector.clear();
    m_countThreshold = 1;
    
    return true;
}

void StageTwo::onEnter()
{
 
    m_gridCount = 0;
    m_gridWidth = 0;
    m_gridHeight = 0;
    m_previousNumber = -1;
    m_Score = 0;
    m_highScore = 0;
    isTouched = true;
    isGameOver = false;
    isCharacterSelected = false;
    m_deadCharacterVector.clear();
    m_aliveCharacterVector.clear();
    isLevelUp = false;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_GUN_SHOT);
    
    
    LayerColor* m_bgLayer = LayerColor::create(Color4B(0,0,0, 255), visibleSize.width, visibleSize.height);
    m_bgLayer->setPosition(Vec2(0,0));
    this->addChild(m_bgLayer);
    
    createTopHeader();
    setNumberOfGrids(NUMBER_OF_GRIDS);
    fillImageVector();
    getGridDimensions();
    createGameGrids();
    handleHighScore();

    selectCharacterToSave(1);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    EventListenerTouchOneByOne* touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(StageTwo::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(StageTwo::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    Node::onEnter();
//    this->schedule(CC_SCHEDULE_SELECTOR(StageTwo::updateColors), TIME_DURATION);
}

void StageTwo::selectCharacterToSave(int buttonCount){

    popUpLayerBase = Layer::create();
    this->addChild(popUpLayerBase);

    auto dispatcher2 = Director::getInstance()->getEventDispatcher();
    EventListenerTouchOneByOne* touchListener2 = EventListenerTouchOneByOne::create();
    touchListener2->setSwallowTouches(true);
    touchListener2->onTouchBegan = [=](Touch* touch, Event* event){
    
        return true;
    };
    
    dispatcher2->addEventListenerWithSceneGraphPriority(touchListener2, popUpLayerBase);
    
    m_characterSelection = Scale9Sprite::create("board_9patch.png");
    m_characterSelection->setContentSize(Size(visibleSize.width * 0.9, visibleSize.height * 0.33));
    m_characterSelection->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
    popUpLayerBase->addChild(m_characterSelection);
    
    Label* messageLabel = Label::createWithTTF("Select A Character \n you want to save", GAME_FONT_HEADER, 50);
    messageLabel->setColor(Color3B::BLACK);
    messageLabel->setAlignment(TextHAlignment::CENTER);
    messageLabel->setPosition(Vec2(m_characterSelection->getContentSize().width * 0.5, m_characterSelection->getContentSize().height * 0.585));
    m_characterSelection->addChild(messageLabel);

    Label* okLabel = Label::createWithTTF("OK", GAME_FONT_HEADER, 40);
    okLabel->setColor(Color3B::BLACK);
    MenuItemLabel* okStr = MenuItemLabel::create(okLabel, CC_CALLBACK_1(StageTwo::okButtonCallback, this));
    okStr->setAnchorPoint(Vec2(0.5,0.5));
    auto okMenu = Menu::create(okStr, NULL);
    okMenu->setPosition(Vec2(m_characterSelection->getContentSize().width * 0.5, m_characterSelection->getContentSize().height * 0.1));
    m_characterSelection->addChild(okMenu);
    
    if (buttonCount == 2)
    {
        
        std::string messageStr = "Are You Sure \n You want to continue \n with \n " + m_selectedPlayerName;
        messageLabel->setString(messageStr);

        
        Label* cancelLabel = Label::createWithTTF("CANCEL", GAME_FONT_HEADER, 40);
        cancelLabel->setColor(Color3B::BLACK);
        MenuItemLabel* cancelStr = MenuItemLabel::create(cancelLabel, CC_CALLBACK_1(StageTwo::cancelButtonCallback, this));
        cancelStr->setAnchorPoint(Vec2(0.5,0.5));
        auto cancelMenu = Menu::create(cancelStr, NULL);
        cancelMenu->setPosition(Vec2(m_characterSelection->getContentSize().width * 0.75, m_characterSelection->getContentSize().height * 0.1));
        m_characterSelection->addChild(cancelMenu);
        
        okMenu->setPosition(Vec2(m_characterSelection->getContentSize().width * 0.25, m_characterSelection->getContentSize().height * 0.1));
    }
    
}

void StageTwo::cancelButtonCallback(Ref* pSender){

    CCLOG("inside cancel button callback");
    if (popUpLayerBase)
        popUpLayerBase->removeFromParentAndCleanup(true);

}

void StageTwo::okButtonCallback(Ref* pSender){
    
    CCLOG("inside ok button callback");
    if (popUpLayerBase)
        popUpLayerBase->removeFromParentAndCleanup(true);
    
    if (!m_selectedPlayerName.empty())
    {
        isCharacterSelected = true;
        this->schedule(CC_SCHEDULE_SELECTOR(StageTwo::updateColors), TIME_DURATION);
    }
    
}

void StageTwo::handleHighScore(){

    UserDefault* userDef =  UserDefault::getInstance();
    int value = userDef->getIntegerForKey(GAME_HIGH_SCORE_KEY_SAVE_GAME, 0);
    m_highScore = value;
}

bool StageTwo::onTouchBegan(Touch *touch, Event *event)
{
    CCLOG("in on touch began");
    isTouched = true;
    
    Size locationInNodeBG;
    
    if (isGameOver)
    {
        CCLOG("game is over");
        return true;
    }
    
    for (int i=0; i < m_gridCount; i++)
    {
        Node* gridE = m_gridVector.at(i);
        
        Vec2 locationInNode = gridE->convertToNodeSpace(touch->getLocation());
        
        GridImage* colorE = (GridImage*)gridE->getChildByTag(GRID_BASE_TAG + i);
        locationInNodeBG = colorE->getContentSize();
        
        Rect rect = Rect(0, 0, m_gridWidth, m_gridHeight);
        
        if (rect.containsPoint(locationInNode))
        {
            
            std::string currColor = colorE->getImageName();
            
            if (!isCharacterSelected){
                m_selectedPlayerName = currColor;
                selectCharacterToSave(2);
                return true;
            }
            
            std::string playerName = m_playerKillName->getString();
            
            if (playerName.compare(m_selectedPlayerName) == 0){
            
                CCLOG("game over !");
                handleGameOver();
                return true;
            }
            
            if (currColor.compare(playerName) == 0)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_GUN_SHOT);
                
                m_Score++;
                playerScore->setString(std::to_string(m_Score));
                
                int killCount = colorE->getKillCount();
                killCount++;
                colorE->setKillCount(killCount);
                
                if (killCount >= m_countThreshold){
                    
                    colorE->setPermanentlyKilled(true);
                    m_deadCharacterVector.push_back(currColor);
                    m_aliveCharacterVector.erase(std::remove(m_aliveCharacterVector.begin(), m_aliveCharacterVector.end(), colorE), m_aliveCharacterVector.end());
                    
                }else{
                    CallFunc* callFun1 = CallFunc::create([=] {
                        
                        colorE->setKillStatus(true);
                        
                    });
                    
                    CallFunc* callFun2 = CallFunc::create([=]{
                        
                        colorE->setKillStatus(false);
                    });
                    
                    colorE->runAction(Sequence::create(callFun1, DelayTime::create(TIME_DURATION), callFun2, NULL));
                }
                break;
            }
            else
            {
                
                CCLOG("game over !");
                handleGameOver();
                break;

            }
        }
        
    }
    return true;
}

void StageTwo::handleGameOver(){

    this->unschedule(CC_SCHEDULE_SELECTOR(StageTwo::updateColors));
    
    std::string popupHeader = "";
    std::string buttonName = "";
    
    if (m_Score > m_highScore)
    {
        m_highScore = m_Score;
        UserDefault::getInstance()->setIntegerForKey(GAME_HIGH_SCORE_KEY_SAVE_GAME, m_highScore);
        UserDefault::getInstance()->flush();
    }
    
    popUpLayer = Scale9Sprite::create("board_9patch.png");
    popUpLayer->setContentSize(Size(visibleSize.width * 0.75, visibleSize.height * 0.35));
    popUpLayer->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
    this->addChild(popUpLayer);
    
    if (isLevelUp){
    
        popupHeader = "LEVEL UP !";
    }else{
    
        popupHeader = "GAME OVER !";
    }
    
    Label* gameOverText = Label::createWithTTF(popupHeader, GAME_FONT_HEADER, 50);
    gameOverText->setColor(Color3B::BLACK);
//    gameOverText->setColor(Color3B::WHITE);
    gameOverText->setPosition(Vec2(popUpLayer->getContentSize().width * 0.5, popUpLayer->getContentSize().height - gameOverText->getContentSize().height *0.9));
    popUpLayer->addChild(gameOverText);

    std::string yourScoreStr = "Your Score : " + std::to_string(m_Score);
    Label* yourScore = Label::createWithTTF(yourScoreStr, GAME_FONT_HEADER, 50);
    yourScore->setColor(Color3B::BLACK);
    yourScore->setAnchorPoint(Vec2(0.5,0.5));
    yourScore->setPosition(Vec2(popUpLayer->getContentSize().width * 0.5, popUpLayer->getContentSize().height * 0.4));
    popUpLayer->addChild(yourScore);

    
    std::string highScore = "High Score : " + std::to_string(m_highScore);
    Label* highScoreStr = Label::createWithTTF(highScore, GAME_FONT_HEADER, 50);
    highScoreStr->setColor(Color3B::BLACK);
    highScoreStr->setAnchorPoint(Vec2(0.5, 0.5));
    highScoreStr->setPosition(Vec2(popUpLayer->getContentSize().width * 0.5, popUpLayer->getContentSize().height * 0.6));
    popUpLayer->addChild(highScoreStr);
    
    if (isLevelUp){
        
        buttonName = "CONTINUE";
    }else{
        
        buttonName = "PLAY AGAIN";
    }
    
    Label* gameStart = Label::createWithTTF(buttonName, GAME_FONT_HEADER, 55);
    gameStart->setColor(Color3B::BLACK);
    MenuItemLabel* restartImage = MenuItemLabel::create(gameStart, CC_CALLBACK_1(StageTwo::restartGameScenario, this));
    restartImage->setAnchorPoint(Vec2(0.5,0.5));
    auto restartMenu = Menu::create(restartImage, NULL);
    restartMenu->setPosition(Vec2(popUpLayer->getContentSize().width * 0.5, restartImage->getContentSize().height * 0.6));
    popUpLayer->addChild(restartMenu);
    
    isGameOver = true;
    
    
    homeButtonBg = Scale9Sprite::create("board_9patch.png");
    homeButtonBg->setContentSize(Size(visibleSize.width * 0.4, visibleSize.height * 0.1));
    homeButtonBg->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.15));
    this->addChild(homeButtonBg);
    
    Label* homeLabel = Label::createWithTTF("HOME", GAME_FONT_HEADER, 40);
    homeLabel->setColor(Color3B::BLACK);
    MenuItemLabel* homeStr = MenuItemLabel::create(homeLabel, CC_CALLBACK_1(StageTwo::homeButtonCallback, this));
    homeStr->setAnchorPoint(Vec2(0.5,0.5));
    auto homeMenu = Menu::create(homeStr, NULL);
    homeMenu->setPosition(Vec2(homeButtonBg->getContentSize().width * 0.5, homeButtonBg->getContentSize().height * 0.5));
    homeButtonBg->addChild(homeMenu);
}

void StageTwo::homeButtonCallback(Ref* pSender){

    CCLOG("home button pressed");
    unscheduleAllCallbacks();
    this->removeFromParentAndCleanup(true);
    AppDelegate::getDelegate()->showMainScene();
    
}

void StageTwo::restartGameScenario(Ref* pSender){
    CCLOG("restart game clicked");
    
    if (isLevelUp){
    
        //do not edit the score
        m_countThreshold = m_countThreshold + 2;
        
    }else{
    
        m_Score = 0;
    }
    
    m_previousNumber = -1;
    isCharacterSelected = false;
    isTouched = true;
    isGameOver = false;
    playerScore->setString(std::to_string(m_Score));
    m_playerKillName->setString("");
    m_selectedPlayerName.clear();
    m_deadCharacterVector.clear();
    m_aliveCharacterVector.clear();
    m_gridVector.clear();
    
    
    for (int i=0; i< m_gridCount; i++)
    {
        this->removeChildByTag(GRID_BASE_TAG + i);
    }
    
    popUpLayer->removeFromParentAndCleanup(true);
    homeButtonBg->removeFromParentAndCleanup(true);
    
    createGameGrids();
    
    isLevelUp = false;
    
    selectCharacterToSave(1);
    
    resetAllGridColors();
//    this->schedule(CC_SCHEDULE_SELECTOR(StageTwo::updateColors), TIME_DURATION);
    
}

void StageTwo::onTouchEnded(Touch *touch, Event *event)
{
    CCLOG("in on touch ended");
}

void StageTwo::setNumberOfGrids(int count)
{
    m_gridCount = count;
}

void StageTwo::fillImageVector()
{
    GridImage* elem1 = GridImage::create(GAME_IMAGES"imageOne.jpg");
    elem1->killCountDisplay();
    elem1->setImageName("Jack Geller");
    m_colorVector.push_back(elem1);
    
    GridImage* elem2 = GridImage::create(GAME_IMAGES"imageTwo.jpg");
    elem2->killCountDisplay();
    elem2->setImageName("Judy Geller");
    m_colorVector.push_back(elem2);
    
    GridImage* elem3 = GridImage::create(GAME_IMAGES"imageThree.jpg");
    elem3->killCountDisplay();
    elem3->setImageName("OMG Janice");
    m_colorVector.push_back(elem3);
    
    GridImage* elem4 = GridImage::create(GAME_IMAGES"imageFour.jpg");
    elem4->killCountDisplay();
    elem4->setImageName("Mike Hannigan");
    m_colorVector.push_back(elem4);
    
    GridImage* elem5 = GridImage::create(GAME_IMAGES"imageFive.png");
    elem5->killCountDisplay();
    elem5->setImageName("Carol Willick");
    m_colorVector.push_back(elem5);
    
    GridImage* elem6 = GridImage::create(GAME_IMAGES"imageSix.jpg");
    elem6->killCountDisplay();
    elem6->setImageName("Richard Burke");
    m_colorVector.push_back(elem6);
    
    GridImage* elem7 = GridImage::create(GAME_IMAGES"imageSeven.jpg");
    elem7->killCountDisplay();
    elem7->setImageName("David");
    m_colorVector.push_back(elem7);
    
    GridImage* elem8 = GridImage::create(GAME_IMAGES"imageEight.jpg");
    elem8->killCountDisplay();
    elem8->setImageName("Paul Stevens");
    m_colorVector.push_back(elem8);
    
    GridImage* elem9 = GridImage::create(GAME_IMAGES"imageNine.jpg");
    elem9->killCountDisplay();
    elem9->setImageName("Gavin Mitchell");
    m_colorVector.push_back(elem9);
    
    GridImage* elem15 = GridImage::create(GAME_IMAGES"imageFifteen.jpg");
    elem15->killCountDisplay();
    elem15->setImageName("Pizza Joey");
    m_colorVector.push_back(elem15);
    
    GridImage* elem16 = GridImage::create(GAME_IMAGES"imageSixteen.png");
    elem16->killCountDisplay();
    elem16->setImageName("Stylish Rachel");
    m_colorVector.push_back(elem16);
    
    GridImage* elem17 = GridImage::create(GAME_IMAGES"imageSeventeen.jpg");
    elem17->killCountDisplay();
    elem17->setImageName("Freaky Pheobe");
    m_colorVector.push_back(elem17);
    
    GridImage* elem18 = GridImage::create(GAME_IMAGES"imageEighteen.jpeg");
    elem18->killCountDisplay();
    elem18->setImageName("Red Ross");
    m_colorVector.push_back(elem18);
    
    GridImage* elem19 = GridImage::create(GAME_IMAGES"imageNineteen.png");
    elem19->killCountDisplay();
    elem19->setImageName("Bossy Monica");
    m_colorVector.push_back(elem19);
    
    GridImage* elem20 = GridImage::create(GAME_IMAGES"imageTwenty.jpg");
    elem20->killCountDisplay();
    elem20->setImageName("Funny Chandler");
    m_colorVector.push_back(elem20);
    
    GridImage* elem21 = GridImage::create(GAME_IMAGES"imageTwentyone.jpg");
    elem21->killCountDisplay();
    elem21->setImageName("Just Gunther");
    m_colorVector.push_back(elem21);
}



void StageTwo::createTopHeader()
{
    m_topHeader = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height * 0.1);
    m_topHeader->setPosition(Vec2(0, visibleSize.height - visibleSize.height * 0.1));
    this->addChild(m_topHeader,1);
    
    Label* yourScroreText = Label::createWithTTF("KILL", GAME_FONT_HEADER, 60);
    yourScroreText->setAnchorPoint(Vec2(0,0.5));
    yourScroreText->setPosition(Vec2(30, m_topHeader->getContentSize().height * 0.475));
    yourScroreText->setColor(Color3B::WHITE);
    m_topHeader->addChild(yourScroreText);
    
    
    m_playerKillName = Label::createWithTTF("-----", GAME_FONT_HEADER, 40);
    m_playerKillName->setAnchorPoint(Vec2(0.5,0.5));
    m_playerKillName->setPosition(Vec2(m_topHeader->getContentSize().width * 0.5, m_topHeader->getContentSize().height * 0.475));
    m_playerKillName->setColor(Color3B::WHITE);
    m_topHeader->addChild(m_playerKillName);
    
    
    playerScore = Label::createWithTTF(std::to_string(m_Score), GAME_FONT_HEADER, 70);
    playerScore->setAnchorPoint(Vec2(1, 0.5));
    playerScore->setPosition(Vec2(m_topHeader->getContentSize().width - 20, m_topHeader->getContentSize().height * 0.4));
    playerScore->setColor(Color3B::WHITE);
    m_topHeader->addChild(playerScore);
}

void StageTwo::updateColors(float dt)
{
    CCLOG("updating layer colors to White");
    
    if (!isTouched){
        
        std::string currDisplayedName = m_playerKillName->getString();
        if (m_selectedPlayerName.compare(currDisplayedName)== 0)
        {
            m_Score++;
            playerScore->setString(std::to_string(m_Score));
        }
        else{
            CCLOG("game over !");
            handleGameOver();
            return;
        }
    }


    int randNo;
    int totalElemLeft = (int)m_aliveCharacterVector.size();
    if (totalElemLeft == 1){
    
        isLevelUp = true;
        handleGameOver();
        return;
    }
    
    do {
        randNo = random(0, totalElemLeft - 1);                // to avoid same color to be WHITE continously
    } while (randNo == m_previousNumber);
    
    
    std::string playerName = m_aliveCharacterVector.at(randNo)->getImageName();
    
    m_playerKillName->setString(playerName);
    
    m_previousNumber = randNo;
    isTouched = false;
}

void StageTwo::resetAllGridColors(){
    
    //set kill count to zero, on game restart
    for (int i=0; i< m_gridCount ; i++){
    
        GridImage* imageE = m_colorVector.at(i);
        imageE->setKillCount(0);
        imageE->setPermanentlyKilled(false);
    }
}


void StageTwo::getGridDimensions()
{
    CCLOG("into creating grids");
    
    //we will divide the whole screen depending upon the number of grids we want
    
    float availableHeight = visibleSize.height - visibleSize.height * 0.1;
    m_gridWidth = visibleSize.width / 2;
    
    if (m_gridCount == 4)
    {
        m_gridHeight = availableHeight /2;
        CCLOG("4 grids created");
    }
    else if (m_gridCount == 6){
        m_gridHeight = availableHeight /3;
        CCLOG("6 grids created");
        
    }
    else if (m_gridCount == 8){
        m_gridHeight = availableHeight /4;
        CCLOG("8 grids created");
    }
}

void StageTwo::createGameGrids(){

    CCLOG("creating game grids and pushing them in a vector");
    
    
    std::random_shuffle(m_colorVector.begin(), m_colorVector.end() , myrandom);
    
    for (int i=0; i < m_gridCount; i++)
    {
        LayerColor* layerE = LayerColor::create(Color4B(Color3B::GRAY), m_gridWidth, m_gridHeight);
        
        GridImage* imageE = m_colorVector.at(i);
        imageE->setTag(GRID_BASE_TAG + i);
        
        m_aliveCharacterVector.push_back(imageE);
        
        Size ws = layerE->getContentSize();
        Size maskSize = ws* 0.925;
        
        float radius = 40;
        if(imageE)
        {
            float scaleX = maskSize.width/imageE->getContentSize().width;
            float scaleY = maskSize.height/imageE->getContentSize().height;
            imageE->setScale(scaleX, scaleY);
        }
        
        // create masked image and position to center it on screen
        Node* clipNode = AppDelegate::getDelegate()->createRoundedRectMaskNode(maskSize, radius, 1.0f, 10);
        clipNode->setAnchorPoint(Vec2(0,0));
        imageE->setAnchorPoint(Vec2(0,0));
        imageE->setPosition(Vec2(clipNode->getContentSize().width * 0.5, clipNode->getContentSize().height * 0.5));
        clipNode->setTag(GRID_BASE_TAG + i);
        clipNode->addChild(imageE);
        
        if ( i % 2 == 0)
        {
            clipNode->setPosition(Vec2(10, (i * 0.5) * m_gridHeight + 10));
        }else{
            
            int factor = (int )i /2;
            clipNode->setPosition(Vec2(m_gridWidth, factor * m_gridHeight + 10));
        }
        
        this->addChild(clipNode);
        m_gridVector.push_back(clipNode);
    }

}


void StageTwo::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
