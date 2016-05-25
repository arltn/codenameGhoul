#pragma once
#include "Renderer.h"
#include "InputHandler.h"
#include "eventManager.h"
#include "DebuggingSystem.h"
#include "FileSystem.h"
#include <string>
#include <vector>

class SystemManager
{
public:
	static SystemManager* getInstance();
	void update();
	void ShutDown();
	void init();
	void writeMessage(string message);
	vector<string> loadFile(string path);
private:
	Renderer* RenderingSystem;
	InputHandler* InputSystem;
	eventManager* EventSystem;
	DebuggingSystem* DebugSystem;
	FileSystem* Filesystem;
	SystemManager() {};
	bool running;
	static SystemManager* inst;
};