#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H
#include "Graphics.h"
#include <map>

class AssetManager
{
private:
	static AssetManager* sInstance;
	map<string, SDL_Texture*> mTextures;
	map<string, SDL_Texture*> mTextTextures;
	map<string, TTF_Font*> mFonts;

public:
	static AssetManager* Instance();
	static void Release();

	SDL_Texture* GetTexture(string fileName);
	SDL_Texture* GetText(string text, string fileName, int size, SDL_Color color);

private:
	AssetManager();
	~AssetManager();

	TTF_Font* GetFont(string fileName, int size);
};
#endif
                                                                                                                                                                                                                                                                                                                       