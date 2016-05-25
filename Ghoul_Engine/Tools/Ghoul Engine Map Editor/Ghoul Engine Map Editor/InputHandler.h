#pragma once

#include <SDL.h>
#include <stdio.h>
#include "event.h"
#include "eventManager.h"

class InputHandler
{
public:
	static InputHandler* getInstance();
	void handleInput(bool &running);
private:
	void initHandler();
	static InputHandler* inst;
	eventManager* eventMan;
	SDL_Event inputEvent;
protected:
	InputHandler();
	~InputHandler();
};