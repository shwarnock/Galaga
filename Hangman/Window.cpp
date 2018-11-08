#include "Window.h"
#include <iostream>
#include <string>

Window::Window()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL could not initialize! SDL ERROR: " << SDL_GetError() << endl;
	}

	SDL_Window *window = SDL_CreateWindow("Hangman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

	if (NULL == window)
	{
		cout << "Could not create window: " << SDL_GetError() << endl;
	}

	SDL_Surface* screen = SDL_GetWindowSurface(window);
	string dir = getCurrentWorkingDir() + "/ExternalDependencies/Roboto-Black.ttf";
	int n = dir.length();
	char char_array[n + 1];
	
	TTF_Font* font = TTF_OpenFont("GSGSDG", 32);
	showMenu(screen, 
}

char Window::showMenu(SDL_Surface* screen, TTF_Font* font)
{
	Uint32 time;
	int x, y;
	const int NUMMENU = 26;
	const char* labels[NUMMENU] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
	SDL_Surface* menus[NUMMENU];
	bool selected[NUMMENU] = { false, false };
	SDL_Color color[2] = { {255,255,255}, {255,0,0} };
	SDL_Rect pos[NUMMENU];

	for (int i = 0; i < NUMMENU; ++i)
	{
		menus[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
		pos[i].x = screen->clip_rect.w / 26 - menus[0]->clip_rect.w / 2;
	}

	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

	SDL_Event event;
	while (1)
	{
		time = SDL_GetTicks();
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					for (int i = 0; i < NUMMENU; ++i)
					{
						SDL_FreeSurface(menus[i]);
					}
					return 1;
				case SDL_MOUSEMOTION:
					x = event.motion.x;
					y = event.motion.y;
					for (int i = 0; i < NUMMENU; ++i)
					{
						if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].h)
						{
							if (!selected[i])
							{
								selected[i] = true;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
							}
						} else
						{
							if (selected[i])
							{
								selected[i] = false;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
							}
						}
					}
				case SDL_MOUSEBUTTONDOWN:
					x = event.button.x;
					y = event.button.y;
					for (int i = 0; i < NUMMENU; i++)
					{
						if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].h)
						{
							return *labels[i];
						}
					}
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						return 0;
					}
			}
		}
	}
}

string Window::getCurrentWorkingDir()
{
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	string current_working_dir(buff);
	return current_working_dir;
}