#include "StructureInterface.h"

void StructureInterface::initialize(Graphics* graphics)
{
	this->graphics = graphics;

	// Wood Floor 1
	if(!WoodTileTX.initialize(graphics, WOODTILE1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Wood Tile texture"));
	if(!WoodTileIM.initialize(graphics, 0, 0, 0, &WoodTileTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Wood Tile image"));
	// House Wall 1
	if(!HouseWallTX.initialize(graphics, HOUSEWALL1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing House Wall texture"));
	if(!HouseWallIM.initialize(graphics, 0, 0, 0, &HouseWallTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing House Wall image"));
	// House Door 1
	if(!HouseDoorTX.initialize(graphics, HOUSEDOOR1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing House Door texture"));
	if(!HouseDoorIM.initialize(graphics, 0, 0, 0, &HouseDoorTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing House Door image"));
	// Horizontal in-house Door 1
	if(!HorizInHouseDoorTX.initialize(graphics, HORIZINHOUSEDOOR1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Horizontal in House Door texture"));
	if(!HorizInHouseDoorIM.initialize(graphics, 32, 32, 2, &HorizInHouseDoorTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing House Door image"));
	// Vertical in-house Door 1
	if(!VertInHouseDoorTX.initialize(graphics, VERTINHOUSEDOOR1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Vertical in House Door texture"));
	if(!VertInHouseDoorIM.initialize(graphics, 32, 32, 2, &VertInHouseDoorTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Vertical in House Door image"));
	// Bed
	if(!BedTX.initialize(graphics, BED1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Bed texture"));
	if(!BedIM.initialize(graphics, 0, 0, 0, &BedTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Bed image"));
	
	// Bar Counter
	if(!BarCounterTX.initialize(graphics, BARCOUNTER))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Bar Counter texture"));
	if(!BarCounterIM.initialize(graphics, 0, 0, 0, &BarCounterTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Bar Counter image"));	
	// Bar Backdrop
	if(!BarBack1TX.initialize(graphics, BARBACKDROP))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Bar Backdrop 1 texture"));
	if(!BarBack1IM.initialize(graphics, 32, 32, 8, &BarBack1TX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Bar Backdrop 1 image"));	
	// Lower Bar Backdrop
	if(!BarBack2TX.initialize(graphics, LOWERBARBACK))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Lower Bar Backdrop texture"));
	if(!BarBack2IM.initialize(graphics, 0, 0, 0, &BarBack2TX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Lower Bar Backdrop image"));	
	// Table
	if(!TableTX.initialize(graphics, TABLE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing table texture"));
	if(!TableIM.initialize(graphics, 0, 0, 0, &TableTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing table image"));	
	// Right facing chair
	if(!RChairTX.initialize(graphics, RIGHTCHAIR))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing RChair texture"));
	if(!RChairIM.initialize(graphics, 0, 0, 0, &RChairTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing RChair image"));	
	// Right facing chair
	if(!LChairTX.initialize(graphics, LEFTCHAIR))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing LChair texture"));
	if(!LChairIM.initialize(graphics, 0, 0, 0, &LChairTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing LChair image"));	
	
}

World* StructureInterface::loadStructure(string fileName, World** external, VECTOR2 Vout)
{
	ifstream fin(fileName);
	if(fin.fail())
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error loading structure"));
	int width, height;
	fin>>width; fin>>height;
	World* W = new World(width, height);
	W->getTile() = new Tile**[width];
	for(int i=0; i<width; i++)
		W->getTile(i) = new Tile*[height];
	int x = 0, y = 0;
	char c;
	fin.get(c);
	while(!fin.eof()  && y < height)
	{
		if(!isspace(c))
		{
			assignTile(W, c, x, y, external, Vout);
			x++;
			if(x>=width)
			{
				x = 0;
				y++;
			}
		}
		fin.get(c);
	}
	// The npc code
	int npcCount;
	fin >> npcCount;
	for (int i=0; i<npcCount; i++)
	{
		int ID, x, y;
		fin >> ID >> x >> y;
		W->addEntity(new NPC(ID, VECTOR2(x,y)));
	}
	// End of npc code

	W->setInitialized(true);
	return W;
}

inline void StructureInterface::assignTile(World* & W, char c, int x, int y, World** external, VECTOR2 Vout)
{
	Tile* T;
	if(isdigit(c))
	{
		VECTOR2 V(x,y);
		int N = (int)c - (int)'0';
		T = new Tile(V, &HouseDoorIM, false);
		T->giveStructure(new Portal(V,1,1,&HouseDoorIM,external[N],Vout));
		W->getTile(x,y) = T;
		entrance = VECTOR2(x,y-1);
		return;
	}
	switch(c)
	{
		case 't': // Wood floor tile
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &WoodTileIM);
			break;
		}
		case '-': // Wooden wall
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &HouseWallIM, false);
			break;
		}
		case 'd': // Inside Horizontal door
		{
			T = new Tile(VECTOR2(x,y), &WoodTileIM, false);
			T->giveStructure(new Door(VECTOR2(x,y),1,1,&HorizInHouseDoorIM), true); 
			W->getTile(x,y) = T;
			break;
		}
		case '|': // Inside Vertical door
		{
			T = new Tile(VECTOR2(x,y), &WoodTileIM, false);
			T->giveStructure(new Door(VECTOR2(x,y),1,1,&VertInHouseDoorIM), true); 
			W->getTile(x,y) = T;
			break;
		}
		case 'b': // Bed (Horizontal)
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &BedIM, false);
			break;
		}
		case 'c': // Bar Counter - for now
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &BarCounterIM, false);
			break;
		}
		case '[': // Bar backdrop - for now
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &BarBack1IM, false, rand()%4);
			break;
		}
		case ']': // Lower Bar backdrop- for now
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &BarBack2IM);
			break;
		}
		case 'T': // Table
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &TableIM, false);
			break;
		}
		case 'r': // Right facing chair
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &RChairIM);
			break;
		}
		case 'l': // Left facing chair
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &LChairIM);
			break;
		}
		case 'x':
		default: W->getTile(x,y) = new Tile(VECTOR2(x,y), 0, false);
	}
}

Portal* StructureInterface::createHouse(World** external, VECTOR2 vOut)
{
	World* W = loadStructure(BARSTRUCTURE, external, vOut);
	return new Portal(vOut,1,1,0,W,entrance);
}