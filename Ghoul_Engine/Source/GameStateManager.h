#pragma once

#include "GameState.h"

#include <vector>

class GameStateManager
{
public:
	static GameStateManager* getInstance();
	void changeState(GameState* state);
	void pushState(GameState* state);
	void popState();
	void draw();
	void update();
private:
	static GameStateManager* inst;
	GameStateManager() {};
	vector<GameState*> states;
};