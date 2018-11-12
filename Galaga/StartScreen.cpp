#include "StartScreen.h"

StartScreen::StartScreen()
{
	string font = "emulogic.ttf";

	//Top Bar Entities
	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 80.0f));
	mPlayerOne = new Texture("1UP", font, 32, { 200, 0, 0 });
	mHiScore = new Texture("HI-SCORE", font, 32, { 200, 0, 0 });
	mPlayerTwo = new Texture("2UP", font, 32, { 200, 0, 0 });

	mPlayerOne->Parent(mTopBar);
	mPlayerTwo->Parent(mTopBar);
	mHiScore->Parent(mTopBar);

	mPlayerOne->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.35f, 0.0f));
	mPlayerTwo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.35f, 0.0f));
	mHiScore->Pos(Vector2(-30.0f, 0.0f));

	mTopBar->Parent(this);

	//Play mode entities
	mPlayModes = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.55f));
	mOnePlayerMode = new Texture("1 Player", font, 32, {230, 230, 230});
	mTwoPlayerMode = new Texture("2 Players", font, 32, { 230, 230, 230 });

	mOnePlayerMode->Parent(mPlayModes);
	mTwoPlayerMode->Parent(mPlayModes);
	mPlayModes->Parent(this);

	mOnePlayerMode->Pos(Vector2(-18.0f, -35.0f));
	mTwoPlayerMode->Pos(Vector2(0.0f, 35.0f));

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

	//Freeing Play Mode Entities
	delete mPlayModes;
	mPlayModes = NULL;
	delete mOnePlayerMode;
	mOnePlayerMode = NULL;
	delete mTwoPlayerMode;
	mTwoPlayerMode = NULL;

	//Freeing Bottom Bar Entities
	delete mBottomBar;
	mBottomBar = NULL;
	delete mNamco;
	mNamco = NULL;
	delete mRights;
	mRights = NULL;
	delete mDates;
	mDates = NULL;

}

void StartScreen::Update()
{

}

void StartScreen::Render()
{
	mPlayerOne->Render();
	mPlayerTwo->Render();
	mHiScore->Render();
	mOnePlayerMode->Render();
	mTwoPlayerMode->Render();
	mNamco->Render();
	mDates->Render();
	mRights->Render();
}