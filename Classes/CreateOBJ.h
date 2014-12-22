#ifndef __TD_GAME__
#define __TD_GAME__

#define PTM_RATIO 32.0
#include "cocos2d.h"
#include <Box2D\Box2D.h>

enum 
{
	enemy,
	Turret,
	wall,
};

USING_NS_CC;

class CreateObj 
{

public:
	~CreateObj ();

	static void Create(int type,CCPoint spwanPoint);


private:



};

#endif