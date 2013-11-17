/*************************************************************
Structure Interface header, Structure Interface loads and creates
structures.

Note: For now only supports one door to the outside

Last Modified: 11/8/2013

*************************************************************/

#ifndef _STRUCTURE_INTERFACE_H
#define _STRUCTURE_INTERFACE_H

#include "World.h"
#include <string>
#include <fstream>
#include <sstream>
#include "ImageLibrary.h"
using std::string;
using std::ifstream;
using std::stringstream;

class World;

class StructureInterface
{
public:
	StructureInterface(ImageLibrary* imageLibrary) 
		: imageLibrary(imageLibrary) {};
	World* loadStructure(string, World**, VECTOR2);

	Portal* createHouse1(World** external, VECTOR2 vOut);
	Portal* createHouse2(World** external, VECTOR2 vOut);
	Portal* createHouse3(World** external, VECTOR2 vOut);
	Portal* createHouse4(World** external, VECTOR2 vOut);
	Portal* createBar1(World** external, VECTOR2 vOut);
	Portal* createBar2(World** external, VECTOR2 vOut);

private:
	inline void assignTile(World* &, char, int, int, World**, VECTOR2);
	VECTOR2 entrance;
	ImageLibrary* imageLibrary;
	Graphics* graphics;
};

#endif

