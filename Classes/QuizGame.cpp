//
//  QuizGame.cpp
//  Friends
//
//  Created by Machintosh on 18/10/16.
//
//

#include "QuizGame.hpp"
#include "extensions/cocos-ext.h"
#include "constant.h"
#include "MainScene.hpp"
#include "audio/include/AudioEngine.h"
#include "SimpleAudioEngine.h"
#include "AppDelegate.h"

USING_NS_CC;

#define FONT_OPTION                             35

#define OPTION_TAG                              218
#define RESULT_IMAGE_TAG                        210
#define OPTION_TWO_TAG                          211
#define OPTION_THREE_TAG                        212
#define OPTION_FOUR_TAG                         213

#define TIMER_DURATION                          8
#define CORRECT_ANSWER_SCORE                    10

using namespace std;

using namespace cocos2d::experimental;

Scene* QuizGame::createGameScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = QuizGame::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool QuizGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    return true;
}

void QuizGame::onEnter()
{
    
    curIndex = 0;
    totalQuestions= 0;
    m_score =0;
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event){
        return true;
    };
    listener->setSwallowTouches(true);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    listener->retain();
    
    
    m_keyboardListener = EventListenerKeyboard::create();
    m_keyboardListener->onKeyReleased = CC_CALLBACK_2(QuizGame::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_keyboardListener, this);
    
    fillDataBase();
    createGameSceneBackground();
    createOptionsHolder();
    
    setGameData();
    
}

void QuizGame::fillDataBase(){

    QuestionStruct* item1 = new QuestionStruct();
    item1->m_question = "Which TV soap Joey Features on FRIENDS?";
    item1->m_optionA = "Its Life";
    item1->m_optionB = "Days of our lifes";
    item1->m_optionC = "Days are high";
    item1->m_optionD = "Eat and Sleep";
    item1->m_answer = "Days of our lifes";
    
    m_questionList.push_back(item1);
    
    QuestionStruct* item2 = new QuestionStruct();
    item2->m_question = "What was the name of Ross & Rachel daughter ?";
    item2->m_optionA = "Emma";
    item2->m_optionB = "Charlie";
    item2->m_optionC = "Emily";
    item2->m_optionD = "Amy";
    item2->m_answer = "Emma";
    
    m_questionList.push_back(item2);
    
    QuestionStruct* item3 = new QuestionStruct();
    item3->m_question = "Which FRIENDS actor never got nominated for Emmy awards in any category ?";
    item3->m_optionA = "Matthew Perry";
    item3->m_optionB = "Lisa Kudrow";
    item3->m_optionC = "Matt Le Blanc";
    item3->m_optionD = "Courtney Cox";
    item3->m_answer = "Courtney Cox";
    
    m_questionList.push_back(item3);
    
    QuestionStruct* item4 = new QuestionStruct();
    item4->m_question = "I will be there for you: was sang by ?";
    item4->m_optionA = "Beatles";
    item4->m_optionB = "Green Day";
    item4->m_optionC = "The Rembrandts";
    item4->m_optionD = "Nirvana";
    item4->m_answer = "The Rembrandts";
    
    m_questionList.push_back(item4);
    
}

void QuizGame::createGameSceneBackground(){

    m_background = LayerColor::create(Color4B(0,0,0,255), visibleSize.width, visibleSize.height);
    m_background->setPosition(Vec2(0,0));
    this->addChild(m_background);
    
    m_questionBg = Scale9Sprite::create("board_9patch.png");
    m_questionBg->setContentSize(Size(visibleSize.width * 0.95, visibleSize.height * 0.33));
    m_questionBg->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height - m_questionBg->getContentSize().height * 0.6));
    this->addChild(m_questionBg);
    
    m_currQuestion = Label::createWithTTF("", FONT_DOSIS, 50);
    m_currQuestion->setColor(Color3B::BLACK);
    m_currQuestion->setWidth(m_questionBg->getContentSize().width * 0.8);
    m_currQuestion->setPosition(Vec2(m_questionBg->getContentSize().width * 0.5, m_questionBg->getContentSize().height * 0.5));
    m_questionBg->addChild(m_currQuestion);
   
}

