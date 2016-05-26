#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Map.h"

using namespace std;

int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* render = NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	Map mainMap("C:\\Users\\nja1121\\Documents\\codenameGhoul\\Ghoul_Engine\\Assets\\lazy.MAPDAT");

	SDL_CreateWindowAndRenderer(640, 640, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &window, &render);

	SDL_SetWindowTitle(window, "Map Test");

	bool running = true;

	SDL_Event e;

	mainMap.init(render);

	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				running = false;
		}

		SDL_SetRenderDrawColor(render, 0, 0, 0, 0xFF);
		SDL_RenderClear(render);
		mainMap.draw(render);
		SDL_RenderPresent(render);
	}


	IMG_Quit();
	SDL_Quit();
	return 0;
}