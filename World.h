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
	Tile(int x, int y, Image* image) : x(x), y(y), image(image), S(0) {};
	~Tile() {};

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

private:
	int width, height;	// Dimensions of this world
	Tile** tiles;		// The tiles that make up the world
};

#endif