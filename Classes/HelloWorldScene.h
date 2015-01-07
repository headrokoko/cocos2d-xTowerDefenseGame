#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <Box2D\Box2D.h>
#include "GLES-Render.h"
#include "CreateOBJ.h"
#include "ContactListener.h"
#include "HudLayer.h"
#include "picojson.h"

USING_NS_CC;

#define PTM_RATIO 32.0

class HelloWorld : public cocos2d::CCLayer, public b2ContactListener
{

protected:
	

public:
	
	HelloWorld();
	~HelloWorld();

    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

	virtual void CreateBackground(); //背景作成メソッド
	virtual void CreatePlayer(CCPoint point);	//プレイヤー作成メソッド
	virtual void CreateEnemy(float dt);	//Enemy作成メソッド
	virtual void CreateBomb(CCPoint point);		//爆弾作成メソッド
	virtual void draw();	//debugDraw作成メソッド　
	virtual void ElapsedTime(float dt);	//経過時間表示メソッド
	virtual void AddScore(int point);	//スコア加算メソッド

	virtual void severMessageLabel();

	virtual void RemoveOBJ(b2Body* body);

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

	void DestroyObject(CCNode* Dobject, void* body);
    
	b2World* _world;	//b2World用のフィールド宣言
	CCSize ScreenSize;
	b2ContactListener* _contactListener;

	CCSpriteBatchNode* ESpriteBatchNode;

    CCPoint tileCoordForPosition(CCPoint position);
	b2Vec2 gravity;
	b2Body* enemyBody;
	b2Body* TurretBody;
	b2Body* wallBody;
	CCLabelTTF* ScoreLabel;
	CCLabelTTF* TimeLabel;
	CCLabelTTF* touchPosX;
	CCLabelTTF* touchPosY;
	int score;
	int time;

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);

private:

	void TouchPosLabel();
	void TouchPosLabelRenewal(CCPoint point);

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