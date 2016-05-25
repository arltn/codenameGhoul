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
	
};

void SystemManager::update()
{
	
};

void SystemManager::writeMessage(string message)
{ 
	DebugSystem->writeMessage(message); 
}

vector<string> SystemManager::loadFile(string path)
{
	return Filesystem->loadFile(path);
}

void SystemManager::ShutDown()
{
	DebugSystem->closeDebugging();
};