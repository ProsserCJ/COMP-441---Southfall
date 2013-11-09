/*************************************************************
Structure Interface header

Last Modified: 11/8/2013

*************************************************************/

#ifndef _STRUCTURE_INTERFACE_H
#define _STRUCTURE_INTERFACE_H

#include "Structure.h"
#include <string>
using std::string;

class World;

class StructureInterface
{
public:
	Structure* loadStructure(string fileName, World* external);
	

private:
	inline void assignTile(World* & W, char c, int x, int y);

	// Images and Textures

	//vector<World*> connectingWorlds;

};

#endif