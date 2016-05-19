#pragma once
#include "Renderer.h"
#include "InputHandler.h"
#include "eventManager.h"
#include "DebuggingSystem.h"

class SystemManager
{
public:
	static SystemManager* getInstance();
	void update();
	void ShutDown();
	void init();
private:
	Renderer* RenderingSystem;
	InputHandler* InputSystem;
	eventManager* EventSystem;
	DebuggingSystem* DebugSystem;
	SystemManager() {};
	bool running;
	static SystemManager* inst;
};