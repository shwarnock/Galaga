#include "BoxCollider.h"

BoxCollider::BoxCollider(Vector2 size)
	: Collider(Collider::ColliderType::Box)
{
	AddVert(0, Vector2(-0.5f * size.x, -0.5f * size.y));
	AddVert(1, Vector2( 0.5f * size.x, -0.5f * size.y));
	AddVert(2, Vector2(-0.5f * size.x,  0.5f * size.y));
	AddVert(3, Vector2( 0.5f * size.x,  0.5f * size.y));

	if (DEBUG_COLLIDERS)
	{
		SetDebugTexture(new Texture("BoxCollider.png"));
		mDebugTexture->Scale(size / 100.0f);
	}
}

BoxCollider::~BoxCollider()
{
	for (int i = 0; i < MAX_VERTS; ++i)
	{
		delete mVerts[i];
		mVerts[i] = nullptr;
	}
}

Vector2 BoxCollider::GetVertexPos(int index)
{
	return mVerts[index]->Pos();
}

Vector2 BoxCollider::GetFurthestPoint()
{
	Vector2 localPosition = Pos(GameEntity::local);

	int furthestIndex = 0;
	float distance = (localPosition + mVerts[0]->Pos(GameEntity::local)).MagnitudeSqr();
	float otherDistance = 0.0f;

	for (int i = 1; i < MAX_VERTS; ++i)
	{
		otherDistance = (localPosition + mVerts[i]->Pos(GameEntity::local)).MagnitudeSqr();
		if (otherDistance > distance)
		{
			furthestIndex = i;
			distance = otherDistance;
		}
	}

	return localPosition + mVerts[furthestIndex]->Pos(GameEntity::local);
}

void BoxCollider::AddVert(int index, Vector2 pos)
{
	mVerts[index] = new GameEntity(pos);
	mVerts[index]->Parent(this);
}