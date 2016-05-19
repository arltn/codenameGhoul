#include "SystemManager.h"

SystemManager* SystemManager::inst = 0;

SystemManager* SystemManager::getInstance()
{
	if (inst == NULL)
	{
		inst = new SystemManager();
		inst->init();
	}
	return inst;
};

void SystemManager::init()
{
	running = true;
	RenderingSystem = Renderer::getInstance();
	InputSystem = InputHandler::getInstance();
	EventSystem = eventManager::getInst();
	DebugSystem = DebuggingSystem::getInstance();
};

void SystemManager::update()
{
	InputSystem->handleInput(running);
	RenderingSystem->render();
	EventSystem->update();
};


void SystemManager::ShutDown()
{
	DebugSystem->closeDebugging();
};