#include "Map.h"
#include "Renderer.h"
#include <fstream>

void Map::getFileHeight(ifstream& file)
{
	while (file.peek() != EOF)
	{
		file.ignore(INT_MAX, '\n');
		mapHeight++;
	}
}

void Map::getFileWidth(ifstream &file)
{
	int holdVal = 0;
	while (file.peek() != EOF)
	{
		file >> holdVal;
		totalTiles++;
	}

	mapWidth = totalTiles / mapHeight;
}

Map::Map(string path)
{
	ifstream file;
	file.open(path, ios::in);

	totalTiles = 0;
	mapHeight = 0;
	mapWidth = 0;

	if (!file)
		cout << "unable to open file" << endl;
	else
	{
		getFileHeight(file);
		file.close();
		file.open(path, ios::in);
		getFileWidth(file);
		cout << "Map demensions:\n             W: "
			<< mapWidth << "\n             H: "
			<< mapHeight << "\n         Total: " << totalTiles << endl;
		file.close();
		file.open(path, ios::in);
		int holdType = 0;
		int holdHeight = 0, holdWidth = 0;

		while (file.peek() != EOF)
		{
			file >> holdType;
			mapTiles.emplace(mapTiles.begin(), Tile(holdWidth * TILE_WIDTH, (holdHeight * TILE_HEIGHT) + 70, holdType));
			//cout << "Adding tile" << endl;
			//cout << "h: " << holdHeight << ", w: " << holdWidth << endl;
			if (holdWidth + 1 >= mapWidth)
			{
				holdWidth = 0;
				holdHeight++;
			}
			else
				holdWidth += 1;
		}
		
		for (unsigned int x = 0; x < mapTiles.size(); x++)
		{
			//cout << mapTiles[x] << endl;
		}
	}
	file.close();
	
	sheet = NULL;

	tileBoxes[BLACK_TILE].x = 0;
	tileBoxes[BLACK_TILE].y = 0;
	tileBoxes[BLACK_TILE].h = TILE_HEIGHT;
	tileBoxes[BLACK_TILE].w = TILE_WIDTH;

}



void Map::init(SDL_Renderer* render)
{
	SDL_Surface* hold;
	string FilePath = "C:\\Users\\nja1121\\Documents\\codenameGhoul\\Ghoul_Engine\\Assets\\SpriteSheets\\mapTiles.png";
	hold = IMG_Load(FilePath.c_str());
	//hold = IMG_Load("..\\..\\..\\Assets\\SpriteSheets\\mapTiles.png");
	
	if (hold == NULL)
		cout << "IMG_Load: " << IMG_GetError() << endl;
	else
	{
		cout << "Loaded map spirtes" << endl;
		sheet = SDL_CreateTextureFromSurface(render, hold);
	}
	cout << "mapTiles size: " << mapTiles.size() << endl;
	
	for (unsigned int x = 0; x < mapTiles.size(); x++)
	{
		//cout << "Adding background Texture" << endl;
		//cout << "Tile " << x << ": " << mapTiles[x] << endl;
		/*<< tileBoxes[mapTiles[x].getType()].x << ", "
			             << tileBoxes[mapTiles[x].getType()].y << ", "
						 << tileBoxes[mapTiles[x].getType()].w << ", "
						 << tileBoxes[mapTiles[x].getType()].h*/
		cout << "type: " << mapTiles[x].getBox().x << ", "
			<< mapTiles[x].getBox().y << ", "
			<< mapTiles[x].getBox().w << ", "
			<< mapTiles[x].getBox().h
			             << endl;
		//Renderer::getInstance()->addBackgroundTexture(sheet, &mapTiles[x].getBox(), &tileBoxes[mapTiles[x].getType()]);//, 
	}
}

void Map::draw(SDL_Renderer* render)
{
	for (unsigned int x = 0; x < mapTiles.size(); x++)
	{
		//cout << "DRAWING!" << endl;
		
		SDL_RenderCopy(render, sheet, &tileBoxes[mapTiles[x].getType()], &mapTiles[x].getBox());
	}
}