#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H
#include "Graphics.h"
#include <map>

class AssetManager
{
private:
	static AssetManager* sInstance;
	map<string, SDL_Texture*> mTextures;

public:
	static AssetManager* Instance();
	static void Release();

	SDL_Texture* GetTexture(string fileName);

private:
	AssetManager();
	~AssetManager();
};
#endif
                                                                                                                                                                                                                                                                                                                       