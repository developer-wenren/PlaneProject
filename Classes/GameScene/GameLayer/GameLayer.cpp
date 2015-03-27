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
#include "GameScene.h"
#include "Prop.h"

#include "MenuLayer.h"

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
        
        m_props = CCArray::create();
        
        m_props->retain();
        
        aLevel = level;
        
        CC_SAFE_RETAIN(m_enemys);
        
        this->setupScoreLabel();
        
    }

    

    return isDone;
    
}

#pragma mark  添加飞机，云，敌人, 道具

void GameLayer::addProp(float dt)
{
    Prop *prop = Prop::create();
    
    this->addChild(prop);
    
    prop->setPosition(ccp(CCRANDOM_0_1()*WINSIZE.width, WINSIZE.height+prop->getContentSize().height*.5));
    
    m_props->addObject(prop);
    
    
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
    int type = rand() % ENEMY_COUNT;
    
    Enemy *enemy = Enemy::createEnemy((EnemyType)type);
    float x = CCRANDOM_0_1() * WINSIZE.width;
    float y = WINSIZE.height + enemy->getContentSize().height * 0.5;
    if (x<= enemy->getContentSize().width*.5)
    {
        x = enemy->getContentSize().width*5;
    }
    
    if (x>=WINSIZE.width-enemy->getContentSize().width*.5)
    {
        x= WINSIZE.width-enemy->getContentSize().width*.5;
    }
    enemy->setPosition(ccp(x,y));
    this->addChild(enemy);
    //把敌人加到数组中
    m_enemys->addObject(enemy);
}


void GameLayer::shootBullet()
{
    
    Bullet *bullet = Bullet::createBullet(plane->getPlaneLevel(),BULLET_TYPE);
    
    bullet->setZOrder(-1);
    
    bullet->setPosition(plane->getPosition());
    
    this->addChild(bullet);
    
    m_bullets->addObject(bullet);
    
    SimpleAudioEngine::sharedEngine()->playEffect("effect_bullet.mp3");

}



#pragma mark  碰撞检测 ，移除飞机，敌人

void GameLayer:: planeAndEnemyCollision()
{
//    CCLog("plane x-%f,y-%f",plane->getPositionX(),plane->getPositionY());
    
    for (int i = 0; i<m_enemys->count(); i++)
    {
        Enemy *enemy = (Enemy *)m_enemys->objectAtIndex(i);
        
        if (enemy->boundingBox().intersectsRect(plane->planeBoundingBox()))
        {
            this->loseGame();
        }

    }
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
                
                if (!enemy->getDie())
                {
                    //  左下角为起始点
                    if (bullet->bulletBoundingBox().intersectsRect(enemy->boundingBox()))
                    {
                        //remove
                        
                        CCLog("hit---");
                        
                        SimpleAudioEngine::sharedEngine()->playEffect("effect_boom.mp3");
                        
                        enemy->harm(bullet->getAttack());
                        
                        bullet->die();
//                        bullet->willDie();
                        
                        
                    }
                    
                }
                
            }
            
        }
        
    }
}

