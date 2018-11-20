#include "GameManager.h"
#include <time.h>

GameManager* GameManager::sInstance = NULL;

GameManager* GameManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new GameManager();
	}

	return sInstance;
}

void GameManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

GameManager::GameManager()
{
	srand(time(0));

	mQuit = false;
	mGraphics = Graphics::Instance();

	if (!Graphics::Initialized())
	{
		mQuit = true;
	}

	mTimer = Timer::Instance();

	mAssetManager = AssetManager::Instance();
	
	mInputManager = InputManager::Instance();

	mAudioManager = AudioManager::Instance();

	mScreenManager = ScreenManager::Instance();
}

GameManager::~GameManager()
{
	ScreenManager::Release();
	mScreenManager = NULL;

	AudioManager::Release();
	mAudioManager = NULL;

	AssetManager::Release();
	mAssetManager = NULL;

	Graphics::Release();
	mGraphics = NULL;

	InputManager::Release();
	mInputManager = NULL;

	Timer::Release();
	mTimer = NULL;
}

void GameManager::EarlyUpdate()
{
	mInputManager->Update();
}


void GameManager::Update()
{
	mScreenManager->Update();
}

void GameManager::Render()
{
	mGraphics->ClearBackBuffer();

	mScreenManager->Render();

	mGraphics->Render();
}

void GameManager::LateUpdate()
{
	mInputManager->UpdatePreviousInput();
	mTimer->Reset();
}

void GameManager::Run()
{
	while (!mQuit)
	{
		mTimer->Update();

		while (SDL_PollEvent(&mEvents) != 0)
		{
			if (mEvents.type == SDL_QUIT)
			{
				mQuit = true;
			}
		}

		if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE))
		{
			EarlyUpdate();
			Update();
			LateUpdate();
			Render();
		}
	}
}