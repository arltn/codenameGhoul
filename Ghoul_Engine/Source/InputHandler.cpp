#include "InputHandler.h"

InputHandler* InputHandler::getInstance()
{
	if (inst == 0)
	{
		inst = new InputHandler();
		inst->initHandler();
	}
	return inst;
};
void InputHandler::handleInput(bool &running)
{
	while (SDL_PollEvent(&inputEvent) != 0)
	{
		if (inputEvent.type == SDL_QUIT)
		{
			// SEND QUIT EVENT
			// FOR NOW MAKING A SINGLETON FOR THE MAIN LOOP'S GAME RUNNING BOOL
			running = false;
		}
	}
};
void InputHandler::initHandler()
{};

InputHandler* InputHandler::inst = 0;
InputHandler::InputHandler()
{};
InputHandler::~InputHandler()
{};