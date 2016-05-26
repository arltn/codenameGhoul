#include "LoadState.h"
#include "FileSystem.h"
#include "Editor.h"

LoadState* LoadState::inst = NULL;

LoadState* LoadState::getInstance()
{
	//filePath = fileName;
	if (inst == NULL)
	{
		inst = new LoadState();
		//inst->init();
	}
	return inst;
}

void LoadState::init()
{
	//FileSystem* tempFile = FileSystem::getInstance();
	cout << "Load State Init" << endl;
	//cout << "File to be loaded: " << filePath << endl;
	loadStateMap = new Map(filePath);

	loadStateMap->init(Renderer::getInstance()->getRenderer());


};
void LoadState::cleanUp() 
{
	delete loadStateMap;
};

void LoadState::pause() {};
void LoadState::resume() {};

void LoadState::draw() 
{
	loadStateMap->draw(Renderer::getInstance()->getRenderer());
};
void LoadState::update() 
{
	draw();
};