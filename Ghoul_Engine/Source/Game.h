#pragma once

#include "SystemManager.h"
#include "GameStateManager.h"
#include "SpriteSheet.h"
#include "IntroState.h"
#include "event.h"
#include "eventListener.h"
#include "ComponentManager.h"

#include <iostream>
#include <string>
#include <math.h>



class Game
{
public:
	static Game* getInstance();
	void init();
	void update();
	void handleEvent(Event E);
	void shutDown();
	bool isRunning() { return running; };
private:
	Game() {};
	static Game* inst;
	SystemManager* GameSystems;
	eventListener* GameListener;
	GameStateManager* StateManager;
	ComponentManager* GameComponentMan;
	bool running;
};