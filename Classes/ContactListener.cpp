#include "ContactListener.h"
#include "Option.h"

ContactListener::ContactListener(CCObject* target, SEL_CallFunc selector)
{
	Mtarget = target;
	Mselector = selector;
}

void ContactListener::BeginContact(b2Contact* contact)
{


	//接触したオブジェクトのuserdataを取得
	CCSprite* SpriteA = (CCSprite*)contact->GetFixtureA()->GetUserData();
	CCSprite* SpriteB = (CCSprite*)contact->GetFixtureB()->GetUserData();

	//接触したオブジェクトのbodyを取得
	b2Body* BodyA = contact->GetFixtureA()->GetBody();
	b2Body* BodyB = contact->GetFixtureB()->GetBody();


	//A側の非表示処理
	//SpriteA->setVisible(false);
	//SpriteA->removeFromParentAndCleanup(true);

	
	//B側の非表示処理
	//SpriteB->setVisible(false);
	//SpriteB->removeFromParentAndCleanup(true);
}