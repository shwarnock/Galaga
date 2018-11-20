#include "PlaySideBar.h"

PlaySideBar::PlaySideBar()
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mBackground = new Texture("Black.png");
	mBackground->Parent(this);
	mBackground->Pos(Vector2(45.0f, 380.0f));
	mBackground->Scale(Vector2(3.0f, 10.0f));

	mHighLabel = new Texture("HIGH", "emulogic.ttf", 32, { 150, 0, 0 });
	mHighLabel->Parent(this);
	mHighLabel->Pos(Vector2(-25.0f, 0.0f));

	mScoreLabel = new Texture("SCORE", "emulogic.ttf", 32, {150, 0, 0 });
	mScoreLabel->Parent(this);
	mScoreLabel->Pos(Vector2(25.0f, 32.0f));

	mHighScoreBoard = new ScoreBoard();
	mHighScoreBoard->Parent(this);
	mHighScoreBoard->Pos(Vector2(90.0f, 70.0f));

	mPlayerOneLabel = new Texture("1UP", "emulogic.ttf", 32, { 150, 0, 0 });
	mPlayerOneLabel->Parent(this);
	mPlayerOneLabel->Pos(Vector2(-45.0f, 160.0f));

	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.5f;
	mPlayerOneLabelVisible = true;

	mPlayerOneScore = new ScoreBoard();
	mPlayerOneScore->Parent(this);
	mPlayerOneScore->Pos(Vector2(90.0f, 200.0f));

	mShips = new GameEntity();
	mShips->Parent(this);
	mShips->Pos(Vector2(-35.0f, 375.0f));

	for (int i = 0; i < MAX_SHIP_TEXTURES; ++i)
	{
		mShipTextures[i] = new Texture("PlayerShip.png");
		mShipTextures[i]->Parent(mShips);
		mShipTextures[i]->Pos(Vector2(60.0f * (i % 3), 60.0f * (i / 3)));
	}

	mTotalShipsLabel = new ScoreBoard();
	mTotalShipsLabel->Parent(mShips);
	mTotalShipsLabel->Pos(Vector2(135.0f, 62.0f));
	mTotalShipsLabel->Score(mTotalShips);

	mFlags = new GameEntity();
	mFlags->Parent(this);
	mFlags->Pos(Vector2(-50.0f, 475.0f));

	mFlagTimer = 0.0f;
	mFlagInterval = 0.3f;
}

PlaySideBar::~PlaySideBar()
{
	mTimer = NULL;
	mAudio = NULL;

	delete mBackground;
	mBackground = NULL;

	delete mHighLabel;
	mHighLabel = NULL;

	delete mScoreLabel;
	mScoreLabel = NULL;

	delete mHighScoreBoard;
	mHighScoreBoard = NULL;

	delete mPlayerOneLabel;
	mPlayerOneLabel = NULL;

	delete mPlayerOneScore;
	mPlayerOneScore = NULL;

	delete mShips;
	mShips = NULL;

	for (int i = 0; i < MAX_SHIP_TEXTURES; ++i)
	{
		delete mShipTextures[i];
		mShipTextures[i] = NULL;
	}

	delete mTotalShipsLabel;
	mTotalShipsLabel = NULL;

	delete mFlags;
	mFlags = NULL;

	ClearFlags();
}

void PlaySideBar::ClearFlags()
{
	for (int i = 0; i < mFlagTextures.size(); ++i)
	{
		delete mFlagTextures[i];
		mFlagTextures[i] = NULL;
	}

	mFlagTextures.clear();
}

void PlaySideBar::AddNextFlag()
{
	if (mRemainingLevels >= 50)
		AddFlag("LevelFiftyFlag.png", 62.0f, 50);
	else if (mRemainingLevels >= 30)
		AddFlag("LevelThirtyFlag.png", 62.0f, 30);
	else if (mRemainingLevels >= 20)
		AddFlag("LevelTwentyFlag.png", 62.0f, 20);
	else if (mRemainingLevels >= 10)
		AddFlag("LevelTenFlag.png", 54.0f, 10);
	else if (mRemainingLevels >= 5)
		AddFlag("LevelFiveFlag.png", 30.0f, 5);
	else
		AddFlag("LevelOneFlag.png", 30.0f, 1);
}

void PlaySideBar::AddFlag(string fileName, float width, int value)
{
	int index = mFlagTextures.size();

	if (index > 0)
	{
		mFlagXOffset += width * 0.5;
	}

	if (index % 3 == 0 && index < 8)
	{
		mFlagYOffset += 64;
		mFlagXOffset = 0;
	} 

	mRemainingLevels -= value;
	mFlagTextures.push_back(new Texture(fileName));
	mFlagTextures[index]->Parent(mFlags);
	mFlagTextures[index]->Pos(Vector2(1.0f * mFlagXOffset, 1.0f * mFlagYOffset));
	mFlagXOffset += width * 0.5f;

	mAudio->PlaySFX("Flag.wav");
}

void PlaySideBar::SetPlayerScore(int score)
{
	mPlayerOneScore->Score(score);
}

void PlaySideBar::SetShips(int ships)
{
	mTotalShips = ships;
	
	if (ships > MAX_SHIP_TEXTURES)
		mTotalShipsLabel->Score(ships);
}

void PlaySideBar::SetHighScore(int score)
{
	mHighScoreBoard->Score(score);
}

void PlaySideBar::SetLevel(int level)
{
	ClearFlags();

	mRemainingLevels = level;
	mFlagXOffset = 0.0f;
	mFlagYOffset = 0.0f;
}

void PlaySideBar::Update()
{
	mBlinkTimer += mTimer->DeltaTime();

	if (mBlinkTimer >= mBlinkInterval)
	{
		mPlayerOneLabelVisible = !mPlayerOneLabelVisible;
		mBlinkTimer = 0.0f;
	}

	if (mRemainingLevels > 0)
	{
		mFlagTimer += mTimer->DeltaTime();
		if (mFlagTimer >= mFlagInterval)
		{
			AddNextFlag();
			mFlagTimer = 0.0f;
		}
	}
}

void PlaySideBar::Render()
{
	mBackground->Render();
	mHighLabel->Render();
	mScoreLabel->Render();
	mHighScoreBoard->Render();

	if (mPlayerOneLabelVisible)
		mPlayerOneLabel->Render();

	mPlayerOneScore->Render();

	for (int i = 0; i < MAX_SHIP_TEXTURES && i < mTotalShips; ++i)
	{
		mShipTextures[i]->Render();
	}

	if (mTotalShips > MAX_SHIP_TEXTURES)
	{
		mTotalShipsLabel->Render();
	}

	for (int i = 0; i < mFlagTextures.size(); ++i)
	{
		mFlagTextures[i]->Render();
	}
}