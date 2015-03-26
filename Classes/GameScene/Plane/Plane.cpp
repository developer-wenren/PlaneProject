//
//  Plane.cpp
//  Plane
//
//  Created by 软件开发 on 15/3/24.
//
//

#include "Plane.h"
#include "Define.h"
#include "GameLayer.h"


Plane* Plane::creatPlane(int type)
{
    
    Plane *plane = new Plane;
    
    if (plane && plane->initPlane(type))
    {
        
        plane->autorelease();

        return plane;
        
    }
    
    CC_SAFE_DELETE(plane);
    
    return NULL;
}

bool Plane:: initPlane(int type)
{
    
    bool isDone = CCSprite:: initWithSpriteFrameName(CCString::createWithFormat("role%d.png",type)->getCString()) ? true:false;
    
    if (isDone)
    {
        plane_type = type;

        plane_level = 1;
        
        this->addFire();
        
        CCDelayTime *delay = CCDelayTime::create(.5);
        CCCallFunc *callBack = CCCallFunc::create(this, callfunc_selector(Plane::bulletScheduleBegin));
        CCSequence *seq = CCSequence::create(delay,callBack,NULL);
        
        this->runAction(seq);
        

    }
    
    return isDone;
    
}

void Plane::addFire()
{
    
    CCSprite *fire = CCSprite::create();
    
    CCAnimation *fire_animation = CCAnimation::create();
    
    for (int i = 0; i<4; i++)
    {
        const char *fire_name = CCString::createWithFormat("role_fire%d.png",i)->getCString();
        
        CCSpriteFrame *fireFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fire_name);
        
        fire_animation ->addSpriteFrame(fireFrame);
        
        
    }
    
    fire_animation ->setDelayPerUnit(.08);
    
    fire_animation ->setLoops(-1);
    
    CCAnimate *fire_animate = CCAnimate::create(fire_animation);
    
    fire->runAction(fire_animate);
    
    this->addChild(fire);
    
    fire->setPosition(ccp(30, -30));
}

void Plane::shotBullet(float dt)
{
   
    GameLayer *gameLayer = (GameLayer *)this->getParent();
    
    gameLayer->GameLayer::shootBullet();
    
}

void Plane::upLevel(int upNum)
{
    plane_level+=upNum;
    
}

void Plane::bulletScheduleBegin()
{
    this->schedule(schedule_selector(Plane::shotBullet),1);

}
