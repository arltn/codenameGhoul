#include <SDL.h>
#include <stdio.h>
#include "Renderer.h"

Renderer* gameRenderer;

int main(int argc, char* argv[])
{
	bool quit = false;
	SDL_Event e;
	gameRenderer = Renderer::getInstance();

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		gameRenderer->renderScene();
	}

	//Quit SDL subsystems
	SDL_Quit();
	return 0;
}