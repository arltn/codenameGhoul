#pragma once


#include <SDL.h>
#include <SDL_image.h>
#include <limits.h>

using namespace std;

class Texture
{
public:
	Texture(SDL_Texture*, SDL_Rect* = NULL, SDL_Rect* = NULL);
	//~Texture() { SDL_DestroyTexture(mTexture); };
	SDL_Texture* getTexture() { return mTexture; };
	SDL_Rect* getClip() { return clipRect; };
	SDL_Rect* getPosRect() { return texturePos; };
private:
	SDL_Texture* mTexture;
	SDL_Rect* clipRect;
	SDL_Rect* texturePos;
	int textureID;
	static int ID;
};