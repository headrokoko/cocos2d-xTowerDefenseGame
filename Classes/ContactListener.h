#ifndef __CONTACT_LISTENER_H__
#define __CONTACT_LISTENER_H__

#include "cocos2d.h"
#include <Box2D\Box2D.h>

USING_NS_CC;

class ContactListener: public b2ContactListener
{
protected:
	CCObject* Mtarget;
	SEL_CallFunc Mselector;

public:
	ContactListener(CCObject* target, SEL_CallFunc selecter);
	void BeginContact(b2Contact* contact);

private:

};

#endif // __CONTACT_LISTENER_H__