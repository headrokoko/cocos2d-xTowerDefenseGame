#include "CreateOBJ.h"

CreateObj::~CreateObj()
{
}

void CreateObj::Create(int type,CCPoint spwanPoint)
{
	if(type == enemy)
	{		
		CCSprite* enemySprite = CCSprite::create("Player.png");	//プレイヤーに当てる画像の設定
		enemySprite->setPosition(spwanPoint);	//生成位置の設定

		//物理属性の初期化
		b2BodyDef enemyBodyDef;
		enemyBodyDef.type = b2_dynamicBody;	//動的に設定
		enemyBodyDef.userData = enemySprite;	//playerSpriteをuserDateに格納
		enemyBodyDef.position.Set(spwanPoint.x/PTM_RATIO, spwanPoint.y/PTM_RATIO);	//bodyDefの生成位置を設定


		//形状の初期化
		b2CircleShape enemyShape;	//形状をサークルに設定
		enemyShape.m_radius = 50/PTM_RATIO;	//径を50ピクセル

		b2FixtureDef enemyFixDef;
		enemyFixDef.shape = &enemyShape;	//形状を入力
		enemyFixDef.density = 1.0f;	//密度
		enemyFixDef.friction = 0.5f;	//摩擦率
		enemyFixDef.restitution = 1.0f;	//反発係数


	}

	else if (type == Turret)
	{

	}

	else if(type == wall)
	{

	}
}