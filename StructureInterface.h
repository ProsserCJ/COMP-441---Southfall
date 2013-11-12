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
using std::string;
using std::ifstream;
using std::stringstream;

class World;

class StructureInterface
{
public:
	StructureInterface() {};
	World* loadStructure(string, World**, VECTOR2);
	void initialize(Graphics* graphics);

	Portal* createHouse(World** external, VECTOR2 vOut);

private:
	inline void assignTile(World* &, char, int, int, World**, VECTOR2);
	VECTOR2 entrance;

	// Images and Textures
	TextureManager WoodTileTX;
	Image WoodTileIM;
	TextureManager HouseWallTX;
	Image HouseWallIM;
	TextureManager HouseDoorTX;
	Image HouseDoorIM;
	TextureManager BedTX;
	Image BedIM;
	TextureManager BarCounterTX;
	Image BarCounterIM;
	TextureManager BarBack1TX;
	Image BarBack1IM;
	TextureManager BarBack2TX;
	Image BarBack2IM;
	TextureManager TableTX;
	Image TableIM;
	TextureManager RChairTX;
	Image RChairIM;
	TextureManager LChairTX;
	Image LChairIM;
	TextureManager HorizInHouseDoorTX;
	Image HorizInHouseDoorIM;
	TextureManager VertInHouseDoorTX;
	Image VertInHouseDoorIM;

	Graphics* graphics;
};

#endif