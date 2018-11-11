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

	mChild = new GameEntity(100.0f, 400.0f);
	mParent = new GameEntity(100.0f, 500.0f);
}

GameManager::~GameManager()
{
	Graphics::Release();
	mGraphics = NULL;
	Timer::Release();
	mTimer = NULL;
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
			mGraphics->Render();

			mTimer->Reset();
		}
	}
}