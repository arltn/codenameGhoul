#include "SystemManager.h"
#include "GameStateManager.h"
#include "SpriteSheet.h"
#include "IntroState.h"
#include <SDL.h>
#include <stdio.h>
#include "Clock.h"
#include "event.h"
#include "eventListener.h"
#include <string>
#include <math.h>
#include <iostream>


const int FRAMES_PER_SECOND = 60;
const float TICKS_PER_FRAME = 1000 / FRAMES_PER_SECOND;

Clock gameClock, fpsClock;
SystemManager* GameSystems;
eventListener* quitListener;
GameStateManager* StateManager;
bool running;

void handleEvent(Event E)
{
	// Allowed as this is currently the only event being handled by this listener.
	if(E.getName() == "Quit")
		running = false;
};

void shutDown()
{
	// Mem Leak proctection
	delete quitListener;

	//Quit SDL subsystems
	GameSystems->ShutDown();
	SDL_Quit();
};

int main(int argc, char* argv[])
{
	printf("Starting Program\n\n");

	SpriteSheet testSheet("..\\Assets\\testSheet.bmp", 32, 32);

	GameSystems = SystemManager::getInstance();
	StateManager = GameStateManager::getInstance();
	StateManager->changeState(IntroState::getInstance());

	quitListener = new eventListener();
	quitListener->init();
	Event quitEvent("Quit");
	quitListener->registerEvent(quitEvent);

	Event holdEvent;

	int countedFrames = 0;
	running = true;
	gameClock.start();
	while (running)
	{
		fpsClock.start();
		GameSystems->update();
		StateManager->update();
		StateManager->draw();
		float frameTime = (Uint32)(gameClock.getTicks() / 1000);

		float averageFrames = countedFrames / frameTime;
		if (averageFrames > 2000000)
		{
			averageFrames = 0;
		}
		//std::string newTitle = "average framerate: " + std::to_string(round(averageFrames));
		//gameRenderer->setTitle(newTitle);
		Uint32 frameTicks = fpsClock.getTicks();
		if (frameTicks < TICKS_PER_FRAME)
		{
			SDL_Delay(TICKS_PER_FRAME - frameTicks);
		}
		//gameClock.update(gameClock.getCurrentSeconds());
		countedFrames++;

		if (!quitListener->isEmpty())
		{
			holdEvent = quitListener->removeEvent();
			handleEvent(holdEvent);
		}

	}


	shutDown();

	return 0;
}