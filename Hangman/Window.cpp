#include "Window.h"

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

	SDL_Event windowEvent;

	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (SDL_QUIT == windowEvent.type)
			{
				break;
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
}