void QuizGame::createOptionsHolder(){

    Color3B tempColor = Color3B(255,203,0);
    
    DrawNode* horLine1 = DrawNode::create();
    horLine1->setLineWidth(10);
    horLine1->setColor(tempColor);
    horLine1->drawLine(Vec2(0, visibleSize.height * 0.55), Vec2(visibleSize.width, visibleSize.height * 0.55),Color4F(tempColor));
    this->addChild(horLine1);
    
    DrawNode* horLine2 = DrawNode::create();
    horLine2->setLineWidth(10);
    horLine2->setColor(tempColor);
    horLine2->drawLine(Vec2(0, visibleSize.height * 0.43), Vec2(visibleSize.width, visibleSize.height * 0.43),Color4F(tempColor));
    this->addChild(horLine2);
    
    DrawNode* horLine3 = DrawNode::create();
    horLine3->setLineWidth(10);
    horLine3->setColor(tempColor);
    horLine3->drawLine(Vec2(0, visibleSize.height * 0.31), Vec2(visibleSize.width, visibleSize.height * 0.31),Color4F(tempColor));
    this->addChild(horLine3);
    
    DrawNode* horLine4 = DrawNode::create();
    horLine4->setLineWidth(10);
    horLine4->setColor(tempColor);
    horLine4->drawLine(Vec2(0, visibleSize.height * 0.19), Vec2(visibleSize.width, visibleSize.height * 0.19),Color4F(tempColor));
    this->addChild(horLine4);
    
    
    Scale9Sprite* image1 = Scale9Sprite::create("board_9patch.png");
    image1->setContentSize(Size(visibleSize.width * 0.85, visibleSize.height * 0.1));
    
    Scale9Sprite* image2 = Scale9Sprite::create("board_9patch.png");
    image2->setContentSize(Size(visibleSize.width * 0.85, visibleSize.height * 0.1));
    
    Scale9Sprite* image3 = Scale9Sprite::create("board_9patch.png");
    image3->setContentSize(Size(visibleSize.width * 0.85, visibleSize.height * 0.1));
    
    Scale9Sprite* image4 = Scale9Sprite::create("board_9patch.png");
    image4->setContentSize(Size(visibleSize.width * 0.85, visibleSize.height * 0.1));
    
    
    option1 = MenuItemSprite::create(image1, image1, CC_CALLBACK_1(QuizGame::answerCallBack, this));
    option1->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.55));
    
    option2 = MenuItemSprite::create(image2, image2, CC_CALLBACK_1(QuizGame::answerCallBack, this));
    option2->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.43));
    
    option3 = MenuItemSprite::create(image3, image3, CC_CALLBACK_1(QuizGame::answerCallBack, this));
    option3->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.31));
    
    option4 = MenuItemSprite::create(image4, image4, CC_CALLBACK_1(QuizGame::answerCallBack, this));
    option4->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.19));
    
    auto optionMenu = Menu::create(option1,option2,option3,option4, NULL);
    optionMenu->setPosition(Vec2(0,0));
    this->addChild(optionMenu);

    //touch was not working on the menu item sprite, hence using this
    Node::onEnter();
    
    std::string userScore = "SCORE \n  " + std::to_string(m_score);
    
    scoreLabel = Label::createWithTTF(userScore, FONT_AFTON_JAMES, 40);
    scoreLabel->setAnchorPoint(Vec2(0, 0.5));
    scoreLabel->setPosition(Vec2(20, scoreLabel->getContentSize().height * 0.65));
    this->addChild(scoreLabel);
    
    timerLabel = Label::createWithTTF("12",FONT_AFTON_JAMES, 80);
    timerLabel->setPosition(Vec2(visibleSize.width * 0.5, timerLabel->getContentSize().height * 0.65));
    this->addChild(timerLabel);
 
    std::string curQuest = std::to_string(curIndex + 1);
    std::string totalQ = std::to_string(totalQuestions);
    
    std::string questionProg = "QUESTION \n  " + curQuest + " / " + totalQ;
    
    questionLabel = Label::createWithTTF(questionProg, FONT_AFTON_JAMES, 40);
    questionLabel->setAnchorPoint(Vec2(1, 0.5));
    questionLabel->setPosition(Vec2(visibleSize.width - 20, questionLabel->getContentSize().height * 0.65));
    this->addChild(questionLabel);
    
    m_optionOne = Label::createWithTTF("", FONT_DOSIS, FONT_OPTION);
    m_optionOne->setTag(OPTION_TAG);
    m_optionOne->setColor(Color3B::BLACK);
    m_optionOne->setPosition(Vec2(option1->getContentSize().width * 0.5, option1->getContentSize().height * 0.5));
    option1->addChild(m_optionOne);
    
    m_optionTwo = Label::createWithTTF("", FONT_DOSIS, FONT_OPTION);
    m_optionTwo->setTag(OPTION_TAG);
    m_optionTwo->setColor(Color3B::BLACK);
    m_optionTwo->setPosition(Vec2(option2->getContentSize().width * 0.5, option2->getContentSize().height * 0.5));
    option2->addChild(m_optionTwo);
    
    m_optionThree = Label::createWithTTF("", FONT_DOSIS, FONT_OPTION);
    m_optionThree->setTag(OPTION_TAG);
    m_optionThree->setColor(Color3B::BLACK);
    m_optionThree->setPosition(Vec2(option3->getContentSize().width * 0.5, option3->getContentSize().height * 0.5));
    option3->addChild(m_optionThree);
    
    m_optionFour = Label::createWithTTF("", FONT_DOSIS, FONT_OPTION);
    m_optionFour->setTag(OPTION_TAG);
    m_optionFour->setColor(Color3B::BLACK);
    m_optionFour->setPosition(Vec2(option4->getContentSize().width * 0.5, option4->getContentSize().height * 0.5));
    option4->addChild(m_optionFour);
    
    QuestionStruct* question1 = m_questionList.at(curIndex);
    updateNextQuestion(question1);
    
    Node::onEnter();
    this->schedule(CC_SCHEDULE_SELECTOR(QuizGame::reduceTimer), 1);
}

