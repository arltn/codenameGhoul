#include <iostream>
#include "Editor.h"


using namespace std;


int main(int argc, char* argv[])
{
	Editor* mainEditor = Editor::getInstance();


	while (mainEditor->isRunning())
	{
		mainEditor->update();
	}

	mainEditor->shutDown();

	return 0;
}