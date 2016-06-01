#include "LoadState.h"

#define White SDL_Color {255,255,255,255};

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
	//cout << "Load State Init" << endl;

	TTF_Init();

	SDL_DisplayMode dm;

	SDL_GetDesktopDisplayMode(0, &dm);

	loadStateViewPort.x = 0;
	loadStateViewPort.y = 25;
	loadStateViewPort.h = dm.h;
	loadStateViewPort.w = dm.w - 64 * 3;


	Event holdEvent("Mouse Move");

	loadStateListener.init();
	loadStateListener.registerEvent(holdEvent);

	holdEvent.setName("Mouse Click");
	loadStateListener.registerEvent(holdEvent);

	getFileHeight();
	getFileWidth();

	ifstream file;
	
	file.open(filePath, ios::in);
	int holdType = 0;
	int holdHeight = 0;
	int holdWidth = 0;
	Renderer* tempRender = Renderer::getInstance();

	SDL_Texture* holdTexture = IMG_LoadTexture(tempRender->getRenderer(), "..\\..\\..\\Assets\\SpriteSheets\\mapTiles.png");
	SDL_Surface* tempSurface = IMG_Load("..\\..\\..\\Assets\\SpriteSheets\\mapTiles.png");


	mapSpriteWidth = tempSurface->clip_rect.w / 64;
	mapSpirteHeight = tempSurface->clip_rect.h / 64;

	SDL_FreeSurface(tempSurface);

	buildTileClips();


	//cout << "Map sprite w: " << mapSpriteWidth << ", h: " << mapSpirteHeight << endl;

		//SDL_CreateTextureFromSurface(tempRender->getRenderer(), IMG_Load("C:\\Users\\nja1121\\Documents\\codenameGhoul\\Ghoul_Engine\\Assets\\SpriteSheets\\mapTiles.png"));
	if (holdTexture == NULL)
		cout << "Failed to load map sprites" << endl;
	SDL_Rect holdRects[MAX_TILE_COUNT];
	SDL_Rect holdClips[MAX_TILE_COUNT];
	int rectCounter = 0;
	while (file.peek() != EOF)
	{
		file >> holdType;
		
		backgroundTypes.push_back(holdType);

		holdRects[rectCounter].x = holdWidth * (TILE_WIDTH);
		holdRects[rectCounter].y = holdHeight * (TILE_HEIGHT) + 25;
		holdRects[rectCounter].w = TILE_WIDTH;
		holdRects[rectCounter].h = TILE_HEIGHT;
		
		holdClips[rectCounter].x = 0;
		holdClips[rectCounter].y = 0;
		holdClips[rectCounter].w = TILE_WIDTH;
		holdClips[rectCounter].h = TILE_HEIGHT;

		//cout << "Adding texture in loadState" << endl;
		//&tileClips[holdType]
		//tempRender->addBackgroundTexture(Texture(holdTexture, &holdRect, &tileClips[holdType]));
		tempRender->addBackgroundTexture(new Texture(holdTexture, holdRects[rectCounter], tileClips[holdType]));
			//holdClips[rectCounter]));

		//mapTiles.emplace(mapTiles.begin(), Tile(holdWidth * TILE_WIDTH, (holdHeight * TILE_HEIGHT), holdType));
		//cout << "Adding tile" << endl;
		//cout << "h: " << holdHeight << ", w: " << holdWidth << endl;
		if (holdWidth + 1 >= mapWidth)
		{
			holdWidth = 0;
			holdHeight++;
		}
		else
			holdWidth += 1;
		rectCounter++;
	}



	file.close();

	SDL_Rect menuRect;
	SDL_Surface* holdSurface;
	//
	string fileName = "C:\\Users\\nja1121\\Documents\\codenameGhoul\\Ghoul_Engine\\Tools\\Ghoul Engine Map Editor\\Assets\\Font\\Deslucida-black-font-FFP.ttf";
	font = TTF_OpenFont(fileName.c_str(), 24);

	menuRect.x = 5;
	menuRect.y = 0;
	menuRect.w = 64;
	menuRect.h = 25;

	if (font == NULL)
		DebuggingSystem::getInstance()->writeMessage("Font failed to load");

	holdSurface = TTF_RenderText_Solid(font, "Menu", { 255,255,255,255 });

	//cout << holdSurface->clip_rect.w << endl;

	holdTexture = SDL_CreateTextureFromSurface(tempRender->getRenderer(), holdSurface);

	Texture* tempTexture = new Texture(holdTexture, menuRect, { 0,0,0,0 });


	//tempTexture =  Texture(holdTexture, menuRect, { 0,0,0,0 });

	//cout << "LOAD STATE STUFF!\nMENU BUTTON ID: " << tempTexture->getID() << endl;

	tempRender->addForegroundTexture(tempTexture);


	holdSurface = TTF_RenderText_Solid(font, "Save", { 255,255,255,255 });
	holdTexture = SDL_CreateTextureFromSurface(tempRender->getRenderer(), holdSurface);

	//tempTexture.setTexture(holdTexture, { 5,25,64,25 }, { 0,0,0,0 });
	tempTexture = new Texture(holdTexture, { 5,25,64,25 }, { 0,0,0,0 });

	//cout << "LOAD STATE STUFF!\nSAVE BUTTON ID: " << tempTexture->getID() << endl;

	menuTextures.emplace_back(tempTexture);
	menuTextureIDs.push_back(tempTexture->getID());

	holdSurface = TTF_RenderText_Solid(font, "Save As", { 255,255,255,255 });
	holdTexture = SDL_CreateTextureFromSurface(tempRender->getRenderer(), holdSurface);

	//tempTexture.setTexture(holdTexture, { 5,25,64,25 }, { 0,0,0,0 });
	tempTexture = new Texture(holdTexture, { 5,50,64,25 }, { 0,0,0,0 });

	//cout << "LOAD STATE STUFF!\nSAVE BUTTON ID: " << tempTexture->getID() << endl;

	menuTextures.emplace_back(tempTexture);
	menuTextureIDs.push_back(tempTexture->getID());

	menuShown = false;

	//cout << "File to be loaded: " << filePath << endl;
	// NEED TO USE NON MAP STUFF HERE
	//loadStateMap = new Map(filePath);



	//loadStateMap->init(Renderer::getInstance()->getRenderer());


};

