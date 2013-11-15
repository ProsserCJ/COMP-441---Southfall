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

void Tile::handleCollisions(Entity* E)
{
	for(auto obj = objects.begin(); obj != objects.end(); obj++)
	{
		if((*obj)->getType() == PROJECTILE)
		{
			Projectile* P = reinterpret_cast<Projectile*>(*obj);
			if(P->isActive() && E->getTeam() != P->getTeam() && HandleCollision(E, P))
				P->interact(E);
		}
	}
}

void Tile::drawObjects(VECTOR2& Center)
{
	if(objects.empty()) return;
	for(auto p = objects.begin(); p != objects.end(); p++)
	{
		int ymin = position.y;
		(*p)->draw(Center);
	}
}

void Tile::interact(Entity* E)
{
	if(S != 0) S->interact(E);
}

void Tile::add(Object* Obj)
{
	if(objects.empty())
	{
		objects.push_back(Obj);
		return;
	}
	auto p = objects.begin();
	int Y = Obj->getPosition().y;
	for(; p != objects.end(); p++)
		if((*p)->getPosition().y > Y)
			continue;

	objects.insert(p, Obj);
}

void World::draw(VECTOR2& Center, bool magicSight)
{
	if(!_initialized) return;
	int x0 = max(0, (Center.x-HSCREEN_WIDTH)/TILE_SIZE), y0 = max(0, (Center.y-HSCREEN_HEIGHT)/TILE_SIZE);
	int x1 = min(width, (Center.x + SCREEN_WIDTH)/TILE_SIZE), y1 = min(height, (Center.y + SCREEN_HEIGHT)/TILE_SIZE);

	// Structures
	for(auto p = structures.begin(); p != structures.end(); p++)
		(*p)->draw(Center);
	
	for(int x = x0; x < x1; x++)
		for(int y = y0; y < y1; y++)
			tiles[x][y]->draw(Center);
	for(int x = x0; x < x1; x++)
		for(int y = y0; y < y1; y++)
			tiles[x][y]->drawObjects(Center);
	for(auto ef = effects.begin(); ef != effects.end(); ef++)
		if(!(*ef)->isInvisible() && (magicSight || !(*ef)->isHidden())) 
			(*ef)->draw(Center);
}

void World::collisions()
{
	// For now, brute force algorithm
	for(auto p = projectiles.begin(); p != projectiles.end(); p++)
	{
		for(auto e = entities.begin(); e != entities.end(); e++)
			if((*e)->isActive() && (*p)->isActive() && (*p)->getTeam() != (*e)->getTeam() && HandleCollision(*e, *p))
			{
				(*e)->receiveDamage(*p);
			}
	}

	for(auto e = entities.begin(); e != entities.end(); e++)
	{
		if((*e)->isActive())
		{
			int LX = max(0, (int)(*e)->getPosition().x - 1);
			int UX = min(width, (int)(*e)->getPosition().x + 1);
			int LY = max(0, (int)(*e)->getPosition().y - 1);
			int UY = min(width, (int)(*e)->getPosition().y + 1);
			for(int i=LX; i<=LY; i++)
			{
				for(int j=LY; j<=LY; j++)
					tiles[i][j]->handleCollisions(*e);
			}
		}
	}
}

void World::addStructure(Structure* S)
{
	structures.push_back(S);
}

void  World::addEntity(Entity* E)		
{
	tiles[(int)E->getPosition().x][(int)E->getPosition().y]->add(E);
	entities.push_back(E);
}

void World::addNPC(NPC* npc)
{
	tiles[(int)npc->getPosition().x][(int)npc->getPosition().y]->add(npc);
	entities.push_back(npc);
	AIs.push_back(new npcAI(npc));
}

void World::addEffect(Effect* E)		
{
	effects.push_back(E);
}

void World::addProjectile(Projectile* P) 
{
	tiles[(int)P->getPosition().x][(int)P->getPosition().y]->add(P);
	projectiles.push_back(P);
}

void World::addObject(Object* Obj)
{
	tiles[(int)Obj->getPosition().x][(int)Obj->getPosition().y]->add(Obj);
	objects.push_back(Obj);
}

void World::removeEntity(Entity* E)	
{
	tiles[(int)E->getLastPosition().x][(int)E->getLastPosition().y]->remove(E);
	entities.remove(E);
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

void World::act() {}

void World::update(float frameTime)
{
	// Update Structures
	for(auto s = structures.begin(); s != structures.end(); s++)
		(*s)->update(frameTime);
	// Update Entities
	auto ai = AIs.begin();
	while(ai != AIs.end())
	{
		auto q = ai; q++;
		(*ai)->update(frameTime, this);
		ai=q;
	}
	// Update Effects
	auto ef = effects.begin();
	while(ef != effects.end())
	{
		auto q = ef; q++;
		(*ef)->update(frameTime, this);
		if((*ef)->done())
		{
			safeDelete<Effect*>(*ef);
			effects.erase(ef);
		}
		ef=q;
	}
	// Update Projectiles
	auto pr = projectiles.begin();
	while(pr != projectiles.end())
	{
		auto q = pr; q++;
		(*pr)->update(frameTime, this);
		if(!(*pr)->isActive())
		{
			projectiles.erase(pr);
		}
		pr=q;
	}
}

Entity* World::getNPCFacing(VECTOR2 pos, DIR dir)
{
	float delta = .8;
	switch(dir)
	{
	case UP: pos.y -= delta; break;
	case DOWN: pos.y += delta; break;
	case LEFT: pos.x -= delta; break;
	case RIGHT: pos.x += delta; break;
	case UP_LEFT: pos.y -= delta; pos.x -= delta; break;
	case UP_RIGHT: pos.y -= delta; pos.x += delta; break;
	case DOWN_RIGHT: pos.y += delta; pos.x += delta; break;
	case DOWN_LEFT: pos.y += delta; pos.x -= delta;  break; 
	};

	for(auto p = entities.begin(); p != entities.end(); p++)
	{
		VECTOR2 NPCposition = (*p)->getPosition();
		
		//if the position is within delta, it's close enough
		if (NPCposition.x > pos.x - delta && 
			NPCposition.x < pos.x + delta &&
			NPCposition.y > pos.y - delta &&
			NPCposition.y < pos.y + delta)
			return (*p);
	}

	return 0;
}
	