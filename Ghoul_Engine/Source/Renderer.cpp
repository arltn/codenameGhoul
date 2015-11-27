#include "Renderer.h"

void Renderer::init(int screenW = 600, int screenH = 800){
	window = NULL;
	screenSurface = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("SDL COULD NOT INITIALIZE");
	else
	{
		window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenW, screenH, SDL_WINDOW_SHOWN);
		if (window == NULL)
			printf("COULDN\'T CREATE THE WINDOW");
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
}

Renderer::Renderer()
{

}

Renderer *Renderer::inst = 0;

Renderer *Renderer::getInstance()
{
	if (inst == 0)
	{
		inst = new Renderer();
		inst->init(800, 600);
	}
	return inst;
}

void Renderer::renderScene()
{
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

	SDL_UpdateWindowSurface(window);
}

Renderer::~Renderer(){
	SDL_DestroyWindow(window);
}