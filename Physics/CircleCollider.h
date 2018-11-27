#ifndef _CIRCLECOLLIDER_H
#define _CIRCLECOLLIDER_H

#include "Collider.h"

class CircleCollider : public Collider
{
private:
	float mRadius;

public:
	CircleCollider(float radius, bool broadPhase = false);
	~CircleCollider();

	float GetRadius();

	Vector2 GetFurthestPoint() override;
};
#endif
