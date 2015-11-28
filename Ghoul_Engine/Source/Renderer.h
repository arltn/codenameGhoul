#include <SDL.h>
#include "FileSystem.h"
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
protected:
private:
	Renderer();
	~Renderer();
	void renderScene();
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Texture* gTexture;
	SDL_Renderer* gRenderer;
	FileSystem* rendererFileSystem;
	static Renderer *inst;
};