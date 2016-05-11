#pragma once

#include "GameState.h"
#include "Renderer.h"
#include "GameStateManager.h"
#include "Entity.h"
#include "PositionComponent.h"
#include <vector>

class IntroState : public GameState
{
public:
	static IntroState* getInstance();
	void init();
	void cleanup();

	void pause();
	void resume();

	void draw();
	void update();
	void handleEvent(Event E);
private:
	static IntroState* inst;
	FileSystem* IntroFile;	
	Renderer* introRenderer;
	eventListener* introListener;
	SDL_Texture* IntroBackground;
	IntroState() {};
	Event queuedEvent;
protected:
};