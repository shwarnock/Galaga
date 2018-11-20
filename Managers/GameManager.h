#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include "AudioManager.h"
#include "ScreenManager.h"
#include "../Timer.h"

class GameManager
{
private:
	static GameManager* sInstance;

	const int FRAME_RATE = 60;

	bool mQuit;
	Graphics* mGraphics;
	AssetManager* mAssetManager;
	InputManager* mInputManager;
	AudioManager* mAudioManager;

	Texture* mTexture;
	Texture* mTexture2;

	Timer* mTimer;

	SDL_Event mEvents;

	ScreenManager* mScreenManager;

public:
	static GameManager* Instance();
	static void Release();

	void Run();

private:
	GameManager();
	~GameManager();

	void EarlyUpdate();
	void Update();
	void LateUpdate();
	void Render();
};
#endif