//
//  Enemy.cpp
//  Plane
//
//  Created by 软件开发 on 15/3/25.
//
//

#include "Enemy.h"


Enemy* Enemy:: createEnemy(EnemyType type)
{
    Enemy *enemy = new Enemy;
    
    if (enemy && enemy->initEnemy(type) )
    {
        enemy->autorelease();
        
        return enemy;
    }
    
    CC_SAFE_DELETE(enemy);
    
    return NULL;
    
}

bool Enemy:: initEnemy(EnemyType type)
{
    //(->getCString) = CCString::createWithFormat("enemy_%d",enemyType+1)->getCString();

    const char* imageName = CCString::createWithFormat("enemy_%d.png", type + 1)->getCString();
    
    if (!CCSprite::initWithFile("enemy_1"))
    {
    
        return false;
        
    }
    
    
    switch ((int)type)
    {
        case ENEMY1:
            m_hp = 1;
            break;
        case ENEMY2:
            m_hp = 2;
            break;
        case ENEMY3:
            m_hp = 3;
            break;
        case ENEMY4:
            m_hp = 4;

            break;

    }
    
    m_speed = rand()%5+3;
    
    this->schedule(schedule_selector(Enemy::move));

    CCLog("enemy init");
    
    
    return true;
    
    
    
}

void Enemy:: harm(int harmHurt)
{
    m_hp-=harmHurt;
    
    if (m_hp<=0)
    {
        this->dieEnemy();
        
    }
}


void Enemy:: move(float dt)
{
    this->setPositionX(this->getPositionY()-m_speed);
    
    if (this->getPositionY() <= -this->getContentSize().height*.5)
    {
        this->dieEnemy();
    }
}

void Enemy:: dieEnemy()
{
    
#warning 爆炸
    
    this->removeEnemy();
    
}

void Enemy:: removeEnemy()
{
    this->removeFromParent();
    
}
