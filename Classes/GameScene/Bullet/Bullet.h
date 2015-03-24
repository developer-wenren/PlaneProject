//
//  Bullet.h
//  Plane
//
//  Created by 软件开发 on 15/3/24.
//
//

#ifndef __Plane__Bullet__
#define __Plane__Bullet__

#include <stdio.h>

#include "cocos2d.h"

USING_NS_CC;

#endif /* defined(__Plane__Bullet__) */


class Bullet: public CCSprite
{
private:
    
    int bullet_type;
    
    float bullet_speed;
    
    void move(float dt);
    
    void removeBullet();
    
    
public:
    
    static Bullet *createBullet(int bulletType);
    
    bool initBullet(int bulletType);
    
    CC_SYNTHESIZE_READONLY(int, bullet_attack, Attack);
    
    
    
    
};