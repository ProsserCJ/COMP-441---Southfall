/****************************************************
World header file, contains the definitions of Tile
and World

Last modified: 11/4/2013

******************************************************/

#ifndef _WORLD_H
#define _WORLD_H

#include <list>
using std::list;

#include "image.h"
#include "Structure.h"
#include "Item.h"
#include "npc.h"
#include "Effects.h"

class Structure;	// Forward reference to Structure

class Tile
{
public:
	Tile(VECTOR2 position, Image* image, bool trav=true, int frame=0) 
		: position(position), image(image), _traversable(trav), 
		S(0), _drawStruct(false), frame(frame) {};
	~Tile() {};

	void draw(VECTOR2& Center);

	// Accessors
	bool isTraversable();
	bool hasStructure()			{return S != 0;}
	Structure* getStructure()	{return S;}

	// Mutators
	void giveStructure(Structure* S, bool draw=false)	{this->S = S;_drawStruct=draw;}
	void interact(Entity* E);	// Open a door on the tile or things like that

private:
	VECTOR2 position;	// Position of the tile in the world
	bool _traversable;	// True if entities can walk on it
	bool _drawStruct;	// True if the tile should draw the structure on it
	Structure* S;		// A building is sitting over this tile
	
	Image* image;		// Base image of the tile
	int frame;			// Frame to draw
};

class World
{
public:
	// Constructors and destructors
	World() : _initialized(false) {};
	World(int width, int height) 
		: width(width), height(height), _initialized(false) {};
	~World() {};

	void draw(VECTOR2& Center);
	void update(float frameTime);
	void act();

	// Accessors
	Tile* &		getTile(int x, int y)	{return tiles[x][y];}
	Tile** &	getTile(int x)			{return tiles[x];}
	Tile*** &	getTile()				{return tiles;}
	bool canMoveHere(Object *E, VECTOR2& position);
	bool collidesWithTile(Object* E, VECTOR2& position);
	bool collidesWithNPC(Object* E, VECTOR2& position);
	bool isTraversible(VECTOR2 T);	// Pass in the world coords, not tile coords

	int getWidth()	{return width;}
	int getHeight()	{return height;}
	bool isInitialized()	{return _initialized;}
	Entity* getNPCFacing(VECTOR2 pos, DIR dir);
	
	// Mutators
	void setInitialized(bool init)	{_initialized = init;}
	void addStructure(Structure* S)	{structures.push_back(S);}
	void addEntity(Entity* E)		{entities.push_back(E);}
	void removeEntity(Entity* E)	{entities.remove(E);}

private:
	int width, height;				// Dimensions of this world		
	bool _initialized;				// Has the world been initialized

	Tile*** tiles;					// The tiles that make up the world
	list<Structure*> structures;	// List of structures in the world
	list<Entity*> entities;			// List of NPCs in this world
	list<Item*> items;				// List of items in this world
	list<Effect*> effects;			// List of effects in the world
};

#endif