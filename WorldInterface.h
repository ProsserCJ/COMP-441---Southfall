/*************************************************************
WorldInterface header file, WorldInterface object controls what 
world we are in, gives us access to it, allows us to switch 
between worlds and save, load and process worlds.

Not sure if this is the best way to do this, 
but I put it in for now.

Last Modified: 11/4/2013

*************************************************************/

#ifndef _WORLD_INTERFACE_H
#define _WORLD_INTERFACE_H

#include "World.h"
#include <string>
#include <fstream>
using std::string;
using std::ifstream;

class WorldInterface
{
public:
	void update(float frameTime) {Current->update(frameTime);}
	void draw(VECTOR2& Center);
	void initialize(Graphics* graphics);
	World* getCurrent() {return Current;}

	World* loadWorld(const string& fileName);

private:
	World* Current;	// What world is currently in focus

	void initializeWorld(); // Initialize a main world

	inline void assignTile(World* & W, char c, int x, int y);

	//World** worlds;	// An array of template worlds

	// Images and Textures
	TextureManager GrassTX;
	Image GrassIM;
	TextureManager WaterTX;
	Image WaterIM;
	TextureManager BoulderTX;
	Image BoulderIM;

	TextureManager TreeTX;
	Image TreeIM;

	Graphics* graphics;

};

#endif