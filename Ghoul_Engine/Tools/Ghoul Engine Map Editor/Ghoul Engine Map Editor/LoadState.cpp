#include "LoadState.h"
#include "FileSystem.h"

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

	cout << "File to be loaded: " << filePath << endl;

};
void LoadState::cleanUp() {};

void LoadState::pause() {};
void LoadState::resume() {};

void LoadState::draw() {};
void LoadState::update() {};