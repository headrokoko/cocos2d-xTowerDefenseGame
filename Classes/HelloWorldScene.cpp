#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Option.h"
#include "PhysiSprite.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    HudLayer *hud = new HudLayer();
    hud->init();
    scene->addChild(hud);
    layer->_hud = hud;
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

	this->initPhysics();
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("pickup.caf");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("hit.caf");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("move.caf");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("TileMap.caf");
    
	ESpriteBatchNode = CCSpriteBatchNode::create("Player.png");

	CreateBackground();	//背景生成メソッドへ

    CCTMXObjectGroup *objectGroup = _tileMap->objectGroupNamed("Objects");
    
    if(objectGroup == NULL){
        CCLog("tile map has no objects object layer");
        return false;
    }
    
    CCDictionary* spawnPoint = objectGroup->objectNamed("SpawnPoint");
    
    int x = ((CCString)*spawnPoint->valueForKey("x")).intValue();
    int y = ((CCString)*spawnPoint->valueForKey("y")).intValue();

	spawnpoint = ccp(x,y);
	//CreatePlayer(ccp(x,y));
	//CreateBomb(spawnpoint);

	this->setTouchEnabled(true);

	scheduleUpdate();	//updateメソッドを実行
	//this->schedule(schedule_selector(HelloWorld::EnemySpwan),1);
    
    return true;
}

void HelloWorld::update(float dt)
{
	_world->Step(dt,10,10);

}

void HelloWorld::EnemySpwan()
{
	CCLog("test");
}

//背景設定メソッド
void HelloWorld::CreateBackground()
{
    _tileMap = new CCTMXTiledMap();
    _tileMap->initWithTMXFile("sample.tmx");
    //_background = _tileMap->layerNamed("Background");
    //_foreground = _tileMap->layerNamed("Foreground");
    
    //_meta = _tileMap->layerNamed("Meta");
    //_meta->setVisible(false);
    
    //this->addChild(_tileMap);

}

//Bomb作成
void HelloWorld::CreateBomb(CCPoint point)
{
	PhysiSprite* BombSprite = new PhysiSprite();
	BombSprite->autorelease();
	BombSprite->initWithFile("Bomb.png");
	BombSprite->setPosition(point);
	this->addChild(BombSprite);

	b2BodyDef BombBodyDef;
	BombBodyDef.type = b2_dynamicBody;
	BombBodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);

	BombBodyDef.userData = BombSprite;

	b2Body* Bomb_body = _world->CreateBody(&BombBodyDef);

	b2CircleShape BombShape;
	BombShape.m_radius = BombSprite->getContentSize().width * 0.5 / PTM_RATIO;

	b2FixtureDef BombFixDef;
	BombFixDef.shape = &BombShape;
	BombFixDef.density = 1.0f;
	BombFixDef.friction = 0.9;

	Bomb_body->CreateFixture(&BombFixDef);
	BombSprite->setPhysiBody(Bomb_body);

	//this->setViewPointCenter(BombSprite->getPosition());

}

//Enemy作成
void HelloWorld::CreateEnemy(CCPoint point)
{
	PhysiSprite* Enemyprite = new PhysiSprite();
	Enemyprite->autorelease();
	Enemyprite->initWithFile("Player.png");

	
	float posX = (float)(rand()%(95-10+1)+10) / 100 ;

	Enemyprite->setPosition(point);
	this->addChild(Enemyprite);

	b2BodyDef EnemyBodyDef;
	EnemyBodyDef.type = b2_dynamicBody;
	EnemyBodyDef.linearVelocity = b2Vec2(0.0f, 15.0f);
	EnemyBodyDef.position.Set(ScreenSize.width * posX / PTM_RATIO, ScreenSize.height * 0.1f / PTM_RATIO);

	EnemyBodyDef.userData = Enemyprite;

	b2Body* Enemy_body = _world->CreateBody(&EnemyBodyDef);

	b2CircleShape EnemyShape;
	EnemyShape.m_radius = Enemyprite->getContentSize().width * 0.5 / PTM_RATIO;

	b2FixtureDef BombFixDef;
	BombFixDef.shape = &EnemyShape;
	BombFixDef.density = 1.0f;
	BombFixDef.friction = 0.9;

	Enemy_body->CreateFixture(&BombFixDef);
	Enemyprite->setPhysiBody(Enemy_body);

	//this->setViewPointCenter(BombSprite->getPosition());

}

