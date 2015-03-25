//
//  Enemy.h
//  Plane
//
//  Created by 软件开发 on 15/3/25.
//
//

#ifndef __Plane__Enemy__
#define __Plane__Enemy__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

typedef enum {
    
    ENEMY1 = 0,
    ENEMY2,
    ENEMY3,
    ENEMY4,
    ENEMY_COUNT
    
}EnemyType;

#endif /* defined(__Plane__Enemy__) */

class Enemy:public CCSprite
{
    int m_hp;
    
    float m_speed;
    
    void move(float dt);
    
    void removeEnemy();
    
    void dieEnemy();
    
public:

    static Enemy* createEnemy(EnemyType type);
    
    bool initEnemy(EnemyType type);
    
    void harm(int harmHurt);
    
    
};