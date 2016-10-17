//
//  Mask.cpp
//  WhoIsGonnaBeDonkey
//
//  Created by Vary on 10/09/14.
//
//

#include "Mask.h"
USING_NS_CC;


Mask* Mask::single = NULL;

Mask* Mask::getInstance()
{
    if(!single)
        single = new Mask();
    return single;
}

/*Using mask
 auto clippingNode =  Mask::getInstance()->getCircularMask();
 clippingNode->setPosition(Vec2(x,y));
 clippingNode->addChild(sprite);
 addChild(clippingNode,1);
 */

ClippingNode* Mask::getCircularMask(int radius)
{
        
    Size s = Director::getInstance()->getVisibleSize();

    // Create simple triangle from stencil buffer
    DrawNode *stencil = DrawNode::create();
    static Point triangle[3];
    triangle[0] = Point(-100, -100);
    triangle[1] = Point(100, -100);
    triangle[2] = Point(0, 100);

    static Color4F mask = {0, 0, 0, 1};
    
    std::vector<Vec2> vertex;
    float precision = .05f;
    float cir = 10;
    Vec2 mCenter = Vec2(0,0);
    float mRadius = radius;
    for (float a = .0f; a < cir; a += precision) {
        float x = mCenter.x + mRadius * cos(a);
        float y = mCenter.y + mRadius * sin(a);
        vertex.push_back(Vec2(x,y));
    }
    stencil->drawPolygon(&vertex[0], vertex.size(), Color4F(0,0,0,0), 2, Color4F(1,1,1,1));
    
    
//    stencil->drawPolygon(triangle, 3, mask, 0, mask);
//    stencil->drawDot(Vec2(0,0), 50,mask);
//    stencil->setPosition(Point(50, 50));

    // Create the clipping node with stencil buffer
    clipper = ClippingNode::create();
    clipper->setAnchorPoint(Point(0.5, 0.5));
    clipper->setPosition(Point(s.width / 2, s.height / 2));
    clipper->setInverted(false);
    clipper->setStencil(stencil);
    
    return clipper;
}

void Mask::appendCubicBezier(int startPoint, std::vector<Vec2>& verts, const Vec2& from, const Vec2& control1, const Vec2& control2, const Vec2& to, uint32_t segments)
{
    float t = 0;
    for(int i = 0; i < segments; i++)
    {
        float x = powf(1 - t, 3) * from.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * to.x;
        float y = powf(1 - t, 3) * from.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * to.y;
        verts[startPoint + i] = Vec2(x,y);
        t += 1.0f / segments;
    }
}

ClippingNode* Mask::createRoundedRectMaskNode(Size size, float radius, float borderWidth, int cornerSegments)
{
    const float kappa = 0.552228474;
    float oneMinusKappa = (1.0f-kappa);
    
    // define corner control points
    std::vector<Vec2> verts(16);
    
    verts[0] = Vec2(0, radius);
    verts[1] = Vec2(0, radius * oneMinusKappa);
    verts[2] = Vec2(radius * oneMinusKappa, 0);
    verts[3] = Vec2(radius, 0);
    
    verts[4] = Vec2(size.width - radius, 0);
    verts[5] = Vec2(size.width - radius * oneMinusKappa, 0);
    verts[6] = Vec2(size.width, radius * oneMinusKappa);
    verts[7] = Vec2(size.width, radius);
    
    verts[8] = Vec2(size.width, size.height - radius);
    verts[9] = Vec2(size.width, size.height - radius * oneMinusKappa);
    verts[10] = Vec2(size.width - radius * oneMinusKappa, size.height);
    verts[11] = Vec2(size.width - radius, size.height);
    
    verts[12] = Vec2(radius, size.height);
    verts[13] = Vec2(radius * oneMinusKappa, size.height);
    verts[14] = Vec2(0, size.height - radius * oneMinusKappa);
    verts[15] = Vec2(0, size.height - radius);
    
    // result
    std::vector<Vec2> polyVerts(4 * cornerSegments + 1);
    
    // add corner arc segments
    appendCubicBezier(0 * cornerSegments, polyVerts, verts[0], verts[1], verts[2], verts[3], cornerSegments);
    appendCubicBezier(1 * cornerSegments, polyVerts, verts[4], verts[5], verts[6], verts[7], cornerSegments);
    appendCubicBezier(2 * cornerSegments, polyVerts, verts[8], verts[9], verts[10], verts[11], cornerSegments);
    appendCubicBezier(3 * cornerSegments, polyVerts, verts[12], verts[13], verts[14], verts[15], cornerSegments);
    // close path
    polyVerts[4 * cornerSegments] = verts[0];
    
    // draw final poly into mask
    auto shapeMask = DrawNode::create();
    shapeMask->drawPolygon(&polyVerts[0], (int)polyVerts.size(), Color4F::YELLOW, 0.0f, Color4F::YELLOW);
    
    // create clip node with draw node as stencil (mask)
    return ClippingNode::create(shapeMask);
}

cocos2d::ClippingNode* Mask::getRoundedCornerMask(cocos2d::Size maskSize, int radius) {
    //createRoundedRectMaskNode(Size size, float radius, float borderWidth, int cornerSegments)
    
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    return createRoundedRectMaskNode(maskSize, radius, 1.0f, 10);
}