void LoadState::getFileHeight()
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

void LoadState::getFileWidth()
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
	int tileCounter = 0;
	for (int y = 0; y < mapSpirteHeight; y++)
	{
		for (int x = 0; x < mapSpriteWidth; x++)
		{
			tileClips[tileCounter].x = x * TILE_WIDTH;
			tileClips[tileCounter].y = y * TILE_HEIGHT;
			tileClips[tileCounter].w = TILE_WIDTH;
			tileClips[tileCounter].h = TILE_HEIGHT;
			tileCounter++;
		}
		tileCounter++;
	}
}

void LoadState::cleanUp() 
{
	//delete loadStateMap;
	TTF_CloseFont(font);
	TTF_Quit();
};

void LoadState::pause() {};
void LoadState::resume() {};

void LoadState::draw() 
{
	//SDL_RenderSetViewport(Renderer::getInstance()->getRenderer(), &loadStateViewPort);
	//loadStateMap->draw(Renderer::getInstance()->getRenderer());
};
void LoadState::update() 
{
	if (!loadStateListener.isEmpty())
	{
		Event holdEvent;
		holdEvent = loadStateListener.removeEvent();
		handleEvent(holdEvent);
		if (!loadStateListener.isEmpty())
		{
			if (loadStateListener.getLastEvent() == holdEvent)
			{
				//Remove Multiple events
				loadStateListener.removeEvent();
			}
		}
	}
	draw();
};

bool checkCollision(SDL_Rect A, SDL_Rect B)
{
	if (A.x > B.x &&
		A.x < B.x + B.w &&
		A.y > B.y &&
		A.y < B.y + B.h)
		return true;
	return false;
}

