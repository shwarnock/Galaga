#include "GameManager.h"

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

	mStartScreen = new StartScreen();
}

GameManager::~GameManager()
{
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

	delete mStartScreen;
	mStartScreen = NULL;
}

void GameManager::EarlyUpdate()
{
	mInputManager->Update();
}


void GameManager::Update()
{
	mStartScreen->Update();
}

void GameManager::Render()
{
	mGraphics->ClearBackBuffer();

	mStartScreen->Render();

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