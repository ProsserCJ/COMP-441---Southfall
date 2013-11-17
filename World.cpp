#include "World.h"

bool Tile::isTraversable()
{
	if(S == 0) return _traversable;
	return S->isPassable();
}

void Tile::draw(VECTOR2& Center)
{
	if(!image) return; // if the image is null
	VECTOR2 diff = (position - Center)*TILE_SIZE;
	int X = diff.x + HSCREEN_WIDTH;
	int Y = diff.y + HSCREEN_HEIGHT;
	image->setScale(DEFAULT_SCALE);
	image->setX(X); image->setY(Y);
	image->setCurrentFrame(frame);
	image->draw();
}

void Tile::handleCollisions(Entity* E)
{
	for(auto obj = objects.begin(); obj != objects.end(); obj++)
		if((*obj)->getType() == PROJECTILE && (*obj)->isActive())
		{
			Projectile* P = reinterpret_cast<Projectile*>(*obj);
			if(E->getTeam() != P->getTeam() && ProjectileCollision(P, E))
				P->interact(E);
		}
}

void Tile::drawObjects(VECTOR2& Center)
{
	if(objects.empty()) return;
	list<Object*> temp = objects;
	while(!temp.empty())
	{
		Object* Obj = 0;
		float max = INT_MAX;
		for(auto p = temp.begin(); p != temp.end(); p++)
			if((*p)->getPosition().y <= max)
			{
				max = (*p)->getPosition().y;
				Obj = *p;
			}
		Obj->draw(Center);
		temp.remove(Obj);
	}
}

void Tile::updateObjects(float frameTime, World* W)
{
	for(auto p = objects.begin(); p != objects.end(); p++)
	{
		(*p)->update(frameTime, W);
	}
}

void Tile::interact(Entity* E)
{
	if(S != 0) S->interact(E);
}

void Tile::add(Object* Obj)
{
	objects.push_back(Obj);
}

void World::draw(VECTOR2& Center, bool magicSight)
{
	if(!_initialized) return;
	int x0 = max(0, Center.x-HSCREEN_WIDTH/TILE_SIZE-1), y0 = max(0, Center.y-HSCREEN_HEIGHT/TILE_SIZE-1);
	int x1 = min(width, Center.x + SCREEN_WIDTH/TILE_SIZE), y1 = min(height, Center.y + SCREEN_HEIGHT/TILE_SIZE);

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
	for(auto e = entities.begin(); e != entities.end(); e++)
	{
		auto p = projectiles.begin();
		//Projectile* P;
		list<Projectile*>::iterator q;
		while(p != projectiles.end())
		{
			q = p;
			q++;
			if((*e)->isActive() && (*p)->isActive() && (*p)->getTeam() != (*e)->getTeam() && ProjectileCollision(*p, *e))
			{
				(*e)->receiveDamage(*p);
				(*p)->deactivate();
			}
			/*if(!(*p)->isActive())
			{
				P = *p;
				projectiles.erase(p);
				tiles[P->LTileX()][P->LTileY()]->remove(P);
				safeDelete<Projectile*>(P);
			}*/
			p = q;
		}
	}
}

void World::addStructure(Structure* S)
{
	structures.push_back(S);
}

void World::addEntity(Entity* E)
{
	tiles[(int)E->getPosition().x][(int)E->getPosition().y]->add(E);
	entities.push_back(E);
}

void World::addEntity(Entity* E, npcAI* AI)		
{
	// Assumes AI already is connected to E
	tiles[(int)E->getPosition().x][(int)E->getPosition().y]->add(E);
	entities.push_back(E);
	AIs.push_back(AI);
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
	VECTOR2 top, right, bottom, left;
	top = position + VECTOR2(0,radius);
	right = position + VECTOR2(radius,0);
	bottom = position + VECTOR2(0,-radius);
	left = position + VECTOR2(-radius,0);
	if(	isTraversible(top) && 
		isTraversible(right) &&
		isTraversible(bottom) && 
		isTraversible(left))
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

void World::update(VECTOR2& Center, float frameTime)
{
	// Update Structures
	for(auto s = structures.begin(); s != structures.end(); s++)
		(*s)->update(frameTime);
	// Update Entities
	int x0 = max(0, Center.x-HSCREEN_WIDTH/TILE_SIZE-1), y0 = max(0, Center.y-HSCREEN_HEIGHT/TILE_SIZE-1);
	int x1 = min(width, Center.x + SCREEN_WIDTH/TILE_SIZE), y1 = min(height, Center.y + SCREEN_HEIGHT/TILE_SIZE);

	// Structures
	for(auto p = structures.begin(); p != structures.end(); p++)
		(*p)->draw(Center);
	
	for(int x = x0; x < x1; x++)
		for(int y = y0; y < y1; y++)
			tiles[x][y]->updateObjects(frameTime, this);

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
	VECTOR2 pos0 = pos;
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
	delta -= .01;
	Entity* closest = NULL;
	float closestDist2 = 0;

	for(auto p = entities.begin(); p != entities.end(); p++)
	{
		VECTOR2 NPCposition = (*p)->getPosition();
		
		//if the position is within delta, it's close enough
		if (NPCposition.x > pos.x - delta && 
			NPCposition.x < pos.x + delta &&
			NPCposition.y > pos.y - delta &&
			NPCposition.y < pos.y + delta &&
			closestDist2 < (NPCposition - pos).x*(NPCposition - pos).x + (NPCposition - pos).y*(NPCposition - pos).y)
		{
			closestDist2 = (NPCposition - pos).x*(NPCposition - pos).x + (NPCposition - pos).y*(NPCposition - pos).y;
			closest = *p;
		}
	}
	return closest;
}
	
list<Entity*> World::search(VECTOR2 Center, float sight)
{
	int x0 = max(0, Center.x-sight), y0 = max(0, Center.y-sight);
	int x1 = min(width, Center.x + sight), y1 = min(height, Center.y +sight);
	float sightsqr = sight*sight;
	list<Entity*> temp;
	for(int x = x0; x < x1; x++)
	{
		for(int y = y0; y < y1; y++)
		{
			for(auto p = tiles[x][y]->begin(); p != tiles[x][y]->end(); p++)
			{
				if((*p)->getType() != OBJECT)
				{
					Entity* E = reinterpret_cast<Entity*>(*p);
					const VECTOR2 V = Center - E->getPosition();
					if(D3DXVec2Length(&V) < sightsqr)
					{
						temp.push_back(E);
					}
				}
			}
		}
	}
	return temp;
}