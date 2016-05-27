#pragma once
#include "State.h"
#include "Tile.h"
#include "FileSystem.h"
#include "Editor.h"
//#include "Map.h"
#include <SDL.h>

using namespace std;

const int MAX_TILE_COUNT = 100;

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
	void getFileHeight(int &);
	void getFileWidth(int &, int &, const int);
	void buildTileClips();
private:
	string filePath;
	static LoadState* inst;
	SDL_Rect tileClips[MAX_TILE_COUNT];
	//Map* loadStateMap;
};