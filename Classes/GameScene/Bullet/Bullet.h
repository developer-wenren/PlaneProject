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



class Bullet: public CCSprite
{

public:
    
    static Bullet *createBullet(int bulletLevel,int bulletType);
    
    bool initBullet(int bulletLevel,int bulletType);
    
    CC_SYNTHESIZE_READONLY(int, bullet_attack, Attack);
    
    CC_SYNTHESIZE(bool, _isDie, BulletDie);
    
//    CC_SYNTHESIZE(bool, _is, funName)
    
    void die();
    
    CCRect bulletBoundingBox();
    
private:
    
    int bullet_Level;
    
    float bullet_speed;
    
    void move(float dt);
    
    void removeBullet();
    
    
    
};


#endif /* defined(__Plane__Bullet__) */
