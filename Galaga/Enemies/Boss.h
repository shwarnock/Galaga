#ifndef _BOSS_H
#define _BOSS_H
#include "Enemy.h"
#include "CaptureBeam.h"

class Boss : public Enemy
{
private:
	static vector<vector<Vector2>> sDivePaths;

	bool mCaptureDive;

	int mCurrentPath;

	bool mCapturing;

	CaptureBeam* mCaptureBeam;

private:

	Vector2 LocalFormationPosition();

	void HandleCaptureBeam();

	void HandleDiveState();
	void HandleDeathState();

	void RenderDiveState();
	void RenderDeathState();

public:
	static void CreateDivePaths();

	Boss(int index, int path, bool challengeStage);
	~Boss();

	void Dive(int type = 0);
};

#endif
