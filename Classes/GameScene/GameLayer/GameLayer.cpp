//
//  GameLayer.cpp
//  Plane
//
//  Created by 软件开发 on 15/3/23.
//
//

#include "GameLayer.h"
#include "Cloud.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

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
        m_bullets = CCArray::create(); // count -> 0
        
        m_bullets->retain(); // count -> 1
        
        m_enemys = CCArray::create();
        
        CC_SAFE_RETAIN(m_enemys);
        
    }

    

    return isDone;
    
}

void GameLayer::addPlane(int type)
{
    plane = Plane::creatPlane(type);
    
    plane->setPosition(ccp(WINSIZE.width*.5, -plane->getContentSize().height*.5));

    CCFadeIn *fadeIn = CCFadeIn::create(1.5);
    
    CCRotateBy *rotate = CCRotateBy::create(1.0, 0, -720);
    
        CCSpawn *spawn = CCSpawn::create(rotate,CCMoveTo::create(1, WIN_PISITION(.5, .2)),fadeIn,NULL);

    CCSequence *sequence = CCSequence::create(spawn,CCCallFunc::create(this, callfunc_selector(GameLayer::openTouch)),NULL);
    
    plane->runAction(sequence);
    
    this->addChild(plane);
    
}

void GameLayer::addCloud(float dt)
{
    Cloud *cloud = Cloud::create();
    
    this->addChild(cloud);
    
    float x = CCRANDOM_0_1() *WINSIZE.width;
    
    float y = WINSIZE.height + cloud->getContentSize().height*.5;
    
    cloud->setPosition(ccp(x, y));
    
    
}

void GameLayer::addEnemy(float dt)
{
//    int type = rand() % ENEMY_COUNT;
    
    Enemy *enemy = Enemy::createEnemy(ENEMY1);
    float x = CCRANDOM_0_1() * WINSIZE.width;
    float y = WINSIZE.height + enemy->getContentSize().height * 0.5;
    enemy->setPosition(ccp(x,y));
    this->addChild(enemy);
    //把敌人加到数组中
    m_enemys->addObject(enemy);
}


void GameLayer::shootBullet()
{
    
    Bullet *bullet = Bullet::createBullet(1);
    
    bullet->setZOrder(-1);
    
    bullet->setPosition(plane->getPosition());
    
    this->addChild(bullet);
    
    m_bullets->addObject(bullet);
    
    SimpleAudioEngine::sharedEngine()->playEffect("effect_bullet.mp3");

}

void GameLayer:: bulletAndEnemyCollision()
{
    for (int i = 0; i<m_bullets->count(); i++)
    {
        Bullet *bullet = (Bullet *)m_bullets->objectAtIndex(i);
        
        if (!bullet->getBulletDie())
        {
            for (int j = 0; j<m_enemys->count(); j++)
            {
                Enemy *enemy = (Enemy *)m_enemys->objectAtIndex(j);
                
                //  左下角为起始点
                if (bullet->boundingBox().intersectsRect(enemy->boundingBox()))
                {
                    //remove
                    
                    
                    
                    bullet->die();
                    
                }
                
                
            }
        }
        
        
    }
}

void GameLayer:: removeBullet()
{
    //  需要移除的子弹 数组
    CCArray *removeArray = CCArray::create();
    
    for (int i = 0; i<m_bullets->count(); i++)
    {
        Bullet *dieBullet = (Bullet *)m_enemys->objectAtIndex(i);
        
        if (dieBullet->getBulletDie())
        {
            removeArray->addObject(dieBullet);
            
        }
    }
    
    for (int j = 0;j<removeArray->count();j++)
    {
        Bullet *removeBullet = (Bullet *)removeArray->objectAtIndex(j);
        
        this->removeChild(removeBullet);
        
        m_bullets->removeObject(removeBullet);
    }

    removeArray->removeAllObjects();
    
}

#pragma mark -touchSetting

void GameLayer::openTouch()
{
    
    this->setTouchEnabled(true);    // 有飞机的前提下才能触摸
    
    this->setTouchMode(kCCTouchesOneByOne);
    
}

bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    
    begin_positon = pTouch->getLocation();
    
    return true;
    
}

void GameLayer:: ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
    CCPoint move_position = pTouch->getLocation()-begin_positon;
    
    plane->setPosition(plane->getPosition()+move_position);
    
#warning 飞机的边界处理--------------------------------------
    
    begin_positon = pTouch->getLocation();
    
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



void GameLayer::onEnterTransitionDidFinish()
{
//    CCLayer::onEnterTransitionDidFinish();
    
    this->addPlane(PLANE_TYPE);
    
//    this->schedule(schedule_selector(GameLayer::addCloud),2);
    
    this->schedule(schedule_selector(GameLayer::addEnemy),2);
    
    this->schedule(schedule_selector(GameLayer::bulletAndEnemyCollision));

}

GameLayer::~GameLayer()
{
    m_enemys->release();
    
    m_bullets->release();
    
}


