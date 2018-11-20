#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H

#include "../Entities/AnimatedTexture.h"
#include "../Managers/InputManager.h"
#include "BackgroundStars.h"
#include "ScoreBoard.h"

class StartScreen : public GameEntity
{

private:

	Timer* mTimer;

	InputManager* mInput;

	//TopBarEntities
	GameEntity* mTopBar;
	Texture* mPlayerOne;
	Texture* mHiScore;
	Texture* mPlayerTwo;
	ScoreBoard* mPlayerOneScore;
	ScoreBoard* mTopScore;
	ScoreBoard* mPlayerTwoScore;

	//Play Mode Entities
	GameEntity* mPlayModes;
	Texture* mOnePlayerMode;
	Texture* mTwoPlayerMode;
	Texture* mCursor;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffset;
	int mSelectedMode;

	//Bottom Bar Entities
	GameEntity* mBottomBar;
	Texture* mNamco;
	Texture* mDates;
	Texture* mRights;

	//Logo Entity
	GameEntity* mLogo;
	AnimatedTexture* mAnimatedLogo;

	//Screen animation variables
	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;

	BackgroundStars* mStars;

public:
	StartScreen();
	~StartScreen();

	int SelectedMode();
	
	void ResetAnimation();

	void ChangeSelectedMode(int change);

	void Update();

	void Render();

	bool AnimationDone();
};

#endif
