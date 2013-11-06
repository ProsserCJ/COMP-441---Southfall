#include "World.h"

void Tile::draw(VECTOR2& Center)
{
	VECTOR2 diff = position*TILE_SIZE - Center;
	int X = diff.x + HSCREEN_WIDTH - HTILE_SIZE;
	int Y = diff.y + HSCREEN_HEIGHT - HTILE_SIZE;
	image->setScale(DEFAULT_SCALE);
	image->setX(X); image->setY(Y);
	image->draw();
}

void World::draw(VECTOR2& Center)
{
	if(!_initialized) return;
	int x0 = max(0, (Center.x-HSCREEN_WIDTH)/TILE_SIZE), y0 = max(0, (Center.y-HSCREEN_HEIGHT)/TILE_SIZE);
	int x1 = min(width, (Center.x + SCREEN_WIDTH)/TILE_SIZE), y1 = min(height, (Center.y + SCREEN_HEIGHT)/TILE_SIZE);
	for(int x = x0; x < x1; x++)
		for(int y = y0; y < y1; y++)
			tiles[x][y]->draw(Center);
}

bool World::canMoveHere(VECTOR2 position, float radius)
{
	VECTOR2 topLeft, topRight, bottomLeft, bottomRight;
	topLeft = position + VECTOR2(-radius,-radius);
	topRight = position + VECTOR2(radius,-radius);
	bottomLeft = position + VECTOR2(-radius,radius);
	bottomRight = position + VECTOR2(radius,radius);
	if(isTraversible(topLeft) && isTraversible(topRight) &&
		isTraversible(bottomLeft) && isTraversible(bottomRight))
		return true;
	return false;
}

bool World::isTraversible(VECTOR2 T)
{
	return getTile(tileX(T.x), tileY(T.y))->isTraversable();
}