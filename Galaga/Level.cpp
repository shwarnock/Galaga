#include "Level.h"

Level::Level(int stage, PlaySideBar* sideBar, Player* player)
{
	mTimer = Timer::Instance();
	mPlaySideBar = sideBar;
	mPlaySideBar->SetLevel(stage);
	mStars = BackgroundStars::Instance();

	mStage = stage;
	mStageStarted = false;

	mLabelTimer = 0.0f;
	
	mStageLabel = new Texture("STAGE", "emulogic.ttf", 32, { 75, 75, 200 });
	mStageLabel->Parent(this);
	mStageLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.32f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mStageNumber = new ScoreBoard({ 75, 75, 200 });
	mStageNumber->Score(mStage);
	mStageNumber->Parent(mStageLabel);
	mStageNumber->Pos(Vector2(180.0f, 0.0f));

	mStageLabelOnScreen = 0.0f;
	mStageLabelOffScreen = 1.5f;

	mReadyLabel = new Texture("READY", "emulogic.ttf", 32, { 150, 0, 0 });
	mReadyLabel->Parent(this);
	mReadyLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.38f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mReadyLabelOnScreen = mStageLabelOffScreen;
	mReadyLabelOffScreen = mReadyLabelOnScreen + 3.0f;

	mPlayer = player;
	mPlayerHit = false;
	mPlayerRespawnDelay = 3.0f;
	mPlayerRespawnTimer = 0.0f;
	mPlayerRespawnLabelOnScreen = 2.0f;

	mGameOverLabel = new Texture("GAME OVER", "emulogic.ttf", 32, { 150, 0, 0 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.38f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mGameOver = false;
	mGameOverDelay = 6.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	mCurrentState = running;

	mFormation = new Formation();
	mFormation->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.38f, 150.0f));
	Enemy::SetFormation(mFormation);

	mButterflyCount = 0;
	mWaspCount = 0;
	mBossCount = 0;

	string fullPath = SDL_GetBasePath();
	fullPath.append("Levels/Level1.xml");
	mSpawningPatterns.LoadFile(fullPath.c_str());

	mCurrentFlyInPriority = 0;
	mCurrentFlyInIndex = 0;
	mSpawningFinished = false;
	mSpawnDelay = 0.2f;
	mSpawnTimer = 0.0f;
}

Level::~Level()
{
	mTimer = NULL;
	mPlaySideBar = NULL;
	mStars = NULL;

	delete mStageLabel;
	mStageLabel = NULL;

	delete mStageNumber;
	mStageNumber = NULL;

	delete mReadyLabel;
	mReadyLabel = NULL;

	mPlayer = NULL;

	delete mGameOverLabel;
	mGameOverLabel = NULL;

	delete mFormation;
	mFormation = NULL;

	for (int i = 0; i < mEnemies.size(); ++i)
	{
		delete mEnemies[i];
		mEnemies[i] = NULL;
	}

	mEnemies.clear();
}

void Level::StartStage()
{
	mStageStarted = true;
}

void Level::HandleStartLabels()
{
	mLabelTimer += mTimer->DeltaTime();
	if (mLabelTimer >= mStageLabelOffScreen)
	{
		mStars->Scroll(true);
		if (mStage > 1)
		{
			StartStage();
			mPlayer->Active(true);
			mPlayer->Visible(true);
		} else
		{
			if (mLabelTimer >= mReadyLabelOffScreen)
			{
				StartStage();
				mPlayer->Active(true);
				mPlayer->Visible(true);
			}
		}
	}
}

void Level::HandleCollisions()
{
	if (!mPlayerHit)
	{
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_X))
		{
			mPlayer->WasHit();
			mPlaySideBar->SetShips(mPlayer->Lives());

			mPlayerHit = true;
			mPlayerRespawnTimer = 0.0f;
			mPlayer->Active(false);
			mStars->Scroll(false);
		}
	}
}

void Level::HandlePlayerDeath()
{
	if (!mPlayer->IsAnimating())
	{
		if (mPlayer->Lives() > 0)
		{
			if (mPlayerRespawnTimer == 0.0f)
				mPlayer->Visible(false);

			mPlayerRespawnTimer += mTimer->DeltaTime();
			if (mPlayerRespawnTimer >= mPlayerRespawnDelay)
			{
				mPlayer->Active(true);
				mPlayer->Visible(true);
				mPlayerHit = false;
				mStars->Scroll(true);
			} 
		} else
		{
			if (mGameOverTimer == 0.0f)
				mPlayer->Visible(false);

			mGameOverTimer += mTimer->DeltaTime();
			if (mGameOverTimer >= mGameOverDelay)
			{
				mCurrentState = gameOver;
			}
		}
	}
}

