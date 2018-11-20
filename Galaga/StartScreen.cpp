#include "StartScreen.h"

using namespace std;

StartScreen::StartScreen()
{
	string font = "emulogic.ttf";

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	//Top Bar Entities
	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 80.0f));
	mPlayerOne = new Texture("1UP", font, 32, { 200, 0, 0 });
	mHiScore = new Texture("HI-SCORE", font, 32, { 200, 0, 0 });
	mPlayerTwo = new Texture("2UP", font, 32, { 200, 0, 0 });
	mPlayerOneScore = new ScoreBoard();
	mTopScore = new ScoreBoard();
	mPlayerTwoScore = new ScoreBoard();

	mPlayerOne->Parent(mTopBar);
	mPlayerTwo->Parent(mTopBar);
	mHiScore->Parent(mTopBar);
	mPlayerOneScore->Parent(mTopBar);
	mPlayerTwoScore->Parent(mTopBar);
	mTopScore->Parent(mTopBar);

	mPlayerOne->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.35f, 0.0f));
	mPlayerTwo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.2f, 0.0f));
	mHiScore->Pos(Vector2(-30.0f, 0.0f));

	mPlayerOneScore->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.23f, 40.0f));
	mPlayerTwoScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.32f, 40.0f));
	mTopScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.05f, 40.0f));

	mTopScore->Score(30000);

	mTopBar->Parent(this);

	Pos(mAnimationStartPos);

	//Play mode entities
	mPlayModes = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.55f));
	mOnePlayerMode = new Texture("1 Player", font, 32, {230, 230, 230});
	mTwoPlayerMode = new Texture("2 Players", font, 32, { 230, 230, 230 });
	mCursor = new Texture("Cursor.jpg");

	mOnePlayerMode->Parent(mPlayModes);
	mTwoPlayerMode->Parent(mPlayModes);
	mPlayModes->Parent(this);
	mCursor->Parent(mPlayModes);

	mOnePlayerMode->Pos(Vector2(-18.0f, -35.0f));
	mTwoPlayerMode->Pos(Vector2(0.0f, 35.0f));
	mCursor->Pos(Vector2(-180.0f, -35.0f));

	mCursorStartPos = mCursor->Pos(local);
	mCursorOffset = Vector2(0.0f, 70.0f);
	mSelectedMode = 0;

	//Bottom Bar Entities
	mBottomBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.7f));
	mNamco = new Texture("namcot", "namco__.ttf", 36, { 200, 0, 0 });
	mDates = new Texture("1981 1985 NAMCO LTD.", font, 32, { 230, 230, 230 });
	mRights = new Texture("ALL RIGHTS RESERVED", font, 32, { 230, 230, 230 });

	mNamco->Parent(mBottomBar);
	mDates->Parent(mBottomBar);
	mRights->Parent(mBottomBar);
	mBottomBar->Parent(this);

	mNamco->Pos(VEC2_ZERO);
	mDates->Pos(Vector2(0.0f, 90.0f));
	mRights->Pos(Vector2(0.0f, 180.0f));

	//Logo Entities
	mLogo = new Texture("GalagaLogo.jpg", 0, 0, 590, 260);
	mAnimatedLogo = new AnimatedTexture("GalagaLogo.jpg", 0, 0, 590, 260, 3, 0.2f, AnimatedTexture::vertical);
	
	mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.32f));
	mAnimatedLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.32f));

	mLogo->Parent(this);
	mAnimatedLogo->Parent(this);

	ResetAnimation();

	mStars = BackgroundStars::Instance();
	mStars->Scroll(true);
}

StartScreen::~StartScreen()
{
	//Freeing top bar entities
	delete mTopBar;
	mTopBar = NULL;
	delete mPlayerOne;
	mPlayerOne = NULL;
	delete mHiScore;
	mHiScore = NULL;
	delete mPlayerTwo;
	mPlayerTwo = NULL;
	delete mPlayerOneScore;
	mPlayerOneScore = NULL;
	delete mPlayerTwoScore;
	mPlayerTwoScore = NULL;
	delete mTopScore;
	mTopScore = NULL;

	//Freeing Play Mode Entities
	delete mPlayModes;
	mPlayModes = NULL;
	delete mOnePlayerMode;
	mOnePlayerMode = NULL;
	delete mTwoPlayerMode;
	mTwoPlayerMode = NULL;
	delete mCursor;
	mCursor = NULL;

	//Freeing Bottom Bar Entities
	delete mBottomBar;
	mBottomBar = NULL;
	delete mNamco;
	mNamco = NULL;
	delete mRights;
	mRights = NULL;
	delete mDates;
	mDates = NULL;

	//Free Logo
	delete mLogo;
	mLogo = NULL;
	delete mAnimatedLogo;
	mAnimatedLogo = NULL;
}

void StartScreen::ResetAnimation()
{
	//Screen Animation Variables
	mAnimationStartPos = Vector2(0.0f, Graphics::Instance()->SCREEN_HEIGHT);
	mAnimationEndPos = VEC2_ZERO;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	Pos(mAnimationStartPos);
}

int StartScreen::SelectedMode()
{
	return mSelectedMode;
}

void StartScreen::ChangeSelectedMode(int change)
{
	mSelectedMode += change;

	if (mSelectedMode < 0)
		mSelectedMode = 1;
	else if (mSelectedMode > 1)
		mSelectedMode = 0;

	mCursor->Pos(mCursorStartPos + mCursorOffset * mSelectedMode);
}

void StartScreen::Update()
{
	if (!mAnimationDone)
	{
		mAnimationTimer += mTimer->DeltaTime();
		Pos(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));

		if (mAnimationTimer >= mAnimationTotalTime)
			mAnimationDone = true;

		if ((mInput->KeyPressed(SDL_SCANCODE_DOWN) || mInput->KeyPressed(SDL_SCANCODE_UP)) && mAnimationDone)
			mAnimationTimer = mAnimationTotalTime;
	} else
	{
		mStars->Scroll(false);
		mAnimatedLogo->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_DOWN) && mSelectedMode == 0)
			ChangeSelectedMode(1);
		else if (mInput->KeyPressed(SDL_SCANCODE_UP) && mSelectedMode == 1)
			ChangeSelectedMode(-1);
	}
}

void StartScreen::Render()
{
	mPlayerOne->Render();
	mPlayerTwo->Render();
	mHiScore->Render();
	mOnePlayerMode->Render();
	mTwoPlayerMode->Render();
	mPlayerOneScore->Render();
	mPlayerTwoScore->Render();
	mTopScore->Render();
	mNamco->Render();
	mDates->Render();
	mRights->Render();
	mCursor->Render();
	
	if (!mAnimationDone)
	{
		mLogo->Render();
	} else
	{
		mAnimatedLogo->Render();
	}

}

bool StartScreen::AnimationDone()
{
	return mAnimationDone;
}