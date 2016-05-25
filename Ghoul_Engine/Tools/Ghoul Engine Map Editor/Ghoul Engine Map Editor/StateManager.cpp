#include "StateManager.h"

StateManager* StateManager::inst = 0;

StateManager* StateManager::getInstance() 
{
	if (inst == 0)
	{
		inst = new StateManager();
	}
	return inst;
};

void StateManager::changeState(State* state) 
{
	if (!states.empty())
	{
		states.back()->cleanUp();
		states.pop_back();
	}
	states.push_back(state);
	states.back()->init();
};

void StateManager::pushState(State* state) 
{
	if (!states.empty())
	{
		states.back()->pause();
	}

	states.push_back(state);
	states.back()->init();
};

void StateManager::popState() 
{
	if (!states.empty()) {
		states.back()->cleanUp();
		states.pop_back();
	}


	if (!states.empty()) {
		states.back()->resume();
	}
};

void StateManager::update() 
{
	if (!states.empty())
	{
		states.back()->update();
	}
};

void StateManager::draw()
{
	if (!states.empty())
	{
		states.back()->draw();
	}
}

void StateManager::cleanUp()
{
	while (!states.empty())
	{
		states.back()->cleanUp();
		states.pop_back();
	}
};