#include "MenuState.h"
#include "NewState.h"
#include "LoadState.h"
#include <Windows.h>

#define Black SDL_Color {0,0,0};
#define White SDL_Color {255,255,255};



MenuState* MenuState::inst = 0;

MenuState* MenuState::getInstance() 
{
	if (inst == NULL)
	{
		inst = new MenuState();
		//inst->init();
	}
	return inst;
};

void MenuState::init()
{
	TTF_Init();
	Renderer* tempRenderer = Renderer::getInstance();
	FileSystem* tempFile = FileSystem::getInstance();
	SDL_Texture* holdTexture;
	SDL_Surface* holdSurface;
	holdSurface = tempFile->loadTexture("..\\Assets\\Images\\map_editor_background.bmp");
	buttonFont = TTF_OpenFont("..\\Assets\\Font\\Deslucida-black-font-FFP.ttf", 100);
	holdTexture = SDL_CreateTextureFromSurface(tempRenderer->getRenderer(), holdSurface);
	tempRenderer->addBackgroundTexture(new Texture(holdTexture, { 0,0,0,0 }, { 0,0,0,0 }));
	
	int screenH;
	int screenW;
	
	SDL_DisplayMode dm;

	if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
	{
		DebuggingSystem* tempDebug = DebuggingSystem::getInstance();
		tempDebug->writeMessage("Error getting Desktop Display Mode");
	}
	else
	{
		screenW = dm.w;
		screenH = dm.h;
	}

	
	newButton.buttonBorder.x = screenW / 2 - 300;
	newButton.buttonBorder.y = screenH / 3 - 100;
	newButton.buttonBorder.h = 200;
	newButton.buttonBorder.w = 600;
	newButton.buttonColor = White;
	newButton.buttonPressedColor = Black;
	newButton.textColor = Black;
	newButton.buttonText = "New Map (CURRENTLY NOT WORKING)";

	loadButton.buttonBorder.x = screenW / 2 - 100;
	loadButton.buttonBorder.y = screenW / 3;
	loadButton.buttonBorder.h = 200;
	loadButton.buttonBorder.w = 200;
	loadButton.buttonColor = White;
	loadButton.textColor = Black;
	loadButton.buttonPressedColor = Black;
	loadButton.buttonText = "Load Map";

	
	holdSurface = TTF_RenderText_Solid(buttonFont, newButton.buttonText.c_str(), newButton.textColor);
	holdTexture = SDL_CreateTextureFromSurface(tempRenderer->getRenderer(), holdSurface);

	tempRenderer->addTexture(new Texture(holdTexture, newButton.buttonBorder, {0,0,0,0}));
	//tempRenderer->addSurface(holdSurface);

	holdSurface = TTF_RenderText_Solid(buttonFont, loadButton.buttonText.c_str(), loadButton.textColor);
	holdTexture = SDL_CreateTextureFromSurface(tempRenderer->getRenderer(), holdSurface);

	tempRenderer->addTexture(new Texture(holdTexture, loadButton.buttonBorder, {0,0,0,0}));
	//tempRenderer->addTexture(holdTexture, &loadButton.buttonBorder);
	//tempRenderer->addSurface(holdSurface);


	Event holdEvent("Mouse Move");

	menuStateListener.init();

	menuStateListener.registerEvent(holdEvent);

	holdEvent.setName("Mouse Click");

	menuStateListener.registerEvent(holdEvent);

	SDL_FreeSurface(holdSurface);
//	SDL_DestroyTexture(holdTexture);
};

void MenuState::update()
{
	if (!menuStateListener.isEmpty())
	{
		Event holdEvent;
		holdEvent = menuStateListener.removeEvent();
		handleEvent(holdEvent);
		if (!menuStateListener.isEmpty())
		{
			if (menuStateListener.getLastEvent() == holdEvent)
			{
				//Remove Multiple events
				menuStateListener.removeEvent();
			}
		}
	}
};


void MenuState::handleEvent(Event e)
{
	Renderer* tempRenderer = Renderer::getInstance();
	if (e.getName() == "Mouse Move")
	{
		int x, y;
		x = e.getValue1();
		y = e.getValue2();
		//cout << "Mouse @ " << x << ", " << y << endl;
		//Check if the mouse is inside the buttons
		if (x > newButton.buttonBorder.x &&
			x < newButton.buttonBorder.x + newButton.buttonBorder.w &&
			y > newButton.buttonBorder.y &&
			y < newButton.buttonBorder.y + newButton.buttonBorder.h)
		{
			//newButton.buttonColor = Black;
			tempRenderer->addDrawRect(newButton.buttonBorder, {255, 255, 255, 255});
			//cout << "Over New Button" << endl;
		}
		
		else if (x > loadButton.buttonBorder.x &&
			x < loadButton.buttonBorder.x + loadButton.buttonBorder.w &&
			y > loadButton.buttonBorder.y &&
			y < loadButton.buttonBorder.y + loadButton.buttonBorder.h)
		{
			//loadButton.buttonColor = Black;
			tempRenderer->addDrawRect(loadButton.buttonBorder, { 255, 255, 255, 255 });
			//cout << "Over Load Button" << endl;
		}
//		else
			//tempRenderer->removeDrawRect();
	} // Mouse Move
	if (e.getName() == "Mouse Click")
	{
		cout << "Mouse Click Detected by MenuState" << endl;
		int x, y;
		x = e.getValue1();
		y = e.getValue2();
		//cout << "Mouse @ " << x << ", " << y << endl;
		//Check if the mouse is inside the buttons
		if (x > newButton.buttonBorder.x &&
			x < newButton.buttonBorder.x + newButton.buttonBorder.w &&
			y > newButton.buttonBorder.y &&
			y < newButton.buttonBorder.y + newButton.buttonBorder.h)
		{
			StateManager* stateMan = StateManager::getInstance();
			stateMan->changeState(NewState::getInstance());
			//newButton.buttonColor = Black;
			//cout << "Over New Button" << endl;
		}

		else if (x > loadButton.buttonBorder.x &&
			x < loadButton.buttonBorder.x + loadButton.buttonBorder.w &&
			y > loadButton.buttonBorder.y &&
			y < loadButton.buttonBorder.y + loadButton.buttonBorder.h)
		{
			//loadButton.buttonColor = Black;
			//tempRenderer->addDrawRect(&loadButton.buttonBorder);
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
			fileSelected = GetOpenFileName(&ofn);
			
			//string messageText = '"' + ofn.lpstrFile + '"';
			//cout << messageText << endl;
			//fileSelected = MessageBox(NULL, ofn.lpstrFile, "File Name", MB_OK);



			if(fileSelected)
			{
				StateManager* stateMan = StateManager::getInstance();
				string holdFile = ofn.lpstrFile;
				Renderer::getInstance()->clearAllTextures();
				LoadState* loadState = LoadState::getInstance();
				loadState->setFilePath(holdFile);
				stateMan->changeState(loadState);
			}
			
		}
	}
}

void MenuState::cleanUp()
{
	cout << "MenuState Cleanup" << endl;
	TTF_CloseFont(buttonFont);
	TTF_Quit();
}