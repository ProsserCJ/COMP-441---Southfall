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
#include "ImageLibrary.h"
using std::string;
using std::ifstream;

const int HOUSE1WIDTH = 8;
const int HOUSE1HEIGHT = 6;

class WorldInterface
{
public:
	WorldInterface(ImageLibrary* imageLibrary) 
		: imageLibrary(imageLibrary) {};
	void initialize(Graphics* graphics, Audio* audio, TextBox* tb);
	
	World* getCurrent()				{return Current;}
	World* getMain()				{return main;}
	World* getStart()				{return bar1;}
	World* getBar2()				{return bar2;}
	TextBox* getTextBox()			{return textbox;}
	ImageLibrary* getImageLibrary() {return imageLibrary;}

	World* loadWorld(const string& fileName, Audio* audio);

	Audio* getAudio()	{return audio;}

private:
	World* Current;	// What world is currently in focus	
	World* main; // The main game world
	World* bar1; //bar1 world, for later reference
	World* bar2; //bar2 world, for later reference
	void initializeWorld(); // Initialize a main world

	inline void assignTile(World* & W, char c, int x, int y, int type);

	//World** worlds;	// An array of template worlds

	ImageLibrary* imageLibrary;
	StructureInterface* StructInt;
	Audio* audio;
	TextBox* textbox;	
};

#endif