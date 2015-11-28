#include "Renderer.h"
#include <SDL_image.h>

void Renderer::init(int screenW = 600, int screenH = 800){
	rendererFileSystem = FileSystem::getInstance();
	window = NULL;
	screenSurface = NULL;
	gRenderer = NULL;
	gTexture = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("SDL COULD NOT INITIALIZE");
	else
	{
		window = SDL_CreateWindow("Code Name Ghoul", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenW, screenH, SDL_WINDOW_SHOWN);
		if (window == NULL)
			printf("COULDN\'T CREATE THE WINDOW");
		else
		{
			gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL){
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);

				int imgFlags = IMG_INIT_PNG;// | IMG_INIT_JPG | IMG_INIT_TIF;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_Image Error: %s\n", IMG_GetError());
				}
				else
				{
					gTexture = rendererFileSystem->loadTexture("C:\\Users\\nate\\Documents\\Development\\codenameGhoul\\codenameGhoul\\Assets\\Pictures\\Demon.png", gRenderer);
				}
			}
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
	SDL_RenderClear(gRenderer);

	//Render texture to screen
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

	//Update screen
	SDL_RenderPresent(gRenderer);

	//SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));

	//SDL_UpdateWindowSurface(window);
}

void Renderer::render()
{
	renderScene();
}

Renderer::~Renderer(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(gRenderer);
	IMG_Quit();
}