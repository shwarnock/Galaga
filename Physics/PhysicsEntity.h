#ifndef _PHYSICSENTITY_H
#define _PHYSICSENTITY_H

#include "Collider.h"
#include <vector>

using namespace std;

class PhysicsEntity : public GameEntity
{
protected:
	vector<Collider*> mColliders;

public:
	PhysicsEntity();
	virtual ~PhysicsEntity();

	virtual void Render();

protected: 
	void AddCollider(Collider* collider, Vector2 localPosition = VEC2_ZERO);
};

#endif
