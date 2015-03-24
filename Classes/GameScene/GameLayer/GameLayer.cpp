//
//  GameLayer.cpp
//  Plane
//
//  Created by 软件开发 on 15/3/23.
//
//

#include "GameLayer.h"



GameLayer* GameLayer::createGameLayer(int level)
{
    
    GameLayer *gameLayer = new GameLayer;
    
    if (gameLayer && gameLayer->initGameLayer(level))
    {
        gameLayer->autorelease();
        
        
        return gameLayer;
    }
    
    CC_SAFE_DELETE(gameLayer);
    
    return NULL;
    
}

bool GameLayer::initGameLayer(int level)
{

    
    bool isDone = CCLayer::init()? true:false;
    
    if (isDone)
    {

        
    }

    

    return isDone;
    
}

void GameLayer::addPlane()
{
    plane = Plane::creatPlane(2);
    
    plane->setPosition(ccp(WINSIZE.width*.5, -plane->getContentSize().height*.5));

    CCSequence *sequence = CCSequence::create(CCMoveTo::create(1, WIN_CENTER),CCCallFunc::create(this, callfunc_selector(GameLayer::openTouch)));
    
    plane->runAction(sequence);
    
    this->addChild(plane);
    
}

void GameLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    
    this->addPlane();

}

void GameLayer::openTouch()
{
    
    this->setTouchEnabled(true);    // 有飞机的前提下才能触摸
    
    this->setTouchMode(kCCTouchesOneByOne);
    
}

bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{

    begin_positon = pTouch->getLocation();
    
//    CCLOG("%f--%f",ponit.x,ponit.y);
    
//    plane->setPosition(ponit);
    
    
    return true;
    
}

void GameLayer:: ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
    CCPoint move_position = pTouch->getLocation()-begin_positon;
    
    
    
    plane->setPosition(plane->getPosition()+move_position);
    
#warning 飞机的边界处理--------------------------------------
    
    begin_positon = pTouch->getLocation();
    
    CCLOG("%f,%f",plane->getPosition().x,plane->getPosition().y);
    
    CCPoint plane_position = plane->getPosition();
    
    if (plane_position.x>WINSIZE.width-plane->getContentSize().width*.5)
    {
        plane->setPosition(ccp(WINSIZE.width-plane->getContentSize().width*.5, plane_position.y));
        
        
        
    }if (plane_position.x < plane->getContentSize().width*.5)
    {
        
        plane->setPosition(ccp(plane->getContentSize().width*.5, plane_position.y));
    }
    
    if (plane_position.y >WINSIZE.height-plane->getContentSize().height* .5)
    {
        
        plane->setPosition(ccp(plane_position.x,WINSIZE.height-plane->getContentSize().height*.5));
        
    }else if (plane_position.y <plane->getContentSize().height* .5)
    {
        
        plane->setPosition(ccp(plane_position.x,plane->getContentSize().height*.5));
    }
    
}

void GameLayer:: ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}


