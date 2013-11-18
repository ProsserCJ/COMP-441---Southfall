/****************************************************
World header file, contains the definitions of Tile
and World

Last modified: 11/12/2013

******************************************************/

#ifndef _WORLD_H
#define _WORLD_H
#define WIN32_LEAN_AND_MEAN

#include <list>
using std::list;

#include "image.h"
#include "Structure.h"
#include "Item.h"
#include "npc.h"
#include "hero.h"
#include "entity.h"
#include "Effects.h"
#include "Projectiles.h"
#include "npcAI.h"

class Structure;	// Forward reference to Structure

class Tile
{
public:
	Tile(VECTOR2 position, Image* image, bool trav=true, int frame=0) 
		: position(position), image(image), _traversable(trav), 
		S(0), frame(frame) {};
	~Tile() {}

	void draw(VECTOR2& Center);
	void drawObjects(VECTOR2& Center);
	void updateObjects(float frameTime, World* W);
	void handleCollisions(Entity* E);

	// Accessors
	bool isTraversable();
	bool hasStructure()			{return S != 0;}
	Structure* getStructure()	{return S;}
	list<Object*>::iterator begin() {return objects.begin();}
	list<Object*>::iterator end()	{return objects.end();}
	VECTOR2 getPosition()		const {return position;}

	// Mutators
	void giveStructure(Structure* S)	{this->S = S;}
	void interact(Entity* E);	// Open a door on the tile or things like that
	void add(Object* Obj);
	void remove(Object* Obj);

private:
	VECTOR2 position;	// Position of the tile in the world
	bool _traversable;	// True if entities can walk on it
	Structure* S;		// A building is sitting over this tile
	
	Image* image;		// Base image of the tile
	int frame;			// Frame to draw

	// Testing
	list<Object*> objects;
};

class World
{
public:
	// Constructors and destructors
	World() : _initialized(false), imageLibrary(0) {};
	World(int width, int height, ImageLibrary* imageLibrary) 
		: width(width), height(height), _initialized(false), imageLibrary(imageLibrary) {};
	~World() {};

	void draw(VECTOR2& Center, bool magicSight);
	void update(VECTOR2& Center, float frameTime);
	void collisions();
	void act() {}
	bool winCondition();

	// Accessors
	Tile* &		getTile(int x, int y)	{return tiles[x][y];}
	Tile** &	getTile(int x)			{return tiles[x];}
	Tile*** &	getTile()				{return tiles;}
	bool canMoveHere(Object *E, VECTOR2& position);
	bool collidesWithTile(Object* E, VECTOR2& position);
	bool collidesWithNPC(Object* E, VECTOR2& position);
	bool collidesWithEffect(Object* E, VECTOR2& position);
	bool isTraversible(VECTOR2 T);	// Pass in the world coords, not tile coords
	ImageLibrary* getImageLibrary()	const {return imageLibrary;}
	int getWidth()					const {return width;}
	int getHeight()					const {return height;}
	bool isInitialized()			const {return _initialized;}
	Entity* getNPCFacing(VECTOR2 pos, DIR dir);
	list<Entity*> search(VECTOR2 Center, float sight);
	
	// Mutators
	void setInitialized(bool init)	{_initialized = init;}
	void addStructure(Structure* S);
	void addEntity(Entity* E);
	void addEntity(Entity* E, npcAI* AI);
	void addEffect(Effect* E);
	void addProjectile(Projectile* P);
	void addObject(Object* Obj);
	void removeEntity(Entity* E);
	void addEnemy(Entity* E)		{enemies.push_back(E);}

private:
	int width, height;				// Dimensions of this world		
	bool _initialized;				// Has the world been initialized

	ImageLibrary* imageLibrary;		// A pointer to the image library

	Tile*** tiles;					// The tiles that make up the world
	list<Structure*> structures;	// List of structures in the world
	list<Entity*> entities;			// List of NPCs in this world
	list<npcAI*> AIs;
	list<Object*> objects;			// List of objects (includes items) in this world
	list<Effect*> effects;			// List of effects in this world
	list<Projectile*> projectiles;	// List of projectiles in this world
	list<Entity*> enemies;			// List of active enemies
};

#endif