#ifndef _STAR_H
#define _STAR_H

#include "../Timer.h"
#include "../Entities/Texture.h"

class Star : Texture
{
private:

	static bool sScroll;

	Timer* mTimer;

	bool mVisible;
	float mFlickerTimer;
	float mFlickerSpeed;

	float mScrollSpeed;

public:

	static void Scroll(bool b);

	Star(int layer);
	~Star();

	void Update();
	void Render();

private:
	void ScrollStart();
};

#endif
