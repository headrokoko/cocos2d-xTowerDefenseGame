#include "ContactListener.h"
#include "Option.h"
 

//ContactListenerのコンストラクタ
ContactListener::ContactListener(b2World* world, HelloWorld* HW)
{
	thisWorld = world;		//worldを設定
	HeWorld = HW;			//レイヤーを設定？
}

void ContactListener::BeginContact(b2Contact* contact)
{
	
	b2Fixture* FixtuerA = contact->GetFixtureA();
	b2Fixture* FixtuerB = contact->GetFixtureB();

	
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);	//＿worldの重力を設定
	b2World* testworld = new b2World(gravity); 

	//FixtureのNullチェック
	CCAssert(FixtuerA != NULL,"FixtureA is NULL");
	CCAssert(FixtuerB != NULL,"FixtureB is NULL");
	
	//接触したオブジェクトのbodyを取得
	b2Body* BodyA = FixtuerA->GetBody();
	b2Body* BodyB = FixtuerB->GetBody();
	
	//BodyのNullチェック
	CCAssert(BodyA != NULL,"BodyAがNULL");
	CCAssert(BodyB != NULL,"BodyBがNULL");

	//Bodyのタイプを取得
	int BodyTypeA = BodyA->GetType();
	int BodyTypeB = BodyB->GetType();
	
	//接触した物体が両方とも動的なものの場合に実行
	if((BodyTypeA == b2_dynamicBody)&&(BodyTypeB == b2_dynamicBody))
	{
		//接触したオブジェクトのuserdataを取得
		CCSprite* SpriteA = (CCSprite*)BodyA->GetUserData();
		CCSprite* SpriteB = (CCSprite*)BodyB->GetUserData();
	
		//AとBのオブジェクトのタグを取得
		int TagA = SpriteA->getTag();
		int TagB = SpriteB->getTag();

		//タグがEnemyの場合削除
		if(TagA == TAG_ENEMY)
		{
			//InvisibleSprite(SpriteA);	//SpritAを非表示
			HeWorld->AddScore(10);		//scoreに10加算
			DeleteBody(BodyA, thisWorld);

		}
		if(TagB == TAG_ENEMY)
		{
			InvisibleSprite(SpriteB);	//SpritAを非表示
			HeWorld->AddScore(10);		//scoreに10加算
			DeleteBody(BodyB, thisWorld);
		}

		//タグがBombの場合削除
		if(TagA == TAG_BOMB)
		{
			InvisibleSprite(SpriteA);
			DeleteBody(BodyA, thisWorld);
		}
		if(TagB == TAG_BOMB)
		{
			InvisibleSprite(SpriteB);
			DeleteBody(BodyB, thisWorld);
		}
	}

	//片方が静的(画面端など)オブジェクトだった場合
	else if(BodyTypeA == b2_dynamicBody)
	{
		//接触したオブジェクトのuserdataを取得
		CCSprite* SpriteA = (CCSprite*)BodyA->GetUserData();
	
		//AとBのオブジェクトのタグを取得
		int TagA = SpriteA->getTag();
		
		//タグがBombの場合削除
		if((TagA == TAG_BOMB)||(TagA == TAG_ENEMY))
		{
			InvisibleSprite(SpriteA);
		}
	}

	else if(BodyTypeB == b2_dynamicBody)
	{
		//接触したオブジェクトのuserdataを取得
		CCSprite* SpriteB = (CCSprite*)BodyB->GetUserData();
	
		//AとBのオブジェクトのタグを取得
		int TagB = SpriteB->getTag();
		
		//タグがBombの場合削除
		if((TagB == TAG_BOMB)||(TagB == TAG_ENEMY))
		{
			InvisibleSprite(SpriteB);
		}
	}
}

//Sprite非表示メソッド
void ContactListener::InvisibleSprite(CCSprite* sprite)
{
	sprite->setVisible(false);
}

//Body削除メソッド
void ContactListener::DeleteBody(b2Body* body, b2World* world)
{
	world->DestroyBody(body);
}
