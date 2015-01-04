#ifndef __CONTACT_LISTENER_H__
#define __CONTACT_LISTENER_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include <Box2D\Box2D.h>

USING_NS_CC;

class ContactListener: public b2ContactListener
{
protected:
	CCObject* Mtarget;
	SEL_CallFunc Mselector;

public:
	ContactListener(b2World* world);
	virtual void InvisibleSprite(CCSprite* sprite);
	virtual void DeleteBody(b2Body* body);
	void BeginContact(b2Contact* contact);

private:
	b2World* thisWorld; 

};

#endif // __CONTACT_LISTENER_H__