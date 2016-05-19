#pragma once
#include "FileSystem.h"
#include <vector>

using namespace std;

class SpriteSheet
{
public:
	SpriteSheet(string, int, int);
	~SpriteSheet();
	SDL_Rect getSprite(int);
private:
	SDL_Surface* spriteSheet;
	vector<SDL_Rect> clipSections;
};