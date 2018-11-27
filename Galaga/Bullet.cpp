#include "Bullet.h";
#include "../Physics/BoxCollider.h"
#include "../Managers/PhysicsManager.h"

Bullet::Bullet(bool friendly)
{
	mTimer = Timer::Instance();

	mSpeed = 1000.0f;

	mBullet = new Texture("PlayerBullet.png");
	mBullet->Parent(this);
	mBullet->Pos(VEC2_ZERO);

	Reload();

	AddCollider(new BoxCollider(mBullet->ScaledDimensions()));

	if (friendly)
	{
		PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::FriendlyProjectiles);
	} else
	{
		PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::HostileProjectiles);
	}
}

Bullet::~Bullet()
{
	mTimer = NULL;

	delete mBullet;
	mBullet = NULL;
}

void Bullet::Fire(Vector2 pos)
{
	Pos(pos);
	Active(true);
}

void Bullet::Hit(PhysicsEntity* other)
{
	Reload();
}

bool Bullet::IgnoreCollisions()
{
	return !Active();
}

void Bullet::Reload()
{
	Active(false);
}

void Bullet::Update()
{
	if (Active())
	{
		Translate(-VEC2_UP * mSpeed * mTimer->DeltaTime(), local);
		
		Vector2 pos = Pos();

		if (pos.y < -OFFSCREEN_BUFFER || pos.y > Graphics::Instance()->SCREEN_HEIGHT + OFFSCREEN_BUFFER)
		{
			Reload();
		}
	}
}

void Bullet::Render()
{
	if (Active())
	{
		mBullet->Render();
		PhysicsEntity::Render();
	}
}