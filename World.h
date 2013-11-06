/****************************************************
World header file, contains the definitions of Tile
and World

Last modified: 11/4/2013

******************************************************/

#ifndef _WORLD_H
#define _WORLD_H

#include "image.h"

class Structure;	// Forward reference to Structure

class Tile
{
public:
	Tile(VECTOR2 position, Image* image, bool trav=true) 
		: position(position), image(image), _traversable(trav), S(0) {};
	~Tile() {};

	void draw(VECTOR2& Center);

	// Accessors
	bool isTraversable() {return _traversable;}
	bool hasStructure() {return S != 0;}

	// Mutators
	void giveStructure(Structure* S) {this->S = S;}

private:
	VECTOR2 position;	// Position of the tile in the world
	bool _traversable;	// True if entities can walk on it
	Structure* S;		// A building is sitting over this tile
	
	Image* image;		// Base image of the tile
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
	void update(float frameTime) {};

	// Accessors
	Tile* &		getTile(int x, int y)	{return tiles[x][y];}
	Tile** &	getTile(int x)			{return tiles[x];}
	Tile*** &	getTile()				{return tiles;}

	int getWidth()	{return width;}
	int getHeight()	{return height;}
	bool isInitialized()	{return _initialized;}
	
	// Mutators
	void setInitialized(bool init)	{_initialized = init;}

private:
	int width, height;	// Dimensions of this world
	Tile*** tiles;		// The tiles that make up the world
						
	bool _initialized;
};

#endif