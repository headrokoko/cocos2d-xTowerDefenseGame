#ifndef __PHYSI_SPRITE_H__
#define __PHYSI_SPRITE_H__

#include "cocos2d.h"
#include <Box2D\Box2D.h>

USING_NS_CC;

class PhysiSprite : public CCSprite
{

protected:


public:
	PhysiSprite();

	void setPhysiBody(b2Body* body);

	virtual bool isDirty(void);
	virtual CCAffineTransform nodeToParentTransform(void);

	b2Body* E_body;

private:

};

#endif // __PHYSI_SPRITE_H__