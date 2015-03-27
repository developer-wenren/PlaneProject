//
//  Plane.h
//  Plane
//
//  Created by 软件开发 on 15/3/24.
//
//

#ifndef __Plane__Plane__
#define __Plane__Plane__

#include <stdio.h>
#include "cocos2d.h"





USING_NS_CC;


class Plane:public CCSprite
{

public:
    
    static Plane* creatPlane(int type);
    
    bool initPlane(int type);
    
    CC_SYNTHESIZE_READONLY(int, plane_level, PlaneLevel); // 声明了一个保护变量，有set,get方法
    
    void upLevel(int upNum);
    
    void shotBullet(float dt);
    
    void addFire();
    
    CCRect planeBoundingBox();
//    void onEnterTransitionDidFinish();
    
protected:
    
    int plane_type;
    
    void bulletScheduleBegin();
    
    
};

#endif /* defined(__Plane__Plane__) */