#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "GameEntity.h"
#include "../AssetManager.h"

class Texture : public GameEntity
{
protected:
	SDL_Texture* mTex;

	Graphics* mGraphics;

	bool mClipped;

	SDL_Rect mRenderRect;
	
	SDL_Rect mClipRect;

	int mWidth;
	int mHeight;

public:
	Texture(string fileName);
	Texture(string fileName, int x, int y, int w, int h);
	Texture(string text, string fontPath, int size, SDL_Color color);
	~Texture();

	virtual void Render();
};

#endif