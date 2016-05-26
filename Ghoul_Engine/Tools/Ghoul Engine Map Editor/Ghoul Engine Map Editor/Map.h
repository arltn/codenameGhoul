#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "Tile.h"


using namespace std;

const int TILE_BOX_COUNT = 100;

enum tileType
{
	// Default non shown tile
	BLACK_TILE
};

class Map
{
public:
	Map(string path);
	void init(SDL_Renderer* render);
	void draw(SDL_Renderer* render);
private:
	vector<Tile> mapTiles;
	int mapWidth, mapHeight, totalTiles;
	void getFileWidth(ifstream&);
	void getFileHeight(ifstream&);
	SDL_Rect tileBoxes[TILE_BOX_COUNT];
	SDL_Texture* sheet;
};