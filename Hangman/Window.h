#include <iostream>
#include <direct.h>
#define GetCurrentDir _getcwd
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL.h>
#undef main

using namespace std;

class Window {

private:
	const int WIDTH = 800, HEIGHT = 600;
	char showMenu(SDL_Surface* surface, TTF_Font* font);
	string getCurrentWorkingDir();

public:
	Window();
};
