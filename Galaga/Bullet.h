#ifndef _BULLET_H
#define _BULLET_H

#include "../Physics/PhysicsEntity.h"
#include "../Timer.h"

class Bullet : public PhysicsEntity
{
private:

	const int OFFSCREEN_BUFFER = 10;

	Timer* mTimer;

	float mSpeed;

	Texture* mBullet;

public:
	Bullet();
	~Bullet();

	void Fire(Vector2 pos);
	void Reload();

	void Update();
	void Render();
};

#endif