void Level::HandleEnemySpawning()
{
	mSpawnTimer += mTimer->DeltaTime();
	if (mSpawnTimer >= mSpawnDelay)
	{
		XMLElement* element = mSpawningPatterns.FirstChildElement("Level")->FirstChild()->NextSiblingElement();
		bool spawned = false;
		bool priorityFound = false;

		while (element != NULL)
		{
			int priority = element->IntAttribute("priority");
			int path = element->IntAttribute("path");
			XMLElement* child = element->FirstChildElement();

			if (mCurrentFlyInPriority == priority)
			{
				priorityFound = true;
				for (int i = 0; i < mCurrentFlyInIndex && child != NULL; ++i)
				{
					child = child->NextSiblingElement();
				}

				if (child != NULL)
				{
					string type = child->Attribute("type");
					int index = child->IntAttribute("index");

					if (type.compare("Butterfly") == 0)
					{
						mEnemies.push_back(new Butterfly(index, path, false));
						++mButterflyCount;
					} else if (type.compare("Wasp") == 0) 
					{
						mEnemies.push_back(new Wasp(index, path, false, false));
						++mWaspCount;
					} else if (type.compare("Boss") == 0)
					{
						mEnemies.push_back(new Boss(index, path, false));
						++mBossCount;
					}

					spawned = true;
				}
			}

			element = element->NextSiblingElement();
		}

		if (!priorityFound)
		{
			mSpawningFinished = true;
		} else
		{
			if (!spawned)
			{
				bool flyingIn = false;

				for (int i = 0; i < mEnemies.size(); ++i)
				{
					if (mEnemies[i]->CurrentState() == Enemy::flyIn)
					{
						flyingIn = true;
						break;
					}

				}

				if (!flyingIn)
				{
					++mCurrentFlyInPriority;
					mCurrentFlyInIndex = 0;
				}
			} else
			{
				++mCurrentFlyInIndex;
			}
		}

		mSpawnTimer = 0.0f;
	}
}

void Level::HandleEnemyFormation()
{
	mFormation->Update();

	if (mButterflyCount == MAX_BUTTERFLIES && mWaspCount == MAX_WASPS && mBossCount == MAX_BOSSES)
	{
		bool flyIn = false;
		for (int i = 0; i < mEnemies.size(); ++i)
		{
			if (mEnemies[i]->CurrentState() == Enemy::flyIn)
			{
				flyIn = true;
				break;
			}
		}

		if (!flyIn)
		{
			mFormation->Lock();
		}
	}
}

void Level::HandleEnemyDiving()
{
	if (mFormation->Locked())
	{
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_V))
		{
			for (int i = mEnemies.size() - 1; i >= 0; --i)
			{
				if (mEnemies[i]->Type() == Enemy::wasp && mEnemies[i]->CurrentState() == Enemy::formation)
				{
					mEnemies[i]->Dive();
					break;
				}
			}
		}
	}

	if (mFormation->Locked())
	{
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_B))
		{
			for (int i = mEnemies.size() - 1; i >= 0; --i)
			{
				if (mEnemies[i]->Type() == Enemy::butterfly && mEnemies[i]->CurrentState() == Enemy::formation)
				{
					mEnemies[i]->Dive();
					break;
				}
			}
		}
	}

	if (mFormation->Locked())
	{
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_W))
		{
			for (int i = mEnemies.size() - 1; i >= 0; --i)
			{
				if (mEnemies[i]->Type() == Enemy::boss && mEnemies[i]->CurrentState() == Enemy::formation)
				{
					mEnemies[i]->Dive(1);
					break;
				}
			}
		}
	}

	if (mFormation->Locked())
	{
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_G))
		{
			for (int i = mEnemies.size() - 1; i >= 0; --i)
			{
				if (mEnemies[i]->Type() == Enemy::boss && mEnemies[i]->CurrentState() == Enemy::formation)
				{
					mEnemies[i]->Dive();

					int index = mEnemies[i]->Index();
					int firstEscortIndex = (index % 2 == 0) ? index * 2 : index * 2 - 1;
					int secondEscortIndex = firstEscortIndex + 4;

					for (int j = 0; j < mEnemies.size(); ++j)
					{
						if (mEnemies[j]->Type() == Enemy::butterfly && mEnemies[j]->CurrentState() == Enemy::formation && (mEnemies[j]->Index() == firstEscortIndex || mEnemies[j]->Index() == secondEscortIndex))
						{
							mEnemies[j]->Dive(1);
						}
					}
					break;
				}
			}
		}
	}
}

Level::LEVEL_STATES Level::State()
{
	return mCurrentState;
}

void Level::Update()
{
	if (!mStageStarted)
	{
		HandleStartLabels();
	} else
	{
		if (!mSpawningFinished)
			HandleEnemySpawning();
		HandleEnemyFormation();
		HandleEnemyDiving();

		for (int i = 0; i < mEnemies.size(); ++i)
			mEnemies[i]->Update();

		HandleCollisions();

		if (mPlayerHit)
		{
			HandlePlayerDeath();
		} else
		{
			if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_N))
				mCurrentState = finished;
		}
	}
}

void Level::Render()
{
	if (!mStageStarted)
	{
		if (mLabelTimer > mStageLabelOnScreen && mLabelTimer < mStageLabelOffScreen)
		{
			mStageLabel->Render();
			mStageNumber->Render();
		} else if (mLabelTimer > mReadyLabelOnScreen && mLabelTimer < mReadyLabelOffScreen)
			mReadyLabel->Render();
		
	} else
	{
		for (int i = 0; i < mEnemies.size(); ++i)
			mEnemies[i]->Render();

		if (mPlayerHit)
		{
			if (mPlayerRespawnTimer > mPlayerRespawnLabelOnScreen)
				mReadyLabel->Render();

			if (mGameOverTimer >= mGameOverLabelOnScreen)
				mGameOverLabel->Render();
		}
	}
}