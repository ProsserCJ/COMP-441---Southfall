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
	Tile(VECTOR2 position, Image* image) : position(position), image(image), S(0) {};
	~Tile() {};

	// Accessors
	bool isTraversable() {return _traversable;}
	bool hasStructure() {return S != 0;}
	Entity* getEntity(){return 0;}; //returns a pointer to an entity is there is one on the tile (else 0)

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

	Tile* getTile(VECTOR2 pos);

private:
	int width, height;	// Dimensions of this world
	Tile** tiles;		// The tiles that make up the world
						//Is this a double array of type Tile or a single array of type Tile* ?
};

#endif