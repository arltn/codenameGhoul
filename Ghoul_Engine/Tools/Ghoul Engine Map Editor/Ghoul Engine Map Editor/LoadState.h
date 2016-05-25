#pragma once
#include "State.h"

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
private:
	string filePath;
	static LoadState* inst;
	
};