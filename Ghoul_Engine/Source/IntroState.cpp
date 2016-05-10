#include "IntroState.h"
#include "GameStateManager.h"

IntroState* IntroState::inst = 0;

IntroState* IntroState::getInstance() 
{
	if (inst == 0) 
	{
		inst = new IntroState();
	}
	return inst;
};

void IntroState::init() 
{
	cout << "IntroState Initialized" << endl;
	IntroFile = FileSystem::getInstance();
	introRenderer = Renderer::getInstance();
	introListener = new eventListener();
	introListener->init();
	queuedEvent.setName("Any Key");
	introListener->registerEvent(queuedEvent);
	IntroBackground = IntroFile->loadTexture("..\\Assets\\Pictures\\intro.bmp", introRenderer->getRenderer());
	introRenderer->addTexture(IntroBackground);
};
void IntroState::cleanup()
{
	introRenderer->clearTextures();
	delete introListener;
	SDL_DestroyTexture(IntroBackground);
	//delete introListener;
};

void IntroState::pause() {};
void IntroState::resume() {};

void IntroState::draw() 
{
};

void IntroState::update() 
{
	if (!introListener->isEmpty())
	{
		queuedEvent = introListener->removeEvent();
		handleEvent(queuedEvent);
	}
};

void IntroState::handleEvent(Event E)
{
	GameStateManager* eventMan = GameStateManager::getInstance();
	if (E.getName() == "Any Key")
	{
		cout << "Event Hit, pushing state" << endl;
		eventMan->changeState(IntroState::getInstance());
	}
};