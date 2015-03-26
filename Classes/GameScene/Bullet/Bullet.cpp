//
//  Bullet.cpp
//  Plane
//
//  Created by 软件开发 on 15/3/24.
//
//

#include "Bullet.h"
#include "Define.h"



Bullet *Bullet::createBullet(int bulletLevel,int bulletType)
{
    
    Bullet *bullet = new  Bullet;
    
    if (bullet&& bullet->initBullet(bulletLevel, bulletType))
    {
        
        bullet->autorelease();
        
        return bullet;
        
    }
    
    CC_SAFE_DELETE(bullet);
    
    return NULL;
    
}

bool Bullet::initBullet(int bulletLevel,int bulletType)
{
    
    if (! CCSprite::initWithSpriteFrameName(CCString::createWithFormat("%d_%d.png",bulletType,bulletLevel)->getCString()))
    {
        return false;
    }
    
    _isDie = false;
    
    bullet_attack = bulletLevel;
    
    bullet_speed = 10+.03*bulletLevel;
    
    this->schedule(schedule_selector(Bullet::move));
    
    return true;
    
}


void Bullet:: move(float dt)
{
    this->setPositionY(this->getPositionY()+bullet_speed);
    
    if (this->getPositionY() >= (WINSIZE.height+ this -> getContentSize().height*.5))
    {
        
        CCLog("removeBullet");
        
        this->die();
        
    }
    
}

void Bullet::die()
{
    _isDie = true;
    this->removeFromParent();


}