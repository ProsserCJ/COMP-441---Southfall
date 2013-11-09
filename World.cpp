#include "World.h"

bool Tile::isTraversable()
{
	if(S == 0) return _traversable;
	return S->isPassable();
}

void Tile::draw(VECTOR2& Center)
{
	if(!image) return; // if the image is null
	VECTOR2 diff = position*TILE_SIZE - Center;
	int X = diff.x + HSCREEN_WIDTH - HTILE_SIZE;
	int Y = diff.y + HSCREEN_HEIGHT - HTILE_SIZE;
	image->setScale(DEFAULT_SCALE);
	image->setX(X); image->setY(Y);
	image->draw();
	if(_drawStruct) S->draw(Center);
}

void Tile::interact()
{
	if(S != 0)
		S->interact();
}

void World::draw(VECTOR2& Center)
{
	if(!_initialized) return;
	int x0 = max(0, (Center.x-HSCREEN_WIDTH)/TILE_SIZE), y0 = max(0, (Center.y-HSCREEN_HEIGHT)/TILE_SIZE);
	int x1 = min(width, (Center.x + SCREEN_WIDTH)/TILE_SIZE), y1 = min(height, (Center.y + SCREEN_HEIGHT)/TILE_SIZE);
	for(int x = x0; x < x1; x++)
		for(int y = y0; y < y1; y++)
			tiles[x][y]->draw(Center);
	for(auto p = structures.begin(); p != structures.end(); p++)
		(*p)->draw(Center);
	for(auto p = npcs.begin(); p != npcs.end(); p++)
		(*p)->draw(Center);
}

bool World::canMoveHere(VECTOR2 position, float radius)
{
	VECTOR2 topLeft, topRight, bottomLeft, bottomRight;
	topLeft = position + VECTOR2(0.5-radius,0.9-radius);
	topRight = position + VECTOR2(0.5+radius,0.9-radius);
	bottomLeft = position + VECTOR2(0.5-radius,0.7+radius);
	bottomRight = position + VECTOR2(0.5+radius,0.7+radius);
	if(isTraversible(topLeft) && isTraversible(topRight) &&
		isTraversible(bottomLeft) && isTraversible(bottomRight))
		return true;
	return false;
}

bool World::isTraversible(VECTOR2 T)
{
	if(T.x < 0 || T.y < 0 || width-0.2 < T.x || height-0.2 < T.y)
		return false;
	return getTile((int)(T.x), (int)(T.y))->isTraversable();
}

void World::act(){
	for(auto p = npcs.begin(); p != npcs.end(); p++)
		(*p)->act(this);
}

void World::update(float frameTime){
	for(auto p = npcs.begin(); p != npcs.end(); p++)
		(*p)->update(frameTime, this);
}
	