void QuizGame::setGameData(){

    totalQuestions = m_questionList.size();
    m_timer = TIMER_DURATION;
    timerLabel->setString(std::to_string(m_timer));

}

void QuizGame::updateNextQuestion(QuestionStruct* question){

    if (question != NULL){
        
        option1->setEnabled(true);
        option2->setEnabled(true);
        option3->setEnabled(true);
        option4->setEnabled(true);

        if (totalQuestions == 0){
            totalQuestions = m_questionList.size();
        }
        
        //UPDATE ALL LABELS HERE
        m_timer = TIMER_DURATION;
        timerLabel->setString(std::to_string(m_timer));
        
        std::string curQuest = std::to_string(curIndex + 1);
        std::string totalQ = std::to_string(totalQuestions);
        std::string questionProg = "QUESTION \n  " + curQuest + " / " + totalQ;
        
        questionLabel->setString(questionProg);
        
        std::string questionName = question->m_question;
        std::string optionA = question->m_optionA;
        std::string optionB = question->m_optionB;
        std::string optionC = question->m_optionC;
        std::string optionD = question->m_optionD;
        std::string answer = question->m_answer;
        
        Scale9Sprite* resultImage = (Scale9Sprite*)option1->getChildByTag(RESULT_IMAGE_TAG);
        if (resultImage != NULL){
        
            resultImage->removeFromParentAndCleanup(true);
        }
        
        Scale9Sprite* resultImage2 = (Scale9Sprite*)option2->getChildByTag(RESULT_IMAGE_TAG);
        if (resultImage2 != NULL){
            
            resultImage2->removeFromParentAndCleanup(true);
        }
        
        Scale9Sprite* resultImage3 = (Scale9Sprite*)option3->getChildByTag(RESULT_IMAGE_TAG);
        if (resultImage3 != NULL){
            
            resultImage3->removeFromParentAndCleanup(true);
        }
        
        Scale9Sprite* resultImage4 = (Scale9Sprite*)option4->getChildByTag(RESULT_IMAGE_TAG);
        if (resultImage4 != NULL){
            
            resultImage4->removeFromParentAndCleanup(true);
        }
        
        m_currQuestion->setString(questionName);
        m_optionOne->setString(optionA);
        m_optionTwo->setString(optionB);
        m_optionThree->setString(optionC);
        m_optionFour->setString(optionD);
        m_correctAnswer = answer;
    }
}

