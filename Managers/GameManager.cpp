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

	mPhysicsManager = PhysicsManager::Instance();

	mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Friendly, PhysicsManager::CollisionFlags::Hostile | PhysicsManager::CollisionFlags::HostileProjectiles);
	mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::FriendlyProjectiles, PhysicsManager::CollisionFlags::Hostile);
	mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Hostile, PhysicsManager::CollisionFlags::Friendly | PhysicsManager::CollisionFlags::FriendlyProjectiles);
	mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::HostileProjectiles, PhysicsManager::CollisionFlags::Friendly);

	mScreenManager = ScreenManager::Instance();
}

GameManager::~GameManager()
{
	ScreenManager::Release();
	mScreenManager = NULL;

	PhysicsManager::Release();
	mPhysicsManager = nullptr;

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
	mPhysicsManager->Update();
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