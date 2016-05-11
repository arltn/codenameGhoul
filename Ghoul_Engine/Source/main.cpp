#include "Game.h"
#include <SDL.h>
#include <stdio.h>
#include "Clock.h"

const int FRAMES_PER_SECOND = 60;
const float TICKS_PER_FRAME = 1000 / FRAMES_PER_SECOND;

Clock gameClock, fpsClock;

void shutDown()
{

};

int main(int argc, char* argv[])
{
	Game* MainGame = Game::getInstance();
	int countedFrames = 0;
	gameClock.start();
	while (MainGame->isRunning())
	{
		fpsClock.start();
		
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

		MainGame->update();

	}


	shutDown();

	return 0;
}