void QuizGame::answerCallBack(Ref* pSender){
    
    CCLOG("answer callback selected");
    
    MenuItemSprite* sender = (MenuItemSprite*)pSender;
    Label* optionSelected = (Label*)sender->getChildByTag(OPTION_TAG);
    
    Scale9Sprite* image;
    Label* resultText;
    
    std::string answerGiven = optionSelected->getString();
    if (answerGiven.compare(m_correctAnswer) == 0){
        
        image = Scale9Sprite::create("greenButton.png");
        resultText = Label::createWithTTF("Yay Correct !", FONT_DOSIS, FONT_OPTION);
        
        m_score = m_score + CORRECT_ANSWER_SCORE;
        std::string userScore = "SCORE \n  " + std::to_string(m_score);
        scoreLabel->setString(userScore);
        
    }else{
        
        image = Scale9Sprite::create("redButton.png");
        
        resultText = Label::createWithTTF("Sorry Wrong !", FONT_DOSIS, FONT_OPTION);
    }

    image->setContentSize(Size(visibleSize.width * 0.85, visibleSize.height * 0.1));
    image->setPosition(Vec2(sender->getContentSize().width * 0.5, sender->getContentSize().height * 0.5));
    image->setTag(RESULT_IMAGE_TAG);
    sender->addChild(image);
    
    resultText->setPosition(Vec2(image->getContentSize().width * 0.5, image->getContentSize().height * 0.5));
    image->addChild(resultText);
    
    this->unschedule(CC_SCHEDULE_SELECTOR(QuizGame::reduceTimer));
    
    CallFunc* callFun1 = CallFunc::create([=]{
    
        CCLOG("inside next question call");
        
        prepareNextQuestion();
        
        Node::onEnter();
        this->schedule(CC_SCHEDULE_SELECTOR(QuizGame::reduceTimer), 1);
    });
    
    auto sequence = Sequence::create(DelayTime::create(1), callFun1, NULL);
    this->runAction(sequence);
}

void QuizGame::prepareNextQuestion(){

    option1->setEnabled(false);
    option2->setEnabled(false);
    option3->setEnabled(false);
    option4->setEnabled(false);
    
    curIndex++;
    if (curIndex == m_questionList.size()){
        
        CCLOG("game over 2");
        
        UserDefault::getInstance()->setIntegerForKey(GAME_HIGH_SCORE_KEY_QUIZ_GAME, m_score);
        
        this->unschedule(CC_SCHEDULE_SELECTOR(QuizGame::reduceTimer));
        return;
    }
    QuestionStruct* nextQuestion =  m_questionList.at(curIndex);
    updateNextQuestion(nextQuestion);
    
}

void QuizGame::reduceTimer(float dt){
    
    if (m_timer == 0){
        
        prepareNextQuestion();
        
    }else{
    
        m_timer--;
    }
    
    timerLabel->setString(std::to_string(m_timer));
    
}

void QuizGame::onExit()
{
    listener->release();
    Layer::onExit();
}

void QuizGame::optionOneCallBack(Ref* pSender){
    
    CCLOG("option one callback");
}

void QuizGame::optionTwoCallBack(Ref* pSender){
    
    CCLOG("option two callback");
    
}

void QuizGame::optionThreeCallBack(Ref* pSender){
    
    CCLOG("option three callback");
}

void QuizGame::optionFourCallBack(Ref* pSender){
    
    CCLOG("option four callback");
    
}


void QuizGame::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent)
{
    pEvent->stopPropagation();
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        this->removeFromParentAndCleanup(true);
        AppDelegate::getDelegate()->showMainScene();
    }
}