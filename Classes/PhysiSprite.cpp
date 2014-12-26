#include "PhysiSprite.h"
#include "Option.h"

PhysiSprite::PhysiSprite()
:E_body(NULL)
{
}

void PhysiSprite::setPhysiBody(b2Body* body)
{
	E_body = body;
}

bool PhysiSprite::isDirty(void)
{
	return true;
}

CCAffineTransform PhysiSprite::nodeToParentTransform(void)
{
	b2Vec2 pos = E_body->GetPosition();

	float x = pos.x * PTM_RATIO;
	float y = pos.y * PTM_RATIO;

	if(isIgnoreAnchorPointForPosition())
	{
		x += m_obAnchorPointInPoints.x;
		y += m_obAnchorPointInPoints.y;
	}

	float radian = E_body->GetAngle();
	float cos = cosf(radian);
	float sin = sinf(radian);

	if(!m_obAnchorPointInPoints.equals(CCPointZero))
	{
		x += cos * -m_obAnchorPointInPoints.x + -sin * -m_obAnchorPointInPoints.y;
		y += sin * -m_obAnchorPointInPoints.x + cos * -m_obAnchorPointInPoints.y;
	}

	m_sTransform = CCAffineTransformMake(cos, sin, -sin, cos, x, y);

	return m_sTransform;
}