void GameLayer::propAndPlaneCollision()
{
    
    
    
    for (int i = 0; i<m_props->count(); i++)
    {
        Prop *prop = (Prop *)m_props->objectAtIndex(i);
        
        if (!prop->getEat())
        {
            if (prop->boundingBox().intersectsRect(plane->boundingBox()))
            {
               
                CCLog("eat");

//                prop->Die();
                prop->willDie(); // 先做动作再死
                
                plane->upLevel(prop->getPower());
                

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
        Bullet *dieBullet = (Bullet *)m_bullets->objectAtIndex(i);
        
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

void GameLayer::removeProp()
{
    //  需要移除的道具 数组
    CCArray *removeArray = CCArray::create();
    
    /**
     *  宏遍历写法
     */
//    CCObject *Obj;
//    CCARRAY_FOREACH(removeArray, Obj);
    
    
    for (int i = 0; i<m_props->count(); i++)
    {
        Prop *dieProp = (Prop *)m_props->objectAtIndex(i);
        
        if (dieProp->getDie())
        {
            removeArray->addObject(dieProp);
            
        }
    }
    
    for (int j = 0;j<removeArray->count();j++)
    {
        Prop *removeProp = (Prop *)removeArray->objectAtIndex(j);
        
        this->removeChild(removeProp);
        
        m_props->removeObject(removeProp);
        
    }
    
    removeArray->removeAllObjects();
    
}

void GameLayer::removeEnemy()
{
    //  需要移除的enemy 数组
    CCArray *removeArray = CCArray::create();
    
    for (int i = 0; i<m_enemys->count(); i++)
    {
        Enemy *dieEnemy = (Enemy *)m_enemys->objectAtIndex(i);
        
        if (dieEnemy->getDie())
        {
            removeArray->addObject(dieEnemy);
            
        }
    }
    
    for (int j = 0;j<removeArray->count();j++)
    {
        Enemy *removerEnemy = (Enemy *)removeArray->objectAtIndex(j);

        
        if (removerEnemy->getBeat())
        {
            this->addScore(removerEnemy->getScore());
        }
        
        this->removeChild(removerEnemy);
        
        m_enemys->removeObject(removerEnemy);

        
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

#pragma mark  ScoreLabel Setting

void GameLayer:: setupScoreLabel()
{
    _score = 0;
    
    _scoreFont = CCLabelBMFont::create("0", "MyFont.fnt");
    
    _scoreFont->setAnchorPoint(ccp(0,1));
    
    _scoreFont->setPosition(0, WINSIZE.height);
    
    this->addChild(_scoreFont);
    
}

void GameLayer:: addScore(int addNum)
{
    _score +=addNum;
    
    _scoreFont->setString(CCString::createWithFormat("%d",_score)->getCString());
    
    if (_score >= SCORE_GOAL)
    {
        this->winGame();
    }
    
}

#pragma mark  游戏暂停

void GameLayer::loseGame()
{
    
    CCLog("die------------die");
    
    this->pauseGame(DIRECTOR->getRunningScene());

    this->setTouchEnabled(false);

    AUDIO_SYSTEM_CC->stopBackgroundMusic();

    this->hideSprites2();
    
    this->addWinLayer2();
    
    
}

void GameLayer::winGame()
{
    this->pauseGame(DIRECTOR->getRunningScene());
    
    this->setTouchEnabled(false);
    
    AUDIO_SYSTEM_CC->stopBackgroundMusic();
    
    this->hideSprites();

}

void GameLayer:: pauseGame(CCNode *node)
{
    
    int count = node->getChildrenCount();
    
    for (int i = 0; i<count; i++)
    {
        CCNode *child =(CCNode *)node->getChildren()->objectAtIndex(i);
        
        this->pauseGame(child);
    }
    
    node->unscheduleAllSelectors();
    
}

void GameLayer:: addWinLayer2()
{
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 125));
    
    //    CCLayerGradient
    
    DIRECTOR->getRunningScene()->addChild(layer);
    
    CCMenu *menu = CCMenu::create();
    
    aLevel = 6;
    CCMenuItemImage *image = CCMenuItemImage::create("game_lost.png", NULL, this, menu_selector(GameLayer::goNextScene));
    
    menu->addChild(image);
    
    layer->addChild(menu);
}

void GameLayer:: addWinLayer()
{
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 125));
    
    //    CCLayerGradient
    
    DIRECTOR->getRunningScene()->addChild(layer);
    
    CCMenu *menu = CCMenu::create();
    
    CCMenuItemImage *image = CCMenuItemImage::create("game_win.png", NULL, this, menu_selector(GameLayer::goNextScene));
 
    menu->addChild(image);
    
    layer->addChild(menu);
    
}

void GameLayer::hideSprites2()
{
    
//    CCMoveTo *moveTo = CCMoveTo::create(1, ccp(plane->getPositionX(), WINSIZE.height+100));
//    
//    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GameLayer::addWinLayer));
//    
//    CCSequence *seq = CCSequence::create(moveTo,callFunc);
//    plane->runAction(seq);
    
    for (int i = 0; i<m_enemys->count(); i++)
    {
        Enemy *enemy = (Enemy *)m_enemys->objectAtIndex(i);
        
        enemy->setVisible(false);
        
    }
    
    for (int i = 0; i<m_bullets->count(); i++)
    {
        Bullet *enemy = (Bullet *)m_bullets->objectAtIndex(i);
        
        enemy->setVisible(false);
        
    }
    
    for (int i = 0; i<m_props->count(); i++)
    {
        Prop *prop = (Prop *)m_props->objectAtIndex(i);
        
        prop->setVisible(false);
        
    }
    
    
    
}

void GameLayer::hideSprites()
{
    CCMoveTo *moveTo = CCMoveTo::create(1, ccp(plane->getPositionX(), WINSIZE.height+100));
    
    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GameLayer::addWinLayer));
    
    CCSequence *seq = CCSequence::create(moveTo,callFunc);
    
    plane->runAction(seq);
    
    for (int i = 0; i<m_enemys->count(); i++)
    {
        Enemy *enemy = (Enemy *)m_enemys->objectAtIndex(i);
        
        enemy->setVisible(false);
        
    }
    
    for (int i = 0; i<m_bullets->count(); i++)
    {
        Bullet *enemy = (Bullet *)m_bullets->objectAtIndex(i);
        
        enemy->setVisible(false);
        
    }
    
    for (int i = 0; i<m_props->count(); i++)
    {
        Prop *prop = (Prop *)m_props->objectAtIndex(i);
        
        prop->setVisible(false);
        
    }

}

#pragma mark 场景切换 onEnter

void GameLayer::onEnterTransitionDidFinish()
{
    
    //        CCLayer::onEnterTransitionDidFinish();
    
    this->addPlane(PLANE_TYPE);

    this->schedule(schedule_selector(GameLayer::addProp),5);

    this->schedule(schedule_selector(GameLayer::addCloud),2);
    
    this->schedule(schedule_selector(GameLayer::addEnemy),1);
    
    this->schedule(schedule_selector(GameLayer::bulletAndEnemyCollision));
    
    this->schedule(schedule_selector(GameLayer::removeBullet));
    
    this->schedule(schedule_selector(GameLayer::removeEnemy));
 
    this->schedule(schedule_selector(GameLayer::propAndPlaneCollision));

    this->schedule(schedule_selector(GameLayer::planeAndEnemyCollision));
    
}

void GameLayer::goNextScene()
{

    CCLOG("%d",aLevel);
    
    if (aLevel<5)
    {
        DIRECTOR->replaceScene(CCTransitionFlipX::create(1, GameScene::createGameScene(++aLevel)));
    }else
    {

#warning 返回主界面--------------------------------------
                CCLOG("---------------");
        CCScene *scene = MenuLayer::scene(GAME_LEVEL);
        
        DIRECTOR->replaceScene(scene);
        
        
    }
    

}


GameLayer::~GameLayer()
{
    m_enemys->release();
    
    m_bullets->release();
    
    m_props->release();
    
}



