//
//  GameLayer.h
//  Plane
//
//  Created by 软件开发 on 15/3/23.
//
//

#ifndef __Plane__GameLayer__
#define __Plane__GameLayer__

#include <stdio.h>

#include "Define.h"

#include "cocos2d.h"

#include "Plane.h"

#include "Bullet.h"

#include "Enemy.h"

#endif /* defined(__Plane__GameLayer__) */

USING_NS_CC;

class GameLayer: public CCLayer
{
    
public:
    
    ~GameLayer();
    
    static GameLayer *createGameLayer(int level);
    
    bool initGameLayer(int level);
    
    virtual void onEnterTransitionDidFinish();
    
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    void shootBullet();
    
    void addCloud(float dt);
    
    void addEnemy(float dt);
    
    Plane *plane;
    
protected:
    
    CCArray *m_bullets;
    
    CCArray *m_enemys;
    
    CCArray *m_props;
    
    CCPoint begin_positon;
    
    int aLevel;
    
    int _score;
    
    CCLabelBMFont *_scoreFont;
    
    
    void addPlane(int type);
    
    void bulletAndEnemyCollision();
    
    void openTouch();
    
    void removeBullet();
    
    void removeEnemy();
    
    void removeProp();
    
    void addScore(int addNum);
  
    void setupScoreLabel();
    
    void winGame();
    
    void loseGame();
    
    void pauseGame(CCNode *);
    
    void addWinLayer();
    
    void addWinLayer2();
    
    void hideSprites();
    
    void hideSprites2();

    
    void goNextScene();
    
    void addProp(float dt);
    
    void propAndPlaneCollision();
    
    void planeAndEnemyCollision();
};