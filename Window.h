#include <iostream>
#include <direct.h>
#define GetCurrentDir _getcwd
#include <stdio.h>
#include <SDL_ttf.h>
#define SDL_MAIN_DEFINED
#include <SDL.h>
#include <algorithm>

using namespace std;

class Window {

private:
	const int WIDTH = 800, HEIGHT = 600;
	char showMenu(SDL_Surface* surface, TTF_Font* font);
	string getCurrentWorkingDir();

public:
	Window();
};
