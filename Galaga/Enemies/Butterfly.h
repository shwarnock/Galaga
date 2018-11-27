#ifndef _BUTTERFLY_H
#define _BUTTERFLY_H
#include "Enemy.h"

class Butterfly : public Enemy
{
private:
	static vector<vector<Vector2>> sDivePaths;

	bool mEscort;

private:
	Vector2 LocalFormationPosition();

	void HandleDiveState();

	void RenderDiveState();

public:
	static void CreateDivePaths();

	Butterfly(int index, int path, bool challengeStage);
	~Butterfly();

	void Dive(int type = 0);

	void Hit(PhysicsEntity* other) override;
};

#endif
