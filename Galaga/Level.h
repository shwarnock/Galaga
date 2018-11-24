#ifndef _LEVEL_H
#define _LEVEL_H

#include "../tinyxml2.h"
#include "../Managers/InputManager.h"
#include "PlaySideBar.h"
#include "BackgroundStars.h"
#include "Player.h"
#include "Enemies/Butterfly.h"
#include "Enemies/Wasp.h"
#include "Enemies/Boss.h"

using namespace tinyxml2;

class Level : GameEntity
{
public:
	enum LEVEL_STATES {running, finished, gameOver };

private:
	Timer* mTimer;
	PlaySideBar* mPlaySideBar;
	BackgroundStars* mStars;

	int mStage;
	bool mStageStarted;

	float mLabelTimer;

	Texture* mStageLabel;
	ScoreBoard* mStageNumber;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	Texture* mReadyLabel;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	Player* mPlayer;
	bool mPlayerHit;
	float mPlayerRespawnDelay;
	float mPlayerRespawnTimer;
	float mPlayerRespawnLabelOnScreen;

	Texture* mGameOverLabel;
	bool mGameOver;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverLabelOnScreen;

	LEVEL_STATES mCurrentState;

	Formation* mFormation;

	bool mChallengeStage;

	static const int MAX_BUTTERFLIES = 16;
	int mButterflyCount;

	static const int MAX_WASPS = 20;
	int mWaspCount;

	static const int MAX_BOSSES = 4;
	int mBossCount;

	Butterfly* mFormationButterflies[MAX_BUTTERFLIES];
	Wasp* mFormationWasps[MAX_WASPS];
	Boss* mFormationBosses[MAX_BOSSES];

	vector<Enemy*> mEnemies;

	XMLDocument mSpawningPatterns;
	int mCurrentFlyInPriority;
	int mCurrentFlyInIndex;

	bool mSpawningFinished;
	float mSpawnDelay;
	float mSpawnTimer;

	Butterfly* mDivingButterfly;
	bool mSkipFirstButterfly;
	float mButterflyDiveDelay;
	float mButteflyDiveTimer;

	Wasp* mDivingWasp;
	Wasp* mDivingWasp2;
	float mWaspDiveDelay;
	float mWaspDiveTimer;

	Boss* mDivingBoss;
	bool mCaptureDive;
	bool mSkipFirstBoss;
	float mBossDiveDelay;
	float mBossDiveTimer;

private:
	void StartStage();
	void HandleStartLabels();
	void HandleCollisions();
	void HandlePlayerDeath();
	
	bool EnemyFlyingIn();

	void HandleEnemySpawning();
	void HandleEnemyFormation();
	void HandleEnemyDiving();

public:
	Level(int stage, PlaySideBar* sideBar, Player* player);
	~Level();

	LEVEL_STATES State();

	void Update();
	void Render();
};

#endif