//
//  MenuLayer.cpp
//  Plane
//
//  Created by 软件开发 on 15/3/23.
//
//

#include "MenuLayer.h"

#include "SimpleAudioEngine.h"

#include "GameScene.h"

USING_CC_AUDIO;

static int gameLevel;

CCScene *MenuLayer::scene(int level)
{
    CCScene *scene = CCScene::create();
    
    MenuLayer *layer = MenuLayer::create();
    
    scene->addChild(layer);
    
    gameLevel = level;
    
    AUDIO_SYSTEM_CC->playBackgroundMusic("bg2.mp3");
    
    return scene;
    
}

void MenuLayer::setupLogo()
{
    CCSprite *logoView = CCSprite::create(LOGO_IMG);
    
    logoView->setScale(.3);
    
    logoView->setOpacity(0);
    
    logoView->setPosition(WIN_PISITION(.5, .8));
    
    CCFadeIn *fadeIn = CCFadeIn::create(1);
    CCScaleTo *scaleTo = CCScaleTo::create(1.5,1);

    CCCallFunc *callFinc = CCCallFunc::create(this, callfunc_selector(MenuLayer::callBack3));
    
    CCCallFunc *callAudio = CCCallFunc::create(this, callfunc_selector(MenuLayer::callBackAudio));

    CCSpawn *spawn = CCSpawn::create(fadeIn,scaleTo,NULL);
    CCEaseBounceOut *bounceOut = CCEaseBounceOut::create(spawn);
    
    CCSequence *sequence = CCSequence::create(callAudio,bounceOut,callFinc,NULL);
    
    logoView->runAction(sequence);
    
    this->addChild(logoView);
    
    
}


void MenuLayer::setupBackgroundView()
{
    CCSprite *backgroundView = CCSprite::create(BACKGROUND_IMG);
    
    backgroundView->setOpacity(0);
    
    backgroundView->setScale(2.0);
    
    backgroundView->setPosition(WIN_CENTER);
    
    CCScaleTo *scaleTo = CCScaleTo::create(1 ,1);
    
    CCFadeIn *fadeIn = CCFadeIn::create(1);
    
    CCMoveTo *move = CCMoveTo::create(1,ccp(160,110));

    CCSpawn *spawn = CCSpawn::create(move,scaleTo,NULL);
    
    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(MenuLayer::callBack2));
    
    CCSequence *sequence = CCSequence::create(fadeIn,spawn,callFunc,NULL);
    
    backgroundView->runAction(sequence);
    
    this->addChild(backgroundView);
    
}


bool MenuLayer::init()
{
    bool isDone = CCLayerColor::initWithColor(ccc4(0, 0, 0, 255)) ? true:false;

    this->setupTeam();
    
    this->scheduleUpdate();
    
    return isDone;
    
}


void MenuLayer::setupTeam()
{
    CCSprite *scorp = CCSprite::create(TEAM_IMG);
    
    scorp->setPosition(WIN_CENTER);
    
    scorp->setScale(.5);
    scorp->setOpacity(0);
    
    
    CCSequence *sequence = CCSequence::create(CCSpawn::create(CCFadeIn::create(1),CCScaleTo::create(1,1), NULL),CCDelayTime::create(.5),CCFadeOut::create(.5),CCCallFunc::create(this, callfunc_selector(MenuLayer::callBack)),NULL);
    
    scorp->runAction(sequence);
    
    this->addChild(scorp);
    
}

void MenuLayer::setupMenu()
{
    CCMenu *menu = CCMenu::create();
    
    this->addChild(menu);
    
    CCLabelBMFont *start_label = CCLabelBMFont::create(START_TEXT, FONTFILE);
    
    CCMenuItemLabel *start_item = CCMenuItemLabel::create(start_label, this, menu_selector(MenuLayer::gotoScene));
    
    start_item->setPosition(ccp(-220, -30));
    
    CCMoveTo *moveTo = CCMoveTo::create(1, ccp(0, -30));
    
    CCEaseBackOut *out = CCEaseBackOut::create(moveTo);
    
    start_item->runAction(out);
    
    menu->alignItemsVerticallyWithPadding(30);
    
    menu->addChild(start_item);

}

void MenuLayer::update(float dt)
{
    
}

void MenuLayer::callBack()
{
    
    this->setupBackgroundView();
    
}

void MenuLayer::callBack2()
{
    
    this->setupLogo();
}

void MenuLayer::callBack3()
{
    
    this->setupMenu();
}

void MenuLayer::callBackAudio()
{
    AUDIO_SYSTEM_CC ->playEffect("title.wav");
    
}

void MenuLayer::gotoScene()
{
    
    AUDIO_SYSTEM_CC->playEffect(ADUIO_EFFECT_FILE);
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFlipY::create(1, GameScene::createGameScene(gameLevel), kCCTransitionOrientationDownOver));
    
}