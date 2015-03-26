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
    
    if (!CCSprite::initWithFile(imageName))
    {
    
        return false;
        
    }
    
//    this->setDie(false);
    _isDie = false;
    
    _isBeat = false;
    
    switch ((int)type)
    {
        case ENEMY1:
            m_hp = 1;
            _score = 100;
            break;
        case ENEMY2:
            m_hp = 1;
            _score = 200;
            break;
        case ENEMY3:
            m_hp = 1;
            _score = 300;
            break;
        case ENEMY4:
            _score = 50;
            m_hp = 1;

            break;

    }
    
    m_speed = rand()%5+3;
    
    this->schedule(schedule_selector(Enemy::move));

    return true;
 
}

void Enemy:: harm(int harmHurt)
{
    this->stopAllActions();

    CCBlink *blink = CCBlink::create(.5, 3);
    
    this->runAction(blink);

    m_hp -= harmHurt;
    
    if (m_hp<=0)
    {
        this->dieEnemy();
        
        _isBeat = true;
        
    }
}


void Enemy:: move(float dt)
{
    this->setPositionY(this->getPositionY()-m_speed);
    
    if (this->getPositionY()<= -this->getContentSize().height*.5)
    {
        this->dieEnemy();
    }
}

void Enemy:: dieEnemy()
{
    
#warning 爆炸
    _isDie = true;
    
    CCParticleSystemQuad *system = CCParticleSystemQuad::create("particle_boom.plist");
    
    this->getParent()->addChild(system);
    
    system->setPosition(this->getPosition());
    
    system->setAutoRemoveOnFinish(true);    //自动销毁例子对象
    
//    this->removeEnemy();
    
}

void Enemy:: removeEnemy()
{
    this->removeFromParent();
    
}
