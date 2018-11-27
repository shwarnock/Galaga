#ifndef _WASP_H
#define _WASP_H
#include "Enemy.h"

class Wasp : public Enemy
{
private:
	static vector<vector<Vector2>> sDivePaths;

	bool mDiver;

private:
	void PathComplete();
	void FlyInComplete();

	Vector2 LocalFormationPosition();
	
	void HandleDiveState();

	void RenderDiveState();

public:
	static void CreateDivePaths();

	void Hit(PhysicsEntity* other) override;

	Wasp(int index, int path, bool challengeStage, bool diver);
	~Wasp();
};
#endif
