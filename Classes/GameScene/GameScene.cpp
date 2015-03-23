//
//  GameScene.cpp
//  Plane
//
//  Created by 软件开发 on 15/3/23.
//
//

#include "GameScene.h"

#include "MapLayer.h"

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
    
    game_level = level;

    MapLayer *mapLayer = MapLayer::creatMaplayer(level);
    
    this->addChild(mapLayer);
    
    return isDone;
    
}