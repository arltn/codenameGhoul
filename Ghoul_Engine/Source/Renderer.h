#pragma once

#include <SDL.h>
#include "FileSystem.h"
#include "eventListener.h"
#include "DebuggingSystem.h"
#include <stdio.h>
#include <string>

class Renderer
{
public:
	static Renderer *getInstance();
	void render();
	void init(int screenW, int screenH);
	void setTitle(std::string newTitle)
	{
		SDL_SetWindowTitle(window, newTitle.c_str());
	};
	SDL_PixelFormat* getFormat();
	void addTexture(SDL_Texture*);
	SDL_Renderer* getRenderer() { return gRenderer; };
	void clearTextures() { gTextures.clear(); };
protected:
private:
	Renderer();
	~Renderer();
	bool fullscreen;
	void fullScreen();
	void renderScene();
	void handleEvent(Event);
	SDL_Window* window;
	SDL_Surface* screenSurface;
	vector<SDL_Texture*> gTextures;
	SDL_Renderer* gRenderer;
	FileSystem* rendererFileSystem;
	eventListener* rendererListener;
	DebuggingSystem* debug;
	static Renderer *inst;
};