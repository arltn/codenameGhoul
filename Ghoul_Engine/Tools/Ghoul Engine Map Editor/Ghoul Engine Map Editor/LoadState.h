#pragma once
#include "State.h"
#include "Tile.h"
#include "FileSystem.h"
#include "Editor.h"
//#include "Map.h"
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

const int MAX_TILE_COUNT = 1000;

class LoadState : public State
{
public:
	void init();
	void cleanUp();

	void pause();
	void resume();

	void draw();
	void update();
	static LoadState* getInstance();
	void setFilePath(string fileName) { filePath = fileName; };
	string getFilePath() { return filePath; };
	void getFileHeight();
	void getFileWidth();
	void buildTileClips();
	void handleEvent(Event E);
private:
	string filePath;
	static LoadState* inst;
	SDL_Rect tileClips[MAX_TILE_COUNT];
	eventListener loadStateListener;
	int mapWidth;
	int mapHeight;
	int totalTiles;
	int mapSpriteWidth;
	int mapSpirteHeight;
	SDL_Rect loadStateViewPort;
	TTF_Font* font;
	//Map* loadStateMap;
};