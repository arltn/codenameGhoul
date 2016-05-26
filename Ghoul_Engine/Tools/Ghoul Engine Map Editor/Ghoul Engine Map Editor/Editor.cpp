#include "Editor.h"



Editor* Editor::inst = 0;

Editor* Editor::getInstance()
{
	if (inst == 0)
	{
		inst = new Editor();
		inst->init();
	}
	return inst;
};

void Editor::init()
{
	printf("Starting Program\n\n");

	//SpriteSheet testSheet("..\\Assets\\testSheet.bmp", 32, 32);

	RenderingSystem = Renderer::getInstance();
	InputSystem = InputHandler::getInstance();
	EventSystem = eventManager::getInst();
	DebugSystem = DebuggingSystem::getInstance();
	Filesystem = FileSystem::getInstance();
	EditorStateManager = StateManager::getInstance();
	//EditorComponentMan = ComponentManager::getInstance();
	EditorStateManager->changeState(MenuState::getInstance());

	running = true;



	EditorListener = new eventListener();
	EditorListener->init();
	Event quitEvent("Quit");
	EditorListener->registerEvent(quitEvent);
};

void Editor::handleEvent(Event E)
{
	// Allowed as this is currently the only event being handled by this listener.
	if (E.getName() == "Quit")
		running = false;
};

void Editor::update()
{
	if (!EditorListener->isEmpty())
	{
		handleEvent(EditorListener->removeEvent());
	}

	EventSystem->update();

	InputSystem->handleInput();
	RenderingSystem->render();
	EditorStateManager->update();


	//EditorComponentMan->update();

	//StateManager->draw();


}

void Editor::shutDown()
{
	// Mem Leak proctection
	delete EditorListener;

	EditorStateManager->cleanUp();

	//Quit SDL subsystems
	//EditorSystems->ShutDown();
	DebugSystem->closeDebugging();

};