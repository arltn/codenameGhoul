#pragma once

#include "GameState.h"
#include "Renderer.h"

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
private:
	static IntroState* inst;
	Renderer* introRenderer;
	IntroState() {};
	vector<SDL_Rect> rects;
protected:
};