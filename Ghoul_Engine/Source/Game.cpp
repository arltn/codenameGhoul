#include "Game.h"


Game* Game::inst = 0;

Game* Game::getInstance() 
{
	if (inst == 0)
	{
		inst = new Game();
		inst->init();
	}
	return inst;
};

void Game::init()
{
	printf("Starting Program\n\n");

	SpriteSheet testSheet("..\\Assets\\testSheet.bmp", 32, 32);

	GameSystems = SystemManager::getInstance();
	StateManager = GameStateManager::getInstance();
	GameComponentMan = ComponentManager::getInstance();
	StateManager->changeState(IntroState::getInstance());

	running = true;



	GameListener = new eventListener();
	GameListener->init();
	Event quitEvent("Quit");
	GameListener->registerEvent(quitEvent);
};

void Game::handleEvent(Event E)
{
	// Allowed as this is currently the only event being handled by this listener.
	if (E.getName() == "Quit")
		running = false;
};

void Game::update()
{
	if (!GameListener->isEmpty())
	{
		handleEvent(GameListener->removeEvent());
	}

	GameSystems->update();
	StateManager->update();
	GameComponentMan->update();

	StateManager->draw();

	
}

void Game::shutDown() 
{
	// Mem Leak proctection
	delete GameListener;

	//Quit SDL subsystems
	GameSystems->ShutDown();
};