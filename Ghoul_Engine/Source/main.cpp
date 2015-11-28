#include <SDL.h>
#include <stdio.h>
#include "Renderer.h"
#include "InputHandler.h"
#include "Clock.h"
#include <string>
#include <math.h>

const int FRAMES_PER_SECOND = 60;
const float TICKS_PER_FRAME = 1000 / FRAMES_PER_SECOND;

Renderer* gameRenderer;
InputHandler* gameInput;
Clock gameClock, fpsClock;

int main(int argc, char* argv[])
{
	int countedFrames = 0;
	bool running = true;
	gameRenderer = Renderer::getInstance();
	gameInput = InputHandler::getInstance();
	gameClock.start();
	while (running)
	{
		fpsClock.start();
		gameInput->handleInput(running);
		gameRenderer->render();
		float frameTime = (Uint32)(gameClock.getTicks() / 1000);

		float averageFrames = countedFrames / frameTime;
		if (averageFrames > 2000000)
		{
			averageFrames = 0;
		}
		std::string newTitle = "average framerate: " + std::to_string(round(averageFrames));
		gameRenderer->setTitle(newTitle);
		Uint32 frameTicks = fpsClock.getTicks();
		if (frameTicks < TICKS_PER_FRAME)
		{
			SDL_Delay(TICKS_PER_FRAME - frameTicks);
		}
		//gameClock.update(gameClock.getCurrentSeconds());
		countedFrames++;
	}

	//Quit SDL subsystems
	SDL_Quit();
	return 0;
}