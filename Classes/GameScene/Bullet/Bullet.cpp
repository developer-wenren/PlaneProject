//
//  Bullet.cpp
//  Plane
//
//  Created by 软件开发 on 15/3/24.
//
//

#include "Bullet.h"
#include "Define.h"



Bullet *Bullet::createBullet(int bulletLevel)
{
    
    Bullet *bullet = new  Bullet;
    
    if (bullet&& bullet->initBullet(bulletLevel))
    {
        
        bullet->autorelease();
        
        return bullet;
        
    }
    
    CC_SAFE_DELETE(bullet);
    
    return NULL;
    
}

bool Bullet::initBullet(int bulletLevel)
{
    
    if (! CCSprite::initWithSpriteFrameName(CCString::createWithFormat("1_%d.png",bulletLevel)->getCString()))
    {
        return false;
    }
    
    this->setBulletDie(false);
    
    bullet_attack = bulletLevel;
    
    bullet_speed = 20+.03*bulletLevel;
    
    this->schedule(schedule_selector(Bullet::move));
    
    return true;
    
}


void Bullet:: move(float dt)
{
    this->setPositionY(this->getPositionY()+bullet_speed);
    
    if (this->getPositionY() >= (WINSIZE.height+ this -> getContentSize().height*.5))
    {
        
//        CCLog("removeBullet");
        this->die();
        
        this->removeBullet();
    }
    
}

void Bullet:: removeBullet()
{
    this->removeFromParent();
    
}

void Bullet::die()
{
    
}