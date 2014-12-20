#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <Box2D\Box2D.h>
#include "GLES-Render.h"
#include "HudLayer.h"

USING_NS_CC;
#define PTM_RATIO 32.0

class HelloWorld : public cocos2d::CCLayer
{
public:

	~HelloWorld();

    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

	virtual void CreateBackground();
	virtual void CreatePlayer(int x,int y);
	virtual void draw();

	void initPhysics(); //ï®óùââéZèâä˙âª

	void update(float dt); 

    
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

private:

	b2World* _world;

	b2Body* P_body;

	GLESDebugDraw* _debugDraw;
	
    CCTMXTiledMap *_tileMap;
    
    CCTMXLayer *_background;
    
    CCSprite *_player;
    
    CCTMXLayer *_meta;
    
    CCTMXLayer *_foreground;
    
    HudLayer *_hud;
    
    int _numCollected;
    

};

#endif // __HELLOWORLD_SCENE_H__