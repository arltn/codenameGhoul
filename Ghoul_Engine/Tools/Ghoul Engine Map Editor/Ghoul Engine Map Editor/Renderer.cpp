#include "Renderer.h"
#include <SDL_image.h>

void Renderer::init() {
	rendererFileSystem = FileSystem::getInstance();
	debug = DebuggingSystem::getInstance();
	window = NULL;
	screenSurface = NULL;
	gRenderer = NULL;
	fullscreen = false;

	int screenW, screenH;

	string debugMessage;


	SDL_DisplayMode dm;
		
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		debugMessage = "SDL COULD NOT INITIALIZE";
		debug->writeMessage(debugMessage);
		//printf(debugMessage.c_str());
	}
	else
	{
		if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
		{
			debugMessage = "SDL_GetDesktopDisplayMode Failed: ";
			debugMessage += SDL_GetError();
			debug->writeMessage(debugMessage);
		}
		else
		{
			screenW = dm.w - 2;
			screenH = dm.h - 70;
		}

		window = SDL_CreateWindow("Map Editor", 1, 29, screenW, screenH, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (window == NULL)
		{
			debugMessage = "COULDN\'T CREATE THE WINDOW";
			debug->writeMessage(debugMessage);
			//printf();
		}

		else
		{
			gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				debugMessage = "Renderer could not be created! SDL Error:\n";
				debugMessage += SDL_GetError();
				debug->writeMessage(debugMessage);
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
				/*
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
				*/
			}
			//screenSurface = SDL_GetWindowSurface(window);

		}

		//TODO:
		//Set up a test for the W key press event
	
		screenSurface = SDL_GetWindowSurface(window);

		rendererListener = new eventListener();
		rendererListener->init();
		fillEvents();
		
		/*
		Event holdEvent("W");
		rendererListener->registerEvent(holdEvent);
		holdEvent.setName("Fullscreen");
		rendererListener->registerEvent(holdEvent);
		*/
	}
}


Renderer::Renderer()
{

}

Renderer *Renderer::inst = 0;

void Renderer::fillEvents() 
{
	vector<string> holdEvents;
	holdEvents = rendererFileSystem->loadFile("..\\Assets\\Config\\renderEvent.dat");


	for (unsigned int x = 0; x < holdEvents.size(); x++)
	{
		rendererListener->registerEvent(holdEvents[x]);
	}

};

Renderer *Renderer::getInstance()
{
	if (inst == 0)
	{
		inst = new Renderer();
		inst->init();
	}
	return inst;
}

void Renderer::renderScene()
{
	SDL_RenderClear(gRenderer);

	//cout << "RENDERER TEXTURE COUNT: " << gTextures.size() << endl;

	//Render texture to screen
	for (unsigned int x = 0; x < gTextures.size(); x++)
	{
		SDL_RenderCopy(gRenderer, gTextures[x], NULL, NULL);
	}
	

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
		//debug->writeMessage("Setting to windowed.");
		SDL_SetWindowFullscreen(window, SDL_FALSE);
		fullscreen = false;
	}
	else if (!fullscreen)
	{
		//debug->writeMessage("Setting to fullscreen.");
		SDL_SetWindowFullscreen(window, SDL_TRUE);
		fullscreen = true;
	}
}

void Renderer::render()
{
	Event holdEvent;

	if (!rendererListener->isEmpty())
	{
		holdEvent = rendererListener->removeEvent();
		handleEvent(holdEvent);
	}

	renderScene();
}


SDL_PixelFormat* Renderer::getFormat()
{
	return screenSurface->format;
};

void Renderer::addTexture(SDL_Texture* texture) 
{
	gTextures.push_back(texture);
};

Renderer::~Renderer(){
	delete rendererListener;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(gRenderer);
	IMG_Quit();
	SDL_Quit();
}