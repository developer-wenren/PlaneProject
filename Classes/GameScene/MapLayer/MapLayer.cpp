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
    
    this->setupMapView(level);
    
    
    return isDone;
    
}


void MapLayer::setupMapView(int level)
{
    
    const char *imageName = CCString::createWithFormat("img_bg_level_%d.jpg",level)->getCString();
    
    map_a = CCSprite::create(imageName);
    
    map_b = CCSprite::create(imageName);
    
    this -> addChild(map_a);
    
    this -> addChild(map_b);
    
    map_a -> setAnchorPoint(CCPointZero);
    
    map_b -> setAnchorPoint(CCPointZero);
    
    map_b -> setPositionY(map_a->getContentSize().height);
    
    map_a ->setPositionY(0);
    

    
    
}

void MapLayer::update(float dt)
{
    
    map_a -> setPositionY(map_a->getPositionY()-2);
    
    map_b -> setPositionY(map_b->getPositionY()-2);
    
    if (map_a->getPositionY()<= -map_a->getContentSize().height)
    {
        map_a->setPositionY(map_a->getContentSize().height+map_b->getPositionY());

    }
    
    if (map_b->getPositionY()<=-map_b->getContentSize().height)
    {
        map_b->setPositionY(map_b->getContentSize().height+map_a->getPositionY());

    }

}

void MapLayer::onEnter()
{
    CCLayer::onEnter();  // 优先调用父类方法
    
}

void MapLayer::onExit()
{
    CCLayer::onExit();
    
}

void MapLayer::onEnterTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();

}

void MapLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    
    this->scheduleUpdate();


}
