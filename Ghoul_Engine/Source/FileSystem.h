#include <SDL.h>
#include <SDL_image.h>
#include <string>

class FileSystem
{
public:
	static FileSystem* getInstance();
	void init();
	SDL_Texture* loadTexture(std::string path, SDL_Renderer* gRenderer);
private:
	FileSystem();
	~FileSystem();
	static FileSystem* inst;
};
