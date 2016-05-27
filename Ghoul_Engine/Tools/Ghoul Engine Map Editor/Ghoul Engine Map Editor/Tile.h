#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

using namespace std;

const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 64;

enum tileType
{
	// Default non shown tile
	BLACK_TILE = 0,
	GREEN_TILE
};

class Tile
{
public:
	Tile(int, int, int);
	int getType() { return tileType; };
	SDL_Rect getBox() { return cBox; };
	void setType(int i) { tileType = i; };
	friend ostream& operator << (ostream& out, Tile tile);
private:
	SDL_Rect cBox;
	int tileType;
};
