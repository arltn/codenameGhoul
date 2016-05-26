#include "Map.h"
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
			mapTiles.emplace(mapTiles.begin(),Tile(holdWidth * TILE_WIDTH, holdHeight * TILE_HEIGHT, holdType));
			//cout << "Adding tile" << endl;
			//cout << "h: " << holdHeight << ", w: " << holdWidth << endl;
			if (holdWidth + 1 >= mapWidth) // Need the >= because we are starting at 0
			{
				holdWidth = 0;
				holdHeight++;
			}
			else
				holdWidth += 1;
		}
		
		//for (unsigned int x = 0; x < mapTiles.size(); x++)
		//{
			//cout << mapTiles[x] << endl;
		//}
	}
	file.close();
	
	sheet = NULL;

	tileBoxes[BLACK_TILE].x = 0;
	tileBoxes[BLACK_TILE].y = 0;
	tileBoxes[BLACK_TILE].h = TILE_HEIGHT;
	tileBoxes[BLACK_TILE].w = TILE_WIDTH;

	tileBoxes[RED_TILE].x = 64;
	tileBoxes[RED_TILE].y = 0;
	tileBoxes[RED_TILE].h = TILE_HEIGHT;
	tileBoxes[RED_TILE].w = TILE_WIDTH;

	tileBoxes[GREEN_TILE].x = 128;
	tileBoxes[GREEN_TILE].y = 0;
	tileBoxes[GREEN_TILE].h = TILE_HEIGHT;
	tileBoxes[GREEN_TILE].w = TILE_WIDTH;

	tileBoxes[BLUE_TILE].x = 192;
	tileBoxes[BLUE_TILE].y = 0;
	tileBoxes[BLUE_TILE].h = TILE_HEIGHT;
	tileBoxes[BLUE_TILE].w = TILE_WIDTH;
}

void Map::init(SDL_Renderer* render)
{
	SDL_Surface* hold;
	hold = IMG_Load("C:\\Users\\nja1121\\Documents\\codenameGhoul\\Assets\\test.png");

	if (!hold)
		cout << "Failed to load hold" << endl;

	sheet = SDL_CreateTextureFromSurface(render, hold);
}

void Map::draw(SDL_Renderer* render)
{
	for (unsigned int x = 0; x < mapTiles.size(); x++)
	{
		SDL_RenderCopy(render, sheet, &tileBoxes[mapTiles[x].getType()], &mapTiles[x].getBox());
	}
}