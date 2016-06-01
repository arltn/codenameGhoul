#pragma once


#include "FileSystem.h"
#include "DebuggingSystem.h"
#include "eventListener.h"
#include "Texture.h"
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
	//void addTexture(SDL_Texture*, SDL_Rect* = NULL, SDL_Rect* = NULL);
	//void addBackgroundTexture(SDL_Texture*, SDL_Rect* = NULL, SDL_Rect* = NULL);
	void addTexture(Texture* t) { textures.push_back(t); };
	void addBackgroundTexture(Texture* t) { backgroundTextures.push_back(t); };
	void addForegroundTexture(Texture* t) { foregroundTextures.push_back(t); };
	int getForegroundSize() { return foregroundTextures.size(); };
	int getTexturesSize() { return textures.size(); };
	int getBackgroundSize() { return backgroundTextures.size(); };

	//void addForegroundTexture(SDL_Texture*, SDL_Rect* = NULL, SDL_Rect* = NULL);
	void addDrawRect(SDL_Rect rect, SDL_Color);
	void removeDrawRect() { drawRect = {0,0,0,0}; };
	SDL_Renderer* getRenderer() { return gRenderer; };
	//void addMap(Map m);
	void removeTexture(int);
	void clearBackgroundTextures();
	void clearTextures();
	void clearForegroundTextures();
	void clearAllTextures();
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
	/* Removing these as they appear to be causing heap issues!
	struct Scene
	{
		vector<SDL_Texture*> foregroundTextures;
		vector<SDL_Rect*> foregroundRects;
		vector<SDL_Rect*> foregroundClips;
		vector<SDL_Texture*> textures;
		vector<SDL_Rect*> textureRects;
		vector<SDL_Rect*> textureClips;
		vector<SDL_Texture*> backgroundTextures;
		vector<SDL_Rect*> backgroundRects;
		vector<SDL_Rect*> backgroundClips;
		SDL_Rect* drawRect;
	};
	Scene scene;
	*/
	SDL_Surface* screenSurface;
	SDL_Renderer* gRenderer;
	eventListener* rendererListener;
	FileSystem* file;
	DebuggingSystem* debug;
	vector<Texture*> backgroundTextures;
	vector<Texture*> textures;
	vector<Texture*> foregroundTextures;
	SDL_Rect drawRect;
	SDL_Color drawRectColor;
	static Renderer *inst;

	// Replacing with the singleton Game that contains these two
	//DebuggingSystem* debug;
	//FileSystem* rendererFileSystem;
};