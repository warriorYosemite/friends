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

enum CONTENT_TYPE{
    CONTENT_LATEST_POST,
    CONTENT_SSB_GUIDE,
    CONTENT_NOTIFICATIONS
};

#endif // __COMMONCLASSES_H__
