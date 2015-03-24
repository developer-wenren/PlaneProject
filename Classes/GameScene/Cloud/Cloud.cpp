//
//  Cloud.cpp
//  Plane
//
//  Created by 软件开发 on 15/3/24.
//
//

#include "Cloud.h"

bool Cloud:: init()
{
    if (!CCSprite::initWithFile("img_cloud_1.png"))
    {
        return false;
        
    }
    
    int num = rand()%2;
    
    if (0 == num)
    {
        this->setScale(.7);
        cloud_speed = 3;
        this->setZOrder(-10);
        
    }else
    {
        this->setScale(1.2);
        cloud_speed = 6;
        this->setZOrder(10);
        
    }
    
    this->schedule(schedule_selector(Cloud::move));
    
    return true;
    
}

void Cloud::move(float dt)
{
    this->setPositionY(this->getPositionY()-cloud_speed);
    
    if (this->getPositionY()<= -this->getContentSize().height*.5)
    {
        this->removeCloud();
        
    }
}

void Cloud::removeCloud()
{
    this->removeFromParent();
    
}