#include <iostream>
#include "SystemManager.h"
#include "eventListener.h"


using namespace std;

SystemManager* editorSystems;
eventListener* quitListener;
bool running;

int main(int argc, char* argv[])
{
	Event quit("Quit");
	quitListener = new eventListener();
	quitListener->registerEvent(quit);
	

	editorSystems = SystemManager::getInstance();
	editorSystems->init();
	
	
	running = true;
	
	while (running) 
	{
		editorSystems->update();

		if (!quitListener->isEmpty())
		{
			cout << "hello world" << endl;
			quitListener->removeEvent();
			running = false;
		}

	}

	


	editorSystems->ShutDown();

	delete quitListener;

	return 0;
}