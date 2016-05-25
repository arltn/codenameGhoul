#pragma once


#include "FileSystem.h"
#include "DebuggingSystem.h"
#include "eventListener.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <vector>


class Renderer
{
public:
	static Renderer *getInstance();
	void render();
	void init();
	void setTitle(std::string newTitle)
	{
		SDL_SetWindowTitle(window, newTitle.c_str());
	};
	SDL_PixelFormat* getFormat();
	void addTexture(SDL_Texture*, SDL_Rect* = NULL);
	void addBackgroundTexture(SDL_Texture*, SDL_Rect* = NULL);
	void addForegroundTexture(SDL_Texture*, SDL_Rect* = NULL);
	void addDrawRect(SDL_Rect* rect) { scene.drawRect = rect; };
	void removeDrawRect() { scene.drawRect = NULL; };
	SDL_Renderer* getRenderer() { return gRenderer; };
	void clearTextures();
	void fillEvents();
protected:
private:
	Renderer();
	~Renderer();
	bool fullscreen;
	void fullScreen();
	void renderScene();
	void handleEvent(Event);
	SDL_Window* window;
	struct Scene
	{
		vector<SDL_Texture*> foregroundTextures;
		vector<SDL_Rect*> foregroundRects;
		vector<SDL_Texture*> textures;
		vector<SDL_Rect*> textureRects;
		vector<SDL_Texture*> backgroundTextures;
		vector<SDL_Rect*> backgroundRects;
		SDL_Rect* drawRect;
	};
	Scene scene;
	SDL_Surface* screenSurface;
	SDL_Renderer* gRenderer;
	eventListener* rendererListener;
	FileSystem* file;
	DebuggingSystem* debug;

	static Renderer *inst;

	// Replacing with the singleton Game that contains these two
	//DebuggingSystem* debug;
	//FileSystem* rendererFileSystem;
};