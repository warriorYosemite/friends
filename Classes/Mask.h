//
//  Mask.h
//  WhoIsGonnaBeDonkey
//
//  Created by Vary on 10/09/14.
//
//

#ifndef __WhoIsGonnaBeDonkey__Mask__
#define __WhoIsGonnaBeDonkey__Mask__

#include "cocos2d.h"
#include <iostream>

class Mask{
    cocos2d::ClippingNode *clipper;
    
    void appendCubicBezier(int startPoint, std::vector<cocos2d::Vec2>& verts, const cocos2d::Vec2& from, const cocos2d::Vec2& control1, const cocos2d::Vec2& control2, const cocos2d::Vec2& to, uint32_t segments);
    cocos2d::ClippingNode* createRoundedRectMaskNode(cocos2d::Size size, float radius, float borderWidth, int cornerSegments);
    
public:
    
    //--Returns the instance of the singleton class
    static Mask* getInstance();
        
    //--Single copy of Table, returned as an instance through getInstance.
    static Mask* single;
    
    cocos2d::ClippingNode* getCircularMask(int radius);
    cocos2d::ClippingNode* getRoundedCornerMask(cocos2d::Size maskSize, int radius);
};

#endif /* defined(__WhoIsGonnaBeDonkey__Mask__) */
