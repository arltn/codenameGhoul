#include "IntroState.h"

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
	SDL_Rect tempRect;
	tempRect.h = 50;
	tempRect.w = 50;
	tempRect.x = 0; 
	tempRect.y = 0;
	rects.emplace_back(tempRect);
	introRenderer = Renderer::getInstance();
};
void IntroState::cleanup() {};

void IntroState::pause() {};
void IntroState::resume() {};

void IntroState::draw() 
{
};

void IntroState::update() 
{
};