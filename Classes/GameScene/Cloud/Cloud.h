//
//  Cloud.h
//  Plane
//
//  Created by 软件开发 on 15/3/24.
//
//

#ifndef __Plane__Cloud__
#define __Plane__Cloud__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;




class Cloud: public CCSprite
{
    float cloud_speed;
    
    void move(float dt);
    
    void removeCloud();
    
public:
    
    CREATE_FUNC(Cloud);
    
    bool init();
    
};


#endif /* defined(__Plane__Cloud__) */
