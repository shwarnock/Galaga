#include "AssetManager.h"

AssetManager* AssetManager::sInstance = NULL;

AssetManager* AssetManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new AssetManager();
	}

	return sInstance;
}

void AssetManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
	for (auto text : mTextures)
	{
		if (text.second != NULL)
		{
			SDL_DestroyTexture(text.second);
		}
	}

	mTextures.clear();
}

SDL_Texture* AssetManager::GetTexture(string fileName)
{
	string fullPath = SDL_GetBasePath();
	fullPath.append("..\\..\\assets\\" + fileName);

	printf(fullPath.c_str());

	if (mTextures[fullPath] == nullptr)
		mTextures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);

	return mTextures[fullPath];
}