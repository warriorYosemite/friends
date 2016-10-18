//
//  QuizGame.hpp
//  Friends
//
//  Created by Machintosh on 18/10/16.
//
//

#ifndef QuizGame_hpp
#define QuizGame_hpp

#include <stdio.h>

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "extensions/cocos-ext.h"
#include "commonClasses.h"

using namespace cocos2d::ui;
USING_NS_CC;

class QuizGame : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createGameScene();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    Size visibleSize;
    cocos2d::EventListenerTouchOneByOne *listener;
    cocos2d::EventListenerKeyboard *m_keyboardListener;
    std::vector<QuestionStruct* > m_questionList;
    
    LayerColor* m_background;
    Scale9Sprite* m_questionBg;
    
    int curIndex;
    
    Label* m_currQuestion;
    Label* m_optionOne;
    Label* m_optionFour;
    Label* m_optionThree;
    Label* m_optionTwo;
    std::string m_correctAnswer;
    
    MenuItemSprite* option1;
    MenuItemSprite* option2;
    MenuItemSprite* option3;
    MenuItemSprite* option4;
    
    int m_score;
    int m_timer;
    Label* scoreLabel;
    Label* timerLabel;
    Label* questionLabel;
    
    void createGameSceneBackground();
    void createOptionsHolder();
    void updateNextQuestion(QuestionStruct* question);
    void fillDataBase();
    
    
    void optionOneCallBack(Ref* pSender);
    void optionTwoCallBack(Ref* pSender);
    void optionThreeCallBack(Ref* pSender);
    void optionFourCallBack(Ref* pSender);
    void answerCallBack(Ref* pSender);
    
    CREATE_FUNC(QuizGame);
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent);
    
    

};
#endif /* QuizGame_hpp */
