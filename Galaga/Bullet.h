#ifndef _BULLET_H
#define _BULLET_H

#include "../Entities/Texture.h"
#include "../Timer.h"

class Bullet : public GameEntity
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
