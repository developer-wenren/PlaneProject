//
//  MenuLayer.h
//  Plane
//
//  Created by 软件开发 on 15/3/23.
//
//

#ifndef __Plane__MenuLayer__
#define __Plane__MenuLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "Define.h"

USING_NS_CC;

class GameScene;

class MenuLayer:public CCLayerColor
{
    
public:
    
   static CCScene *scene(int level);
    
    CREATE_FUNC(MenuLayer);
    
    bool init();
    
    void setupBackgroundView();
    
    void update(float dt);
    
    void setupLogo();
    
    void setupTeam();
    
    void setupMenu();
    
    void callBack();
    
    void callBack2();
    
    void gotoScene();
    
    void callBack3();
    
    void callBackAudio();
    
};



#endif /* defined(__Plane__MenuLayer__) */
