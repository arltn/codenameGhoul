#include <SDL.h>
#include <stdio.h>


class Renderer
{
public:
	static Renderer *getInstance();
	void init(int screenW, int screenH);
	void renderScene();
protected:
private:
	Renderer();
	~Renderer();
	SDL_Window* window;
	SDL_Surface* screenSurface;
	static Renderer *inst;
};