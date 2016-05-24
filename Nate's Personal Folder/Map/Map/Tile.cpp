#include "Tile.h"


Tile::Tile(int x, int y, int type)
{
	cBox.x = x;
	cBox.y = y;
	cBox.h = TILE_HEIGHT;
	cBox.w = TILE_WIDTH;
	tileType = type;
}

ostream& operator << (ostream& out, Tile tile)
{
	out << "X Pos: " << tile.cBox.x << "\nY Pos: " << tile.cBox.y << "\n Type:" << tile.getType() << endl;
	return out;
};