#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(string filename, int w, int h) 
{
	FileSystem* tempFile;
	tempFile = FileSystem::getInstance();
	SDL_Rect holdRect;
	spriteSheet = tempFile->loadTexture(filename.c_str());

	for (int x = 0; x < spriteSheet->clip_rect.h / h; x++)
	{
		for (int y = 0; y < spriteSheet->clip_rect.w / w; y++)
		{
			holdRect = {y * h, x * w, w, h};
			clipSections.push_back(holdRect);
		}
	}

};
SpriteSheet::~SpriteSheet() {};

SDL_Rect SpriteSheet::getSprite(int i) 
{
	return clipSections[i];
};