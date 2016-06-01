#include "Texture.h"


int Texture::ID = 0;

Texture::Texture(SDL_Texture* texture, SDL_Rect posRect, SDL_Rect clip)
{
	SDL_Rect nullRect = {0,0,0,0};
	mTexture = texture;
	if (posRect.x == 0 && posRect.y == 0 && posRect.w == 0 && posRect.h == 0)
		texturePos = NULL;
	else
		texturePos = new SDL_Rect(posRect);
	if (clip.x == 0 && clip.y == 0 && clip.w == 0 && clip.h == 0)
		clipRect = NULL;
	else
		clipRect = new SDL_Rect(clip);
	textureID = ID;
	if (ID + 1 > INT_MAX)
	{
		ID = 0;
	}
	else
		ID++;
};

void Texture::setTexture(SDL_Texture* texture, SDL_Rect posRect, SDL_Rect clip)
{
	SDL_Rect nullRect = { 0,0,0,0 };
	mTexture = texture;
	if (posRect.x == 0 && posRect.y == 0 && posRect.w == 0 && posRect.h == 0)
		texturePos = NULL;
	else
		texturePos = new SDL_Rect(posRect);
	if (clip.x == 0 && clip.y == 0 && clip.w == 0 && clip.h == 0)
		clipRect = NULL;
	else
		clipRect = new SDL_Rect(clip);
	textureID = ID;
	if (ID + 1 > INT_MAX)
	{
		ID = 0;
	}
	else
		ID++;
};


SDL_Rect* Texture::getClip() 
{ 
	return clipRect;
};

SDL_Rect* Texture::getPosRect() 
{ 
	return texturePos;
};

Texture::~Texture()
{
	//delete clipRect;
	//delete texturePos;
}