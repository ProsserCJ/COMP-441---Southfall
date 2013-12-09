/*************************************************************
WorldInterface header file, WorldInterface object loads worlds

Last Modified: 11/17/2013

*************************************************************/

#ifndef _WORLD_INTERFACE_H
#define _WORLD_INTERFACE_H

#include "StructureInterface.h"
#include "World.h"
#include <string>
#include <fstream>
using std::string;
using std::ifstream;

const int HOUSE1WIDTH = 8;
const int HOUSE1HEIGHT = 6;

class WorldInterface
{
public:
	WorldInterface(ImageLibrary* imageLibrary) 
		: imageLibrary(imageLibrary) {};
	void initialize(Graphics* graphics, Audio* audio);
	
	World* getCurrent()	{return Current;}
	World* getMain()	{return main;}
	World* getStart()	{return bar1;}

	World* loadWorld(const string& fileName, Audio* audio);

private:
	World* Current;	// What world is currently in focus	
	World* main; // The main game world
	World* bar1; //bar1 structure, to ease starting there
	void initializeWorld(); // Initialize a main world

	inline void assignTile(World* & W, char c, int x, int y, int type);

	//World** worlds;	// An array of template worlds

	ImageLibrary* imageLibrary;
	StructureInterface* StructInt;
};

#endif