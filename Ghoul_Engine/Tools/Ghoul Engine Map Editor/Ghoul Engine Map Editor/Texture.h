#pragma once


#include <SDL.h>
#include <SDL_image.h>
#include <limits.h>

using namespace std;

class Texture
{
public:
	Texture(SDL_Texture*, SDL_Rect, SDL_Rect);
	~Texture();
	SDL_Texture* getTexture() { return mTexture; };
	int getID() { return textureID; };
	SDL_Rect* getClip();
	SDL_Rect* getPosRect();
private:
	SDL_Texture* mTexture;
	SDL_Rect* clipRect;
	SDL_Rect* texturePos;
	int textureID;
	static int ID;
};