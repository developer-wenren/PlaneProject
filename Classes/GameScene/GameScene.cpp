//
//  GameScene.cpp
//  Plane
//
//  Created by 软件开发 on 15/3/23.
//
//

#include "GameScene.h"

#include "SimpleAudioEngine.h"

#include "MapLayer.h"

#include "Define.h"

#include "GameLayer.h"

USING_CC_AUDIO;

GameScene* GameScene::createGameScene(int level)
{
    GameScene *scene = new GameScene;
    
    if(scene && scene->initGameScene(level))
    {
        
        scene->autorelease();
        
        return scene;
        
    }
    
    CC_SAFE_DELETE(scene);
    
    return NULL;
    
}

bool GameScene::initGameScene(int level)
{
    bool isDone = CCScene::init()? true:false;
    
    
    if (isDone)
    {
        this->loadResurces();
        
        game_level = level;
        
        MapLayer *mapLayer = MapLayer::creatMaplayer(level);
        
        this->addChild(mapLayer);
        
        GameLayer *gameLayer = GameLayer::createGameLayer(2);
        
        this->addChild(gameLayer);
        
    }
    
    return isDone;
    
}

void GameScene::onEnterTransitionDidFinish()
{
    CCScene::onEnterTransitionDidFinish();
    
    AUDIO_SYSTEM_CC->playBackgroundMusic("BGMusic.mp3", true);
    
}


void GameScene::loadResurces()
{

    // 设置随机算子
    srand(time(0));
    
    // 加载飞机文件
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sp_all.plist");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bullet_lv.plist");

}