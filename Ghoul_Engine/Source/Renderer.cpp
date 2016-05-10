#include "Renderer.h"
#include <SDL_image.h>

void Renderer::init(int screenW = 600, int screenH = 800){
	rendererFileSystem = FileSystem::getInstance();
	debug = DebuggingSystem::getInstance();
	window = NULL;
	screenSurface = NULL;
	gRenderer = NULL;
	gTexture = NULL;
	fullscreen = false;

	string debugMessage;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		debugMessage = "SDL COULD NOT INITIALIZE";
		debug->writeMessage(debugMessage);
		//printf(debugMessage.c_str());
	}
	else
	{
		window = SDL_CreateWindow("Code Name Ghoul", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenW, screenH, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (window == NULL)
		{ 
			debugMessage = "COULDN\'T CREATE THE WINDOW";
			debug->writeMessage(debugMessage);
			//printf();
		}
			
		else
		{
			gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL){
				debugMessage = "Renderer could not be created! SDL Error:\n";
				debugMessage += SDL_GetError();
				debug->writeMessage(debugMessage);
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);

				int imgFlags = IMG_INIT_PNG;// | IMG_INIT_JPG | IMG_INIT_TIF;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					debugMessage = "SDL_image could not initialize! SDL_Image Error:\n";
					debugMessage += IMG_GetError();
					debug->writeMessage(debugMessage);
					//printf(, IMG_GetError());
				}
				else
				{
					gTexture = rendererFileSystem->loadTexture("..\\Assets\\Pictures\\Demon.png", gRenderer);
				}
			}
			screenSurface = SDL_GetWindowSurface(window);
		}
		
		//TODO:
		/*
		Set up a test for the W key press event
		*/
		rendererListener = new eventListener();
		rendererListener->init();
		Event holdEvent("W");
		rendererListener->registerEvent(holdEvent);
		holdEvent.setName("Fullscreen");
		rendererListener->registerEvent(holdEvent);
		
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
	Event holdEvent;
	
	if (!rendererListener->isEmpty())
	{
		holdEvent = rendererListener->removeEvent();
		handleEvent(holdEvent);
	}

	SDL_RenderClear(gRenderer);

	//Render texture to screen
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

	//Update screen
	SDL_RenderPresent(gRenderer);

	//SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));

	//SDL_UpdateWindowSurface(window);



};


void Renderer::handleEvent(Event E)
{
	//cout << "Renderer handleEvent" << endl;
	if (E.getName() == "Fullscreen")
		fullScreen();
	//cout << E << endl;
	//double holdValue = E.getValue();
	//string message = "Event: " + E.getName();
	//debug->writeMessage(message);
}

void Renderer::fullScreen()
{
	if (fullscreen)
	{
		debug->writeMessage("Setting to windowed.");
		SDL_SetWindowFullscreen(window, SDL_FALSE);
		fullscreen = false;
	}
	else if (!fullscreen)
	{
		debug->writeMessage("Setting to fullscreen.");
		SDL_SetWindowFullscreen(window, SDL_TRUE);
		fullscreen = true;
	}
}

void Renderer::render()
{
	renderScene();
}


SDL_PixelFormat* Renderer::getFormat()
{
	return screenSurface->format;
};

Renderer::~Renderer(){
	delete rendererListener;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(gRenderer);
	IMG_Quit();
}