#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "DebuggingSystem.h"
#include <iostream>
#include <vector>

class FileSystem
{
public:
	static FileSystem* getInstance();
	void init();
	SDL_Texture* loadTexture(std::string path, SDL_Renderer* gRenderer);
	SDL_Surface* loadTexture(std::string path);
	vector<string> loadFile(std::string path);
private:
	FileSystem();
	~FileSystem();
	static FileSystem* inst;
	DebuggingSystem* debug;
};
