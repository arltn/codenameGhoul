#include "Texture.h"


int Texture::ID = 0;

Texture::Texture(SDL_Texture* texture, SDL_Rect* posRect, SDL_Rect* clip)
{
	mTexture = texture;
	texturePos = posRect;
	clipRect = clip;
	textureID = ID;
	if (ID + 1 > INT_MAX)
	{
		ID = 0;
	}
};