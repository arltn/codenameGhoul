#pragma once

#include "StateManager.h"
#include "Map.h"
#include "SpriteSheet.h"
#include "MenuState.h"
#include "event.h"
#include "eventListener.h"
#include "InputHandler.h"
#include "DebuggingSystem.h"
#include "FileSystem.h"
#include "Renderer.h"
//#include "ComponentManager.h"
#include <vector>
#include <iostream>
#include <string>
#include <math.h>


using namespace std;

class Editor
{
public:
	static Editor* getInstance();
	void init();
	void update();
	void handleEvent(Event E);
	void shutDown();
	bool isRunning() { return running; };
	void addMap(string path) { editorMap = new Map(path); };

private:
	Editor() {};
	static Editor* inst;
	eventListener* EditorListener;
	StateManager* EditorStateManager;
	Renderer* RenderingSystem;
	InputHandler* InputSystem;
	eventManager* EventSystem;
	DebuggingSystem* DebugSystem;
	FileSystem* Filesystem;
	//ComponentManager* EditorComponentMan;
	bool running;
	Map* editorMap;
};