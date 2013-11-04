#include "World.h"

Tile* World::getTile(VECTOR2 pos){
	//Should calculate the indexes of the absolute position.  Is this correct?
	int i = pos.x/TILE_SIZE;
	int j = pos.y/TILE_SIZE;
	
	return &tiles[i][j];
}