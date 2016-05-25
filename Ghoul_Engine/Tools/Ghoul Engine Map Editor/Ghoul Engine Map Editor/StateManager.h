#pragma once

#include "State.h"

#include <vector>

class StateManager
{
public:
	static StateManager* getInstance();
	void changeState(State* state);
	void pushState(State* state);
	void popState();
	void draw();
	void update();
	void cleanUp();
private:
	static StateManager* inst;
	StateManager() {};
	vector<State*> states;
};