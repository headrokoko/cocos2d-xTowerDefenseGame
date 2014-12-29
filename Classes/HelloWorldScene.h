#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <Box2D\Box2D.h>
#include "GLES-Render.h"
#include "CreateOBJ.h"
#include "HudLayer.h"

USING_NS_CC;
#define PTM_RATIO 32.0

class HelloWorld : public cocos2d::CCLayer
{

protected:
	
	void EnemySpwan();

public:

	~HelloWorld();

    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

	virtual void CreateBackground(); //背景作成メソッド
	virtual void CreatePlayer(CCPoint point);	//プレイヤー作成メソッド
	virtual void CreateEnemy(CCPoint point);	//Enemy作成メソッド
	virtual void CreateBomb(CCPoint point);		//爆弾作成メソッド
	virtual void draw();	//debugDraw作成メソッド　


	void initPhysics(); //物理演算初期化

	void update(float dt); //updateメソッド

    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void setViewPointCenter(CCPoint position);
    
    void registerWithTouchDispatcher();
    
    void setPlayerPosition(CCPoint position);
    
    bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    
    void ccTouchEnded(CCTouch *touch, CCEvent *event);
    
	b2World* _world;	//b2World用のフィールド宣言
	CCSize ScreenSize;

	CCSpriteBatchNode* ESpriteBatchNode;

    CCPoint tileCoordForPosition(CCPoint position);
	
	b2Body* enemyBody;
	b2Body* TurretBody;
	b2Body* wallBody;

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);

private:

	CCPoint spawnpoint;
	CCSpriteBatchNode* batchNode;
	b2Body* P_body;		//プレイヤーの物理ボディ

	GLESDebugDraw* _debugDraw;	//物理範囲の可視化用
	
    CCTMXTiledMap *_tileMap;	//TMXデータ格納フィールド
    
    CCTMXLayer *_background;	//背景レイヤー
    
    CCSprite *_player;	//プレイヤーのスプライト
    
    CCTMXLayer *_meta;	//metaデータのレイヤー
    
    CCTMXLayer *_foreground;	//foregroundレイヤー
    
    HudLayer *_hud;		//HUDレイヤー
    
    int _numCollected;
	int count;
    

};

#endif // __HELLOWORLD_SCENE_H__