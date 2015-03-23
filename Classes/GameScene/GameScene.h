
//
//  GameScene.h
//  Plane
//
//  Created by 软件开发 on 15/3/23.
//
//

#ifndef __Plane__GameScene__
#define __Plane__GameScene__

#include <stdio.h>
#include "cocos2d.h"

#endif /* defined(__Plane__GameScene__) */
USING_NS_CC;

class GameScene:public CCScene
{
private:
    
    int game_level;
    
public:
    
//    CREATE_FUNC(GameScene);
    static GameScene* createGameScene(int level);
    
    bool initGameScene(int level);
    
    
    
    
    
};