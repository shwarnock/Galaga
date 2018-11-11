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

	mTex = new AnimatedTexture("AlphabetSheet.png", 0, 0, 25, 28, 7, 5.0f, AnimatedTexture::horizontal);
	mTex->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));
}

GameManager::~GameManager()
{
	Graphics::Release();
	mGraphics = NULL;

	AssetManager::Release();
	mAssetManager = NULL;

	InputManager::Release();
	mInputManager = NULL;

	Timer::Release();
	mTimer = NULL;

	delete mTex;
	mTex = NULL;
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
			mInputManager->Update();

			mTex->Update();

			mGraphics->ClearBackBuffer();

			mTex->Render();

			mGraphics->Render();

			mTimer->Reset();
		}
	}
}