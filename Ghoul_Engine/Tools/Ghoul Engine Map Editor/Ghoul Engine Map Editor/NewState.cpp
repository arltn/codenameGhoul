#include "NewState.h"

NewState* NewState::inst = NULL;

NewState* NewState::getInstance()
{
	if (inst == NULL)
	{
		inst = new NewState();
		//inst->init();
	}
	return inst;
}

void NewState::init() 
{

};
void NewState::cleanUp() {};

void NewState::pause() {};
void NewState::resume() {};

void NewState::draw() {};
void NewState::update() {};