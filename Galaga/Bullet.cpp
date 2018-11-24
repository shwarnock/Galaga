#include "Bullet.h";
#include "../Physics/BoxCollider.h"

Bullet::Bullet()
{
	mTimer = Timer::Instance();

	mSpeed = 500.0f;

	mBullet = new Texture("PlayerBullet.png");
	mBullet->Parent(this);
	mBullet->Pos(VEC2_ZERO);

	Reload();

	AddCollider(new BoxCollider(mBullet->ScaledDimensions()));
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