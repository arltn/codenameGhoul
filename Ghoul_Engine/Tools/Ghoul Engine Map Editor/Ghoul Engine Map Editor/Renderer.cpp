#include "Renderer.h"



void Renderer::init() {

	//Replacing with Editor because both systems are contained there
	file = FileSystem::getInstance();
	debug = DebuggingSystem::getInstance();
	
	window = NULL;
	screenSurface = NULL;
	gRenderer = NULL;
	fullscreen = false;

	int screenW, screenH;

	string debugMessage;


	SDL_DisplayMode dm;
		
	//clearTextures();


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

		screenSurface = SDL_GetWindowSurface(window);

		rendererListener = new eventListener();
		rendererListener->init();
		fillEvents();
		
		//scene.drawRect = NULL;
		//scene.mapTiles = NULL;

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
	holdEvents = file->loadFile("..\\Assets\\Config\\renderEvent.dat");


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
	SDL_SetRenderDrawColor(gRenderer, 255, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	/*
	//cout << "RENDERER TEXTURE COUNT: " << gTextures.size() << endl;

	//Render the background:
	if (!scene.backgroundTextures.empty())
	{
		//cout << "backgroundTextures size: " << scene.backgroundTextures.size() << endl;
		for (unsigned int x = 0; x < scene.backgroundTextures.size(); x++)
		{
			//SDL_BlitSurface(screenSurface, NULL, scene.backgroundTextures[x], &scene.backgroundTextures[x]->clip_rect);

			SDL_RenderCopy(gRenderer, scene.backgroundTextures[x], scene.backgroundClips[x], scene.backgroundRects[x]);//scene.backgroundClips[x], scene.backgroundRects[x]);
			//scene.backgroundRects[x]
																								   //
		}
	}

	//Render texture to screen
	if (!scene.textures.empty())
	{
		//cout << "textures size: " << scene.textures.size() << endl;
		for (unsigned int x = 0; x < scene.textures.size(); x++)
		{
			//SDL_BlitSurface(screenSurface, NULL, scene.Textures[x], NULL);
			//&scene.Textures[x]->clip_rect
			SDL_RenderCopy(gRenderer, scene.textures[x], scene.textureClips[x], scene.textureRects[x]);
		}
	}

	if (!scene.foregroundTextures.empty())
	{
		//cout << "foregroundTextures size: " << scene.foregroundTextures.size() << endl;
		for (unsigned int x = 0; x < scene.foregroundTextures.size(); x++)
		{
			//SDL_BlitSurface(screenSurface, NULL, scene.foregroundTextures[x], NULL);
			//&scene.foregroundTextures[x]->clip_rect
			SDL_RenderCopy(gRenderer, scene.foregroundTextures[x], scene.foregroundClips[x], scene.foregroundRects[x]);
		}
	}
	

	if (scene.drawRect != NULL)
	{
		SDL_RenderDrawRect(gRenderer, scene.drawRect);
	}
	*/
	//Update screen
	SDL_RenderPresent(gRenderer);
	//SDL_UpdateWindowSurface(window);

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

	//renderScene();
}


SDL_PixelFormat* Renderer::getFormat()
{
	return screenSurface->format;
};

/*void Renderer::addTexture(SDL_Texture* texture, SDL_Rect* rect, SDL_Rect* clip)
{
	scene.textures.push_back(texture);
	scene.textureRects.push_back(rect);
	scene.textureClips.push_back(clip);
};

void Renderer::addBackgroundTexture(SDL_Texture* texture, SDL_Rect* rect, SDL_Rect* clip)
{
	scene.backgroundTextures.push_back(texture);
	scene.backgroundRects.push_back(rect);
	scene.backgroundClips.push_back(clip);
	//cout << "Background Scene Info: \n" << scene.backgroundTextures.size() << endl << scene.backgroundRects.size() << endl << scene.backgroundClips.size() << endl;
};
void Renderer::addForegroundTexture(SDL_Texture* texture, SDL_Rect* rect, SDL_Rect* clip)
{
	scene.foregroundTextures.push_back(texture);
	scene.foregroundRects.push_back(rect);
	scene.foregroundClips.push_back(clip);
};
*/
//void Renderer::addMap(Map m)
//{
//	scene.mapTiles = &m;
//};

/*
void Renderer::clearTextures() 
{ 
	for (unsigned int x = 0; x < scene.backgroundTextures.size(); x++)
	{
		SDL_DestroyTexture(scene.backgroundTextures[x]);
	}

	for (unsigned int x = 0; x < scene.textures.size(); x++)
	{
		SDL_DestroyTexture(scene.textures[x]);
	}

	for (unsigned int x = 0; x < scene.foregroundTextures.size(); x++)
	{
		SDL_DestroyTexture(scene.foregroundTextures[x]);
	}

	scene.drawRect = NULL;

	scene.backgroundTextures.clear();
	scene.textures.clear(); 
	scene.foregroundTextures.clear();
	scene.backgroundRects.clear();
	scene.textureRects.clear();
	scene.foregroundRects.clear();
	scene.backgroundClips.clear();
	scene.foregroundClips.clear();
	scene.textureClips.clear();
};
*/
Renderer::~Renderer(){
	delete rendererListener;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(gRenderer);
	IMG_Quit();
	SDL_Quit();
}