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

	const int MAX_BUTTERFLIES = 16;
	int mButterflyCount;

	const int MAX_WASPS = 20;
	int mWaspCount;

	const int MAX_BOSSES = 4;
	int mBossCount;

	vector<Enemy*> mEnemies;

	XMLDocument mSpawningPatterns;
	int mCurrentFlyInPriority;
	int mCurrentFlyInIndex;

	bool mSpawningFinished;
	float mSpawnDelay;
	float mSpawnTimer;

private:
	void StartStage();
	void HandleStartLabels();
	void HandleCollisions();
	void HandlePlayerDeath();
	
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