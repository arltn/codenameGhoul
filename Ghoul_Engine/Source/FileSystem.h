#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "DebuggingSystem.h"

class FileSystem
{
public:
	static FileSystem* getInstance();
	void init();
	SDL_Texture* loadTexture(std::string path, SDL_Renderer* gRenderer);
	SDL_Surface* loadTexture(std::string path);
private:
	FileSystem();
	~FileSystem();
	static FileSystem* inst;
	DebuggingSystem* debug;
};
