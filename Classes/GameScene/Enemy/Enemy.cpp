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
            m_hp = 2;
            _score = 200;
            break;
        case ENEMY3:
            m_hp = 3;
            _score = 250;
            break;
        case ENEMY4:
            _score = 350;
            m_hp = 4;

            break;

    }
    
    max_hp = m_hp;
    
    m_speed = rand()%5+3;
    
    this->schedule(schedule_selector(Enemy::move));
    
    this->setupBloodBar();

    return true;
 
}

void Enemy::setupBloodBar()
{
    CCSprite *blood2 = CCSprite::create("progress2.png");
    
    CCSprite *blood1 = CCSprite::create("progress1.png");
    
    
    progress = CCProgressTimer::create(blood2);
    
    progress->setType(kCCProgressTimerTypeBar);
    progress->setMidpoint(CCPointZero);
    progress->setBarChangeRate(ccp(1,0));
    progress->setPercentage(100);

    this->addChild(blood1);

    this->addChild(progress);
    

    blood1->setPosition(ccp(this->getContentSize().width*.5, this->getContentSize().height));
    progress->setPosition(ccp(this->getContentSize().width*.5, this->getContentSize().height));
    
}

void Enemy:: harm(int harmHurt)
{
    this->stopAllActions();

    CCBlink *blink = CCBlink::create(.5, 3);
    
    this->runAction(blink);

    m_hp -= harmHurt;
    
    progress->setPercentage(100*m_hp/max_hp);
    
    
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
        this->removeEnemy();
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
    _isDie = true;

    this->removeFromParent();
    
}
