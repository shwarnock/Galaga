#include "PhysicsEntity.h"
#include "PhysicsHelper.h"
#include "../Managers/PhysicsManager.h"

PhysicsEntity::PhysicsEntity()
{
	mBroadPhaseCollider = nullptr;
	mId = 0;
}

PhysicsEntity::~PhysicsEntity()
{
	for (int i = 0; i < mColliders.size(); ++i)
	{
		delete mColliders[i];
		mColliders[i] = NULL;
	}

	mColliders.clear();

	if (mBroadPhaseCollider)
	{
		delete mBroadPhaseCollider;
		mBroadPhaseCollider = nullptr;
	}

	if (mId != 0)
	{
		PhysicsManager::Instance()->UnregisterEntity(mId);
	}
}

unsigned long PhysicsEntity::GetId()
{
	return mId;
}

bool PhysicsEntity::CheckCollision(PhysicsEntity* other)
{
	if (IgnoreCollisions() || other->IgnoreCollisions())
	{
		return false;
	}

	bool narrowPhaseCheck = false;
	if (mBroadPhaseCollider && other->mBroadPhaseCollider)
	{
		narrowPhaseCheck = ColliderColliderCheck(mBroadPhaseCollider, other->mBroadPhaseCollider);
	} else
	{
		narrowPhaseCheck = true;
	}

	if (narrowPhaseCheck)
	{
		for (int i = 0; i < mColliders.size(); ++i)
		{
			for (int j = 0; j < other->mColliders.size(); ++j)
			{
				if (ColliderColliderCheck(mColliders[i], other->mColliders[j]))
				{
					return true;
				}
			}
		}
	}

	return false;
}

void PhysicsEntity::Hit(PhysicsEntity* other)
{

}

bool PhysicsEntity::IgnoreCollisions()
{
	return false;
}

void PhysicsEntity::AddCollider(Collider* collider, Vector2 localPosition)
{
	collider->Parent(this);
	collider->Pos(localPosition);
	mColliders.push_back(collider);

	if (mColliders.size() > 1 || mColliders[0]->GetType() != Collider::ColliderType::Circle)
	{
		float furthestDistance = mColliders[0]->GetFurthestPoint().Magnitude();
		float distance = 0.0f;
		for (int i = 1; i < mColliders.size(); ++i)
		{
			distance = mColliders[i]->GetFurthestPoint().Magnitude();
			if (distance > furthestDistance)
			{
				furthestDistance = distance;
			}
		}

		delete mBroadPhaseCollider;


		mBroadPhaseCollider = new CircleCollider(furthestDistance, true);
		mBroadPhaseCollider->Parent(this);
		mBroadPhaseCollider->Pos(VEC2_ZERO);
	}
}

void PhysicsEntity::Render()
{
	for (int i = 0; i < mColliders.size(); ++i)
	{
		mColliders[i]->Render();
	}

	if (mBroadPhaseCollider)
	{
		mBroadPhaseCollider->Render();
	}
}