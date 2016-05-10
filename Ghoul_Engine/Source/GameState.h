#pragma once

#include "eventListener.h"
#include "eventManager.h"
#include <SDL.h>

class GameState
{
public:
	virtual void init() = 0;
	virtual void cleanup() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void draw() = 0;
	virtual void update() = 0;
protected:
	GameState() { }
};