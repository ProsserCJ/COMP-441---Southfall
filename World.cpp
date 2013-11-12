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
	int width = 0.5*image->getWidth()*image->getScale();
	int height = 0.5*image->getHeight()*image->getScale();
	int X = diff.x + HSCREEN_WIDTH - width;
	int Y = diff.y + HSCREEN_HEIGHT - height;
	image->setScale(DEFAULT_SCALE);
	image->setX(X); image->setY(Y);
	image->setCurrentFrame(frame);
	image->draw();
	if(_drawStruct) S->draw(Center);
}

void Tile::interact(Entity* E)
{
	if(S != 0)
		S->interact(E);
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
	for(auto p = entities.begin(); p != entities.end(); p++)
		(*p)->draw(Center);
	for(auto p = effects.begin(); p != effects.end(); p++)
		(*p)->draw(Center);
}

bool World::canMoveHere(Object* E, VECTOR2& position)
{
	return !collidesWithTile(E, position) && !collidesWithNPC(E, position);	
}

bool World::collidesWithTile(Object* E, VECTOR2& position)
{
	float radius = E->getRadius();
	VECTOR2 topLeft, topRight, bottomLeft, bottomRight;
	topLeft = position + VECTOR2(0.5-radius,0.9-radius);
	topRight = position + VECTOR2(0.5+radius,0.9-radius);
	bottomLeft = position + VECTOR2(0.5-radius,0.7+radius);
	bottomRight = position + VECTOR2(0.5+radius,0.7+radius);
	if(	isTraversible(topLeft) && 
		isTraversible(topRight) &&
		isTraversible(bottomLeft) && 
		isTraversible(bottomRight))
	{
		return false;	
	}	
	return true;
}

bool World::collidesWithEffect(Object* E, VECTOR2& position)
{
	VECTOR2 temp = E->getPosition();
	E->setPosition(position);
	for(auto p = effects.begin(); p != effects.end(); p++)
	{
		if(HandleCollision(*p, E))
		{
			E->setPosition(temp);
			(*p)->effect(E);
			return true;
		}
	}
	E->setPosition(temp);
	return false;
}

bool World::collidesWithNPC(Object* E, VECTOR2& position)
{
	VECTOR2 temp = E->getPosition();
	E->setPosition(position);
	for(auto p = entities.begin(); p != entities.end(); p++)
	{
		if (*p == E) continue; // You can't collide with yourself
		if(HandleCollision(*p, E)) 
		{
			E->setPosition(temp);
			return true;
		}
	}
	E->setPosition(temp);
	return false;
}

bool World::isTraversible(VECTOR2 T)
{
	if(T.x < 0 || T.y < 0 || width-0.2 < T.x || height-0.2 < T.y)
		return false; // Off the world map
	return getTile((int)(T.x), (int)(T.y))->isTraversable();
}

void World::act()
{
	for(auto p = entities.begin(); p != entities.end(); p++)
		(*p)->act(this);
}

void World::update(float frameTime)
{
	// Update Structures
	for(auto s = structures.begin(); s != structures.end(); s++)
		(*s)->update(frameTime);
	// Update Entities
	auto p = entities.begin();
	while(p != entities.end())
	{
		auto q = p; q++;
		(*p)->update(frameTime, this);
		p=q;
	}
	// Update Effects
	auto e = effects.begin();
	while(e != effects.end())
	{
		auto q = e; q++;
		(*e)->update(frameTime, this);
		if((*e)->done())
		{
			safeDelete<Effect*>(*e);
			effects.erase(e);
		}
		e=q;
	}
}

Entity* World::getNPCFacing(VECTOR2 pos, DIR dir)
{
	switch(dir)
	{
	case UP: pos.y -= 1; break;
	case DOWN: pos.y += 1; break;
	case LEFT: pos.x -= 1; break;
	case RIGHT: pos.x += 1; break;
	case UP_LEFT: pos.y -= 1; pos.x -= 1; break;
	case UP_RIGHT: pos.y -= 1; pos.x += 1; break;
	case DOWN_RIGHT: pos.y += 1; pos.x += 1; break;
	case DOWN_LEFT: pos.y += 1; pos.x -= 1;  break; 
	};

	for(auto p = entities.begin(); p != entities.end(); p++)
	{
		VECTOR2 NPCposition = (*p)->getPosition();
		
		//if the position is within .5, it's close enough
		if (NPCposition.x > pos.x - .5 && 
			NPCposition.x < pos.x + .5 &&
			NPCposition.y > pos.y - .5 &&
			NPCposition.y < pos.y + .5)
			return (*p);
	}

	return 0;
}
	