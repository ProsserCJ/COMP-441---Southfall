#include "World.h"

Tile* World::getTile(int x, int y)
{
	return tiles[x][y];
}