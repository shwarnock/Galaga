#include "Texture.h"

Texture::Texture(string fileName)
{
	mGraphics = Graphics::Instance();
	
	mTex = AssetManager::Instance()->GetTexture(fileName);

	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mClipped = false;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Texture::Texture(string fileName, int x, int y, int w, int h)
{
	mGraphics = Graphics::Instance();

	mTex = AssetManager::Instance()->GetTexture(fileName);

	mClipped = true;

	mWidth = w;
	mHeight = h;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	mClipRect.x = x;
	mClipRect.y = y;
	mClipRect.w = mWidth;
	mClipRect.h = mHeight;
}

Texture::Texture(string text, string fontPath, int size, SDL_Color color)
{
	mGraphics = Graphics::Instance();

	mTex = AssetManager::Instance()->GetText(text, fontPath, size, color);

	mClipped = false;

	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Texture::~Texture()
{
	mTex = NULL;
	mGraphics = NULL;
}

void Texture::Render()
{
	Vector2 pos = Pos(world);
	mRenderRect.x = (int)(pos.x - mWidth * 0.5f);
	mRenderRect.y = (int)(pos.y - mHeight * 0.5f);
	mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect);
}