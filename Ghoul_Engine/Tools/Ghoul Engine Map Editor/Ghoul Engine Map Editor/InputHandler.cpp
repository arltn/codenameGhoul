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
	Event queueEvent;
	
	while (SDL_PollEvent(&inputEvent) != 0)
	{
		if (inputEvent.type == SDL_QUIT)
		{
			queueEvent.setName("Quit");
			eventMan->sendNow(queueEvent);
			// SEND QUIT EVENT
			// FOR NOW MAKING A SINGLETON FOR THE MAIN LOOP'S GAME RUNNING BOOL
			running = false;
		}
		if (inputEvent.type == SDL_KEYDOWN)
		{
			queueEvent.setName("Any Key");
			eventMan->sendNow(queueEvent);
			switch (inputEvent.key.keysym.sym)
			{
			case SDLK_w:				
				queueEvent.setName("W");
				eventMan->queueEvent(queueEvent);
				break;
			case SDLK_F4:
				//cout << "Sending Fullscreen Event" << endl;
				queueEvent.setName("Fullscreen");
				eventMan->queueEvent(queueEvent);
				//eventMan->printListeners();
				break;
			default:
				break;
			}
		}
		if (inputEvent.type == SDL_MOUSEMOTION)
		{
			int x, y;
			queueEvent.setName("Mouse Move");
			SDL_GetMouseState(&x, &y);
			queueEvent.setValues(x, y);
			eventMan->queueEvent(queueEvent);
		}
		if (inputEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			int x, y;
			queueEvent.setName("Mouse Click");
			SDL_GetMouseState(&x, &y);
			queueEvent.setValues(x, y);
			eventMan->queueEvent(queueEvent);
		}
	}
};
void InputHandler::initHandler()
{
	eventMan = eventManager::getInst();
};

InputHandler* InputHandler::inst = 0;
InputHandler::InputHandler()
{};
InputHandler::~InputHandler()
{};
