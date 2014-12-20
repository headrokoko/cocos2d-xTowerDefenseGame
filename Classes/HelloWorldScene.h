#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "HudLayer.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
private:
    CCTMXTiledMap *_tileMap;
    
    CCTMXLayer *_background;
    
    CCSprite *_player;
    
    CCTMXLayer *_meta;
    
    CCTMXLayer *_foreground;
    
    HudLayer *_hud;
    
    int _numCollected;
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void setViewPointCenter(CCPoint position);
    
    void registerWithTouchDispatcher();
    
    void setPlayerPosition(CCPoint position);
    
    bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    
    void ccTouchEnded(CCTouch *touch, CCEvent *event);
    
    CCPoint tileCoordForPosition(CCPoint position);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__