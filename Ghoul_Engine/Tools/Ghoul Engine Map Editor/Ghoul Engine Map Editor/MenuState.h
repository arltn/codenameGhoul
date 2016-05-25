#pragma once
#include "State.h"
#include "Renderer.h"
#include "eventListener.h"
#include "StateManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>



class MenuState : public State
{
public:
	void init();
	void cleanUp();

	void pause() {};
	void resume() {};

	void draw() {};
	void update();
	void handleEvent(Event);
	static MenuState* getInstance();
private:
	static MenuState* inst;
	TTF_Font* buttonFont;
	struct Button 
	{
		SDL_Rect buttonBorder;
		SDL_Color buttonColor;
		SDL_Color buttonPressedColor;
		SDL_Color textColor;
		string buttonText;
	};

	Button newButton;
	Button loadButton;

	eventListener menuStateListener;

};