#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity()
{

}

PhysicsEntity::~PhysicsEntity()
{
	for (int i = 0; i < mColliders.size(); ++i)
	{
		delete mColliders[i];
		mColliders[i] = NULL;
	}

	mColliders.clear();
}

void PhysicsEntity::AddCollider(Collider* collider, Vector2 localPosition)
{
	collider->Parent(this);
	collider->Pos(localPosition);
	mColliders.push_back(collider);
}

void PhysicsEntity::Render()
{
	for (int i = 0; i < mColliders.size(); ++i)
	{
		mColliders[i]->Render();
	}
}