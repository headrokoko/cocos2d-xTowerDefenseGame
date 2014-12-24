#ifndef __TD_GAME__
#define __TD_GAME__

#define PTM_RATIO 32.0
#include "cocos2d.h"
#include <Box2D\Box2D.h>

class HelloWorld;

enum 
{
	enemy,
	Turret,
	wall,
};

USING_NS_CC;

class CreateObj : public CCSprite
{

public:
	CreateObj ();
	~CreateObj ();

	virtual void Create(HelloWorld* Game, b2World* world, int type,CCPoint spwanPoint);

	virtual void update(float dt);
	
	b2Body* Enemy_body;		//EnemyÇÃï®óùÉ{ÉfÉB
	b2BodyDef enemyBodyDef;

	CCSprite* enemySprite;


private:
	


};

#endif