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

	cout << "File to be loaded: " << filePath << endl;
	Editor* tempEditor = Editor::getInstance();
	tempEditor->addMap(filePath);


};
void LoadState::cleanUp() {};

void LoadState::pause() {};
void LoadState::resume() {};

void LoadState::draw() {};
void LoadState::update() {};