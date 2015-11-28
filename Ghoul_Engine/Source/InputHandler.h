#include <SDL.h>

class InputHandler
{
public:
	static InputHandler* getInstance();
	void handleInput(bool &running);
private:
	void initHandler();
	static InputHandler* inst;
	SDL_Event inputEvent;
protected:
	InputHandler();
	~InputHandler();
};