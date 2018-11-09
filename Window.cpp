#include "Window.h"
#include <iostream>
#include <string>

Window::Window()
{
	SDL_SetMainReady();
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL could not initialize! SDL ERROR: " << SDL_GetError() << endl;
	}
	cout << "HELLO";
	SDL_Window *window = SDL_CreateWindow("Hangman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

	if (NULL == window)
	{
		cout << "Could not create window: " << SDL_GetError() << endl;
	}

	cout << "I AM HERE";
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 20, 20, 20, 20);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	SDL_Surface* screen = SDL_GetWindowSurface(window);
	string dir = getCurrentWorkingDir() + "/Roboto-Black.ttf";
	cout << dir; 
	char * path = new char[dir.size() + 1];

	path[dir.size()] = 0;
	memcpy(path, dir.c_str(), dir.size());

	cout << path;
	TTF_Init();
	TTF_Font* font = TTF_OpenFont(path, 32);
	showMenu(screen, font);

	SDL_DestroyWindow(window);
	SDL_Quit();
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
		pos[i].x = screen->clip_rect.w / 26 - menus[i]->clip_rect.w / 26;
		SDL_BlitSurface(menus[i], NULL, screen, &pos[i]);
	}

	bool isRunning = true;
	SDL_Event event;
	while (isRunning)
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
					isRunning = false;
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
							for (int j = 0; j < 2; ++j)
							{
								SDL_FreeSurface(menus[j]);
							}
							return *labels[i];
						}
					}
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						for (int i = 0; i < 2; ++i)
						{
							SDL_FreeSurface(menus[i]);
						}
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
	
	int index = 0;
	while (true)
	{
		index = current_working_dir.find("\\", index);
		if (index == -1) break;

		current_working_dir.replace(index, 1, "/");
	}
	return current_working_dir;
}