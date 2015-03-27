//
//  Prop.cpp
//  Plane
//
//  Created by 软件开发 on 15/3/26.
//
//

#include "Prop.h"


bool Prop::init()
{
    if( !CCSprite::initWithFile("prop.png"))
        return false;
    
    int index = rand()%3;
    
    _speed = rand()%4+2;
    
    _isDie = false;
    
    _isEat = false;
    
    switch (index)
    {
        case 0:
//            this->setColor(ccc3(255, 0, 0));
            _addPower = 1;
            break;
        case 1:
//            this->setColor(ccc3(0, 255, 0));
            _addPower = 1;
            break;
        case 2:
//            this->setColor(ccc3(0, 0, 255));
            _addPower = 1;
            break;
    
    }
    
    CCRotateBy *rotate = CCRotateBy::create(1, 360);
    
    this->runAction(CCRepeatForever::create(rotate));
    
    
    this->schedule(schedule_selector(Prop::move));
    
    return true;
    
}

void Prop::move()
{
    this->setPositionY(this->getPositionY()-_speed);
    if (this->getPositionY()<=-this->getContentSize().height*.5)
    {
        this->Die();
    }
}

void Prop::Die()
{
    _isDie = true;
    
    this->removeFromParent();
    
}

void Prop::willDie()
{
    this->setEat(true);
    
    this->unschedule(schedule_selector(Prop::move));
    
    CCScaleTo *scale = CCScaleTo::create(.5, .5);
    
    CCFadeOut *fadeOut = CCFadeOut::create(.5);
    
    CCSpawn *spawn = CCSpawn::create(scale,fadeOut,NULL);
    
    CCSequence *seq = CCSequence::create(spawn,CCCallFunc::create(this, callfunc_selector(Prop::Die)),NULL);
    
    this->runAction(seq);
    
    
    

}