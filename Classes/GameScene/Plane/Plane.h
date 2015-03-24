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

#endif /* defined(__Plane__Plane__) */

USING_NS_CC;


class Plane:public CCSprite
{

public:
    
    static Plane* creatPlane(int no);
    
    bool initPlane(int no);
    
    CC_SYNTHESIZE_READONLY(int, plane_level, PlaneLevel); // 声明了一个保护变量，有set,get方法
    
//    int getPlaneLevel()
//    {
//        
//        return plane_level;
//        
//    }
//    
//    void setPlaneLevel(int level)
//    {
//          plane_levle;
//    }
    
    void upLevel(int upNum);
    
    void shotBullet();
    
protected:
    
    int plane_no;
    
//    int plane_level;
    
    
    
};