//
//  Bullet.cpp
//  Plane
//
//  Created by 软件开发 on 15/3/24.
//
//

#include "Bullet.h"
#include "Define.h"

Bullet *Bullet::createBullet(int bulletType)
{
    
    Bullet *bullet = new  Bullet;
    
    if (bullet&& bullet->initBullet(bulletType))
    {
        
        bullet->autorelease();
        
        return bullet;
        
    }
    
    CC_SAFE_DELETE(bullet);
    
    return NULL;
    
}

bool Bullet::initBullet(int bulletType)
{
    
    bool isDone = CCSprite::initWithSpriteFrameName(CCString::createWithFormat("1_%d.png",bulletType)->getCString())? true:false;
    
    if (isDone)
    {

        bullet_attack = bullet_type;
        
        bullet_speed = 10+.1*bullet_type;
        
        this->schedule(schedule_selector(Bullet::move));
        
        
    }
    
    return isDone;
    
}


void Bullet:: move(float dt)
{
    this->setPositionY(this->getPositionY()+bullet_speed);
    
    if (this->getPositionY() >= WINSIZE.height+this->getContentSize().height*.5)
    {
        this->removeBullet();
    }
    
}

void Bullet:: removeBullet()
{
    this->removeFromParent();
    
}