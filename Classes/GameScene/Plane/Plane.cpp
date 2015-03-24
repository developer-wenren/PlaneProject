//
//  Plane.cpp
//  Plane
//
//  Created by 软件开发 on 15/3/24.
//
//

#include "Plane.h"
#include "Define.h"


Plane* Plane::creatPlane(int no)
{
    
    Plane *plane = new Plane;
    
    if (plane && plane->initPlane(no))
    {
        
        plane->autorelease();

        return plane;
        
    }
    
    CC_SAFE_DELETE(plane);
    
    return NULL;
}

bool Plane:: initPlane(int no)
{
    
    CCString *plane_name = CCString::createWithFormat("role%d.png",no);
    
    bool isDone = CCSprite:: initWithSpriteFrameName(plane_name->getCString()) ? true:false;
    
    if (isDone)
    {
        plane_no = no;
        
        CCSprite *fire = CCSprite::create();
        
        CCAnimation *fire_animation = CCAnimation::create();
        
        for (int i = 0; i<4; i++)
        {
            const char *fire_name = CCString::createWithFormat("role_fire%d.png",i)->getCString();
            CCSpriteFrame *fireFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fire_name);
            
            fire_animation ->addSpriteFrame(fireFrame);
            
//            CCSpriteFrame
        }
        
        fire_animation ->setDelayPerUnit(.08);
        
        fire_animation ->setLoops(-1);
        
        CCAnimate *fire_animate = CCAnimate::create(fire_animation);
        
        fire->runAction(fire_animate);
        
        this->addChild(fire);
//        fire->seta
        fire->setPosition(ccp(30, -30));
        
        
    }
    
    return isDone;
    
}

void Plane::shotBullet()
{
    
}

void Plane::upLevel(int upNum)
{
    
}

