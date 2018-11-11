#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include "Entities/AnimatedTexture.h"
#include "InputManager.h"

class GameManager
{
private:
	static GameManager* sInstance;

	const int FRAME_RATE = 60;

	bool mQuit;
	Graphics* mGraphics;
	AssetManager* mAssetManager;
	InputManager* mInputManager;

	Timer* mTimer;

	SDL_Event mEvents;

	AnimatedTexture* mTex;

public:
	static GameManager* Instance();
	static void Release();

	void Run();

private:
	GameManager();
	~GameManager();
};
#endif