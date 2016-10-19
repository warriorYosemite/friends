//
//  CommonClasses.h
//  Snakes and Ladders
//
//  Created by Kuldeep Teekas on 28/08/15.
//
//


#ifndef __COMMONCLASSES_H__
#define __COMMONCLASSES_H__

struct ItemsDetailStruct{

    std::string m_heading;
    std::string m_imageURL;
    std::string m_content;
    
    ItemsDetailStruct(){
    
        m_heading = "";
        m_imageURL = "";
        m_content = "";
    }
};

struct TransformationStruct{
    
    std::string m_characterName;
    std::string m_urlSeason1;
    std::string m_urlSeason2;
    std::string m_urlSeason3;
    std::string m_urlSeason4;
    std::string m_urlSeason5;
    std::string m_urlSeason6;
    std::string m_urlSeason7;
    std::string m_urlSeason8;
    std::string m_urlSeason9;
    std::string m_urlSeason10;
    
    TransformationStruct(){
        
        m_characterName = "";
        m_urlSeason1 = "";
        m_urlSeason2 = "";
        m_urlSeason3 = "";
        m_urlSeason4 = "";
        m_urlSeason5 = "";
        m_urlSeason6 = "";
        m_urlSeason7 = "";
        m_urlSeason8 = "";
        m_urlSeason9 = "";
        m_urlSeason10 = "";
    }
};



struct LevelDetailStruct{
    
    std::string m_level;
    int m_currentQuestions;
    int m_totalQestions;
    std::string m_levelName;
    bool isLocked;
    
    LevelDetailStruct(){
        
        m_level = "";
        m_levelName = "";
        m_currentQuestions = 0;
        m_totalQestions = 0;
        isLocked = true;
        
    }
};

struct QuestionStruct{
    
    std::string m_question;
    std::string m_optionA;
    std::string m_optionB;
    std::string m_optionC;
    std::string m_optionD;
    std::string m_answer;
    
    QuestionStruct(){
        m_question = "";
        m_optionA = "";
        m_optionB = "";
        m_optionC = "";
        m_optionD = "";
        m_answer = "";
    }
};

enum CONTENT_TYPE{
    CONTENT_LATEST_POST,
    CONTENT_SSB_GUIDE,
    CONTENT_NOTIFICATIONS
};

#endif // __COMMONCLASSES_H__
