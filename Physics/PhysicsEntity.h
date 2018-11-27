#ifndef _PHYSICSENTITY_H
#define _PHYSICSENTITY_H

#include "CircleCollider.h"
#include <vector>

using namespace std;

class PhysicsEntity : public GameEntity
{
protected:
	unsigned long mId;

	vector<Collider*> mColliders;

	Collider* mBroadPhaseCollider;

public:
	PhysicsEntity();
	virtual ~PhysicsEntity();

	unsigned long GetId();

	bool CheckCollision(PhysicsEntity* other);

	virtual void Hit(PhysicsEntity* other);

	virtual void Render();

protected: 
	void AddCollider(Collider* collider, Vector2 localPosition = VEC2_ZERO);
	virtual bool IgnoreCollisions();
};

#endif
