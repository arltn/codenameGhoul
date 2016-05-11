#include "FileSystem.h"
#include "Renderer.h"

FileSystem * FileSystem::inst = 0;

FileSystem* FileSystem::getInstance()
{
	if (inst == 0)
	{
		inst = new FileSystem();
		inst->init();
	}
	return inst;
}

void FileSystem::init()
{
	debug = DebuggingSystem::getInstance();
};

FileSystem::FileSystem()
{
}

FileSystem::~FileSystem()
{
}
SDL_Texture* FileSystem::loadTexture(std::string path, SDL_Renderer* gRenderer)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path

	string debugMessage;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		debugMessage = "Unable to load image " + path + "SDL_image Error:\n";
		debugMessage += IMG_GetError();
		debug->writeMessage(debugMessage);
		//printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			debugMessage = "Unable to create texture from " + path + " SDL Error:\n";
			debugMessage += SDL_GetError();
			debug->writeMessage(debugMessage);
			//printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

SDL_Surface* FileSystem::loadTexture(std::string path)
{
	Renderer* tempRend;
	tempRend = Renderer::getInstance();
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, tempRend->getFormat(), NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
};


vector<string> FileSystem::loadFile(std::string path)
{
	ifstream retVal;
	vector<string> retVect;
	string holdString;
	retVal.open(path, ios::in);
	while (!retVal.eof())
	{
		std::getline(retVal, holdString);
		retVect.push_back(holdString);
		//debug->writeMessage(holdString);
	}
	retVal.close();
	return retVect;
}
