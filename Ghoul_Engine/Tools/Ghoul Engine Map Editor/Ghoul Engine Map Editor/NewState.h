#pragma once


#include "State.h"
#include <string>

using namespace std;

class NewState : public State
{
public:
	void init();
	void cleanUp();

	void pause();
	void resume();

	void draw();
	void update();
	static NewState* getInstance();
private:
	static NewState* inst;
};
