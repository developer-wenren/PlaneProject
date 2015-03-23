//
//  MapLayer.cpp
//  Plane
//
//  Created by 软件开发 on 15/3/23.
//
//

#include "MapLayer.h"

MapLayer* MapLayer::creatMaplayer(int level)
{
    MapLayer *mapLayer = new MapLayer;
    
    if (mapLayer && mapLayer->initMaplayer(level))
    {
        mapLayer->autorelease();
        
        return mapLayer;

    }
    
    CC_SAFE_DELETE(mapLayer);
    
    return NULL;
}

bool MapLayer:: initMaplayer(int level)
{
    bool isDone = CCLayer::init()? true:false;
    
    CCSprite *sprite = CCSprite::create("scorpion.png");
    
    sprite->setPosition(ccp(160, 240));
    
    this->addChild(sprite);
    
    
    return isDone;
    
    
}