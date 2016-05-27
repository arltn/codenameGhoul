#include "LoadState.h"

LoadState* LoadState::inst = NULL;

LoadState* LoadState::getInstance()
{
	//filePath = fileName;
	if (inst == NULL)
	{
		inst = new LoadState();
		//inst->init();
	}
	return inst;
}

void LoadState::init()
{
	//FileSystem* tempFile = FileSystem::getInstance();
	cout << "Load State Init" << endl;
	int fWidth = 0, fHeight = 0, totalTiles = 0;

	getFileHeight(fHeight);
	getFileWidth(fWidth, totalTiles, fHeight);

	ifstream file;
	
	file.open(filePath, ios::in);
	int holdType = 0;
	int holdHeight = 0;
	int holdWidth = 0;
	Renderer* tempRender = Renderer::getInstance();

	buildTileClips();

	SDL_Texture* holdTexture = IMG_LoadTexture(tempRender->getRenderer(), "C:\\Users\\nja1121\\Documents\\codenameGhoul\\Ghoul_Engine\\Assets\\SpriteSheets\\mapTiles.png");
		//SDL_CreateTextureFromSurface(tempRender->getRenderer(), IMG_Load("C:\\Users\\nja1121\\Documents\\codenameGhoul\\Ghoul_Engine\\Assets\\SpriteSheets\\mapTiles.png"));
	if (holdTexture == NULL)
		cout << "Failed to load map sprites" << endl;
	SDL_Rect holdRects[MAX_TILE_COUNT];
	SDL_Rect holdClips[MAX_TILE_COUNT];
	int rectCounter = 0;
	while (file.peek() != EOF)
	{
		file >> holdType;
		
		holdRects[rectCounter].x = holdWidth * (TILE_WIDTH + 5);
		holdRects[rectCounter].y = holdHeight * (TILE_HEIGHT + 5);
		holdRects[rectCounter].w = TILE_WIDTH;
		holdRects[rectCounter].h = TILE_HEIGHT;
		
		holdClips[rectCounter].x = 0;
		holdClips[rectCounter].y = 0;
		holdClips[rectCounter].w = TILE_WIDTH;
		holdClips[rectCounter].h = TILE_HEIGHT;

		//cout << "Adding texture in loadState" << endl;
		//&tileClips[holdType]
		//tempRender->addBackgroundTexture(Texture(holdTexture, &holdRect, &tileClips[holdType]));
		tempRender->addForegroundTexture(new Texture(holdTexture, holdRects[rectCounter], holdClips[rectCounter]));

		//mapTiles.emplace(mapTiles.begin(), Tile(holdWidth * TILE_WIDTH, (holdHeight * TILE_HEIGHT), holdType));
		//cout << "Adding tile" << endl;
		//cout << "h: " << holdHeight << ", w: " << holdWidth << endl;
		if (holdWidth + 1 >= fWidth)
		{
			holdWidth = 0;
			holdHeight++;
		}
		else
			holdWidth += 1;
		rectCounter++;
	}



	file.close();
	//cout << "File to be loaded: " << filePath << endl;
	// NEED TO USE NON MAP STUFF HERE
	//loadStateMap = new Map(filePath);



	//loadStateMap->init(Renderer::getInstance()->getRenderer());


};

void LoadState::getFileHeight(int &mapHeight)
{
	fstream file;
	file.open(filePath, ios::in);
	while (file.peek() != EOF)
	{
		file.ignore(INT_MAX, '\n');
		mapHeight++;
	}
	file.close();
}

void LoadState::getFileWidth(int &mapWidth, int &totalTiles, const int mapHeight)
{
	ifstream file;
	file.open(filePath, ios::in);
	int holdVal = 0;
	while (file.peek() != EOF)
	{
		file >> holdVal;
		totalTiles++;
	}
	file.close();
	mapWidth = totalTiles / mapHeight;
	
}

void LoadState::buildTileClips()
{
	tileClips[0].x = 0;
	tileClips[0].y = 0;
	tileClips[0].w = TILE_WIDTH;
	tileClips[0].h = TILE_HEIGHT;
}

void LoadState::cleanUp() 
{
	//delete loadStateMap;
};

void LoadState::pause() {};
void LoadState::resume() {};

void LoadState::draw() 
{
	//loadStateMap->draw(Renderer::getInstance()->getRenderer());
};
void LoadState::update() 
{
	draw();
};