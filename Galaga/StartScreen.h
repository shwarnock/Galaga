#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H

#include "../Entities/AnimatedTexture.h"
#include "../InputManager.h"

class StartScreen : public GameEntity
{
private:

	//TopBarEntities
	GameEntity* mTopBar;
	Texture* mPlayerOne;
	Texture* mHiScore;
	Texture* mPlayerTwo;

	//Play Mode Entities
	GameEntity* mPlayModes;
	Texture* mOnePlayerMode;
	Texture* mTwoPlayerMode;

	//Bottom Bar Entities
	GameEntity* mBottomBar;
	Texture* mNamco;
	Texture* mDates;
	Texture* mRights;

	//Logo Entity
	GameEntity* mLogo;

public:
	StartScreen();
	~StartScreen();

	void Update();

	void Render();
};

#endif
