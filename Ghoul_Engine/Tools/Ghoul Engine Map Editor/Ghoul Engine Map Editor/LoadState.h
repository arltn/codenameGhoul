#pragma once
#include "State.h"
#include "Map.h"
#include <SDL.h>

using namespace std;

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
private:
	string filePath;
	static LoadState* inst;
};