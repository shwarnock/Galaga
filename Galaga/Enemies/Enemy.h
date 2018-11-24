#ifndef _ENEMY_H
#define _ENEMY_H

#include "../../Entities/AnimatedTexture.h"
#include "../../BezierPath.h"
#include "../Formation.h"
#include "../../Physics/PhysicsEntity.h"

class Enemy : public PhysicsEntity
{
public:
	enum STATES { flyIn, formation, dive, death };
	enum TYPES { butterfly, wasp, boss };

protected:
	static vector<vector<Vector2>> sPaths;

	static Formation* sFormation;

	Timer* mTimer;

	Texture* mTextures[2];

	STATES mCurrentState;

	int mCurrentPath;

	int mCurrentWaypoint;
	const float EPSILON = 50.0f;

	float mSpeed;

	TYPES mType;
	int mIndex;

	bool mChallengeStage;

	Vector2 mDiveStartPosition;

protected:
	virtual void PathComplete();

	virtual void FlyInComplete();

	void JoinFormation();
	virtual Vector2 WorldFormationPosition();
	virtual Vector2 LocalFormationPosition() = 0;

	virtual void HandleFlyInState();
	virtual void HandleFormationState();
	virtual void HandleDiveState() = 0;
	virtual void HandleDeathState() = 0;

	void HandleStates();

	virtual void RenderFlyInState();
	virtual void RenderFormationState();
	virtual void RenderDiveState() = 0;
	virtual void RenderDeathState() = 0;
	
	void RenderStates();

public:
	static void CreatePaths();
	static void SetFormation(Formation* f);

	Enemy(int index, int path, bool challengeStage);
	virtual ~Enemy();

	STATES CurrentState();
	TYPES Type();
	int Index();

	virtual void Dive(int type = 0);

	void Update();
	void Render();
};

#endif