//プレイヤー作成
void HelloWorld::CreatePlayer(CCPoint point)
{

	CCSprite* playerSprite = CCSprite::create("Player.png");	//プレイヤーに当てる画像の設定
	playerSprite->setPosition(point);	//生成位置の設定
	this->addChild(playerSprite);	//playerSpriteの生成

	//物理属性の初期化
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;	//動的に設定
	bodyDef.userData = playerSprite;	//playerSpriteをuserDateに格納
	bodyDef.position.Set(point.x/PTM_RATIO, point.y/PTM_RATIO);	//bodyDefの生成位置を設定

	P_body = _world->CreateBody(&bodyDef);	//bodyDefの設定が入ったP_bodyというb2bodyを生成

	//形状の初期化
	b2CircleShape circleShape;	//形状をサークルに設定
	circleShape.m_radius = 50/PTM_RATIO;	//径を50ピクセル

	b2FixtureDef fixDef;
	fixDef.shape = &circleShape;	//形状を入力
	fixDef.density = 1.0f;	//密度
	fixDef.friction = 0.5f;	//摩擦率
	fixDef.restitution = 1.0f;	//反発係数
	P_body->CreateFixture(&fixDef);	//P_bodyに形状を設定

	this->setViewPointCenter(playerSprite->getPosition());

}

//物理初期化
void HelloWorld::initPhysics()
{
	//ワールドの物理設定
	b2Vec2 gravity = b2Vec2(0.0f, -10.0f);	//＿worldの重力を設定
	_world = new b2World(gravity);	//_worldにgravityを入力

	//ゲーム画面端の設定
	ScreenSize = CCDirector::sharedDirector()->getWinSize();
	b2BodyDef worldBodyDef;
	worldBodyDef.position.Set(0,0);

	b2Body* worldBody = _world->CreateBody(&worldBodyDef);

	b2EdgeShape worldBox;

	//下限
	worldBox.Set(b2Vec2(ScreenSize.width * 0.05f / PTM_RATIO, ScreenSize.height * 0.05f / PTM_RATIO),
		b2Vec2(ScreenSize.width * 0.95f /PTM_RATIO, ScreenSize.height * 0.05f / PTM_RATIO));

	worldBody->CreateFixture(&worldBox,0);

	//左限
	worldBox.Set(b2Vec2(ScreenSize.width * 0.05f / PTM_RATIO, ScreenSize.height * 0.05f / PTM_RATIO),
		b2Vec2(ScreenSize.width * 0.05f /PTM_RATIO, ScreenSize.height * 0.95f / PTM_RATIO));

	worldBody->CreateFixture(&worldBox,0);
	
	//右限
	worldBox.Set(b2Vec2(ScreenSize.width * 0.95f / PTM_RATIO, ScreenSize.height * 0.05f / PTM_RATIO),
		b2Vec2(ScreenSize.width * 0.95f /PTM_RATIO, ScreenSize.height * 0.95f / PTM_RATIO));

	worldBody->CreateFixture(&worldBox,0);
	
 
	//debugDrawの設定
	_debugDraw = new GLESDebugDraw( PTM_RATIO );
	_world->SetDebugDraw(_debugDraw);
 
	//DebudDrawを使用するためCCLayerのdrawクラスをオーバーライドしている
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //        flags += b2Draw::e_jointBit;
    //        flags += b2Draw::e_aabbBit;
    //        flags += b2Draw::e_pairBit;
    //        flags += b2Draw::e_centerOfMassBit;
    _debugDraw->SetFlags(flags);
}

void HelloWorld::setViewPointCenter(CCPoint position)
{
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    int x = MAX(position.x, winSize.width/2);
    int y = MAX(position.y, winSize.height/2);
    x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height/2);
    CCPoint actualPosition = ccp(x, y);
    
    CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
    CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
    this->setPosition(viewPoint);
}

#pragma mark - handle touches

void HelloWorld::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

//クリック押下イベント
bool HelloWorld::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCPoint touchPoint = pDirector->convertToGL(touch->getLocationInView());

	//CreatePlayer(touchPoint);

	CreateBomb(touchPoint);
	CreateEnemy(touchPoint);


    return true;
}

void HelloWorld::setPlayerPosition(CCPoint position)
{
    CCPoint tileCoord = this->tileCoordForPosition(position);
    int tileGid = _meta->tileGIDAt(tileCoord);
    if (tileGid) {
        CCDictionary *properties = _tileMap->propertiesForGID(tileGid);
        if (properties) {
            CCString *collision = new CCString();
            *collision = *properties->valueForKey("Collidable");
            if (collision && (collision->compare("True") == 0)) {
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hit.caf");
                return;
            }
            CCString *collectible = new CCString();
            *collectible = *properties->valueForKey("Collectable");
            if (collectible && (collectible->compare("True") == 0)) {
                _meta->removeTileAt(tileCoord);
                _foreground->removeTileAt(tileCoord);
                _numCollected++;
                _hud->numCollectedChanged(_numCollected);
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pickup.caf");
            }
        }
    }
    _player->setPosition(position);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("move.caf");
}

void HelloWorld::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
}

CCPoint HelloWorld::tileCoordForPosition(CCPoint position)
{
    int x = position.x / _tileMap->getTileSize().width;
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
    return ccp(x, y);
}

void HelloWorld::draw()
{
	CCLayer::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	_world->DrawDebugData();
	kmGLPopMatrix();
}
 
//newでメモリを確保した_worldと_debugDrawはautoreleaseされないためデストラクタにて解放
HelloWorld::~HelloWorld()
{
	delete _debugDraw;
    _debugDraw = NULL;
 
    delete _world;
    _world = NULL;
}
