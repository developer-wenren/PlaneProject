//
//  Define.h
//  Plane
//
//  Created by 软件开发 on 15/3/23.
//
//

#ifndef Plane_Define_h
#define Plane_Define_h

#define WINSIZE CCDirector::sharedDirector()->getWinSize()

#define WIN_CENTER ccp(WINSIZE.width*.5, WINSIZE.height*.5)

#define WIN_PISITION(_X,_Y) ccp(WINSIZE.width*(_X), WINSIZE.height*(_Y))

#define USING_CC_AUDIO using namespace CocosDenshion

#define AUDIO_SYSTEM_CC SimpleAudioEngine::sharedEngine()
//(宏参数)推荐加

#define TEAM_IMG "scorpion.png"

#define BACKGROUND_IMG "img_bg_logo.jpg"

#define LOGO_IMG "LOGO.png"

#define FONTFILE "MyFont.fnt"

#define START_TEXT "Start"

#define ADUIO_EFFECT_FILE "effect_boom.mp3"

#endif
