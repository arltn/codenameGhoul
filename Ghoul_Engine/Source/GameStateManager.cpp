#include "GameStateManager.h"

GameStateManager* GameStateManager::inst = 0;

GameStateManager* GameStateManager::getInstance() 
{
	if (inst == 0)
	{
		inst = new GameStateManager();
	}
	return inst;
};

void GameStateManager::changeState(GameState* state) 
{
	if (!states.empty())
	{
		states.back()->cleanup();
		states.pop_back();
	}
	states.push_back(state);
	states.back()->init();
};

void GameStateManager::pushState(GameState* state) 
{
	if (!states.empty())
	{
		states.back()->pause();
	}

	states.push_back(state);
	states.back()->init();
};

void GameStateManager::popState() 
{
	if (!states.empty()) {
		states.back()->cleanup();
		states.pop_back();
	}


	if (!states.empty()) {
		states.back()->resume();
	}
};

void GameStateManager::update() 
{
	if (!states.empty())
	{
		states.back()->update();
	}
};

void GameStateManager::draw()
{
	if (!states.empty())
	{
		states.back()->draw();
	}
}