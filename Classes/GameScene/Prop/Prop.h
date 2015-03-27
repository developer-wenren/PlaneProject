//
//  Prop.h
//  Plane
//
//  Created by 软件开发 on 15/3/26.
//
//

#ifndef __Plane__Prop__
#define __Plane__Prop__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;


class Prop:public CCSprite
{
    
    float _speed;
    
public:
    
    CREATE_FUNC(Prop);
    
    bool init();
    
    void move();
    
    void Die();
    
    void willDie();

    CC_SYNTHESIZE(int, _addPower, Power);
    
    CC_SYNTHESIZE(bool, _isDie, Die);
    
    CC_SYNTHESIZE(bool, _isEat, Eat);
    
    
};

#endif /* defined(__Plane__Prop__) */