void LoadState::handleEvent(Event E)
{
	if (E.getName() == "Mouse Move")
	{
		//cout << "Mouse @ X: " << E.getValue1() << " Y: " << E.getValue2() << endl;
		SDL_Rect mouseRect;
		mouseRect.x = E.getValue1();
		mouseRect.y = E.getValue2() - 15;
		mouseRect.h = 10;
		mouseRect.w = 10;
		
		SDL_Rect drawRect;
		SDL_Rect collisionRect;
		collisionRect.h = TILE_HEIGHT;
		collisionRect.w = TILE_WIDTH;

		if (mouseRect.y + 15 > 25 && !menuShown)
		{

			drawRect.w = TILE_WIDTH;
			drawRect.h = TILE_HEIGHT;
			drawRect.x = (mouseRect.x / 64) * 64;
			drawRect.y = ((mouseRect.y - 15) / 64) * 64 + 25;


			Renderer::getInstance()->addDrawRect(drawRect, SDL_Color{ 255,255,255,255 });
		}
		else if (mouseRect.y + 15 > 25 && menuShown)
		{
			if (mouseRect.x < 70)
			{
				drawRect.w = 66;
				drawRect.h = 25;
				drawRect.x = 4;
				drawRect.y = ((mouseRect.y +15) / 25) * 25;

				if (drawRect.y > (menuTextures.size()) * 25)
					drawRect.y = (menuTextures.size()) * 25;

				Renderer::getInstance()->addDrawRect(drawRect, SDL_Color{ 255,255,255,255 });
			}
			else
				Renderer::getInstance()->removeDrawRect();
		}
		else if (mouseRect.y + 15 < 25)
		{
			if (mouseRect.x < 70)
			{
				drawRect.w = 66;
				drawRect.h = 25;
				drawRect.x = 4;
				drawRect.y = 0;


				Renderer::getInstance()->addDrawRect(drawRect, SDL_Color{ 255,255,255,255 });
			}
			else
				Renderer::getInstance()->removeDrawRect();
		}
		else
			Renderer::getInstance()->removeDrawRect();
		/*
		for (int x = 0; x < mapWidth; x += 64)
		{
			for (int y = 0; y < mapHeight; y += 64)
			{
				collisionRect.x = x;
				collisionRect.y = y;
				if (checkCollision(mouseRect, collisionRect))
				{
					drawRect.x = x * 65;
					drawRect.y = y * 65;
					drawRect.h = TILE_HEIGHT;
					drawRect.w = TILE_WIDTH;
					cout << "Adding drawRect" << endl;
					
				}
			}
		}
		*/

	}
	if (E.getName() == "Mouse Click")
	{
		SDL_Rect mouseRect;

		mouseRect.x = E.getValue1();
		mouseRect.y = E.getValue2();
		mouseRect.h = 10;
		mouseRect.w = 10;

		if (mouseRect.y < 25)
			if (mouseRect.x <= 70)
				//cout << "Menu Button clicked" << endl;
				showMenu();
		if (checkCollision(mouseRect, { 4,25,66,25 }) && menuShown)
			saveMap();
		if (checkCollision(mouseRect, { 4,50,66,25 }) && menuShown)
			saveAsMap();
			//cout << "Save clicked!" << endl;
		//TODO ADD SAVE FUNCTIONALITY

	}
}

void LoadState::showMenu()
{
	if (menuShown)
	{
		menuShown = false;
		for (unsigned int x = 0; x < menuTextureIDs.size(); x++)
		{
			//cout << "SHOW MENU REMOVING ID: " << menuTextureIDs[x] << endl;
			Renderer::getInstance()->removeTexture(menuTextureIDs[x]);
		}
	}
	else
	{
		menuShown = true;
		for (unsigned int x = 0; x < menuTextures.size(); x++)
		{
			Renderer::getInstance()->addForegroundTexture(menuTextures[x]);
		}
	}

};

void LoadState::saveMap()
{
	ofstream file;
	file.open(filePath);
	file.clear();
	for (unsigned int x = 0; x < backgroundTypes.size(); x++)
	{
		if (x % mapWidth == 0 && x != 0)
			file << endl;
			//cout << endl;
		//cout << 0 << backgroundTypes[x] << " ";
		file << " " << 0 << backgroundTypes[x];
	}
	file.close();
}

void LoadState::saveAsMap()
{
	bool fileSelected = false;
	OPENFILENAME ofn;
	// a another memory buffer to contain the file name
	char szFile[100];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Map Files\0*.MAPDAT\0\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = "..\\..\\..\\Assets\\Maps\\";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	fileSelected = GetSaveFileName(&ofn);

	if (fileSelected)
	{
		saveMap(ofn.lpstrFile);
	}

};

void LoadState::saveMap(string fileName)
{
	ofstream file;
	file.open(fileName + ".MAPDAT");
	file.clear();
	for (unsigned int x = 0; x < backgroundTypes.size(); x++)
	{
		if (x % mapWidth == 0 && x != 0)
			file << endl;
		//cout << endl;
		//cout << 0 << backgroundTypes[x] << " ";
		file << " " << 0 << backgroundTypes[x];
	}
	file.close();
}