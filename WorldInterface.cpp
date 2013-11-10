#include "WorldInterface.h"

void WorldInterface::initialize(Graphics* graphics)
{
	StructInt = new StructureInterface;
	StructInt->initialize(graphics);
	this->graphics = graphics;
	
	// Grass
	if(!GrassTX.initialize(graphics, GRASS1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Grass texture"));
	if(!GrassIM.initialize(graphics, 0, 0, 0, &GrassTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Grass image"));
	// Tree
	if(!TreeTX.initialize(graphics, TREE1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Tree texture"));
	if(!TreeIM.initialize(graphics, 0, 0, 0, &TreeTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Tree image"));
	// Boulder 1
	if(!Boulder1TX.initialize(graphics, BOULDER1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boulder texture"));
	if(!Boulder1IM.initialize(graphics, 0, 0, 0, &Boulder1TX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boulder image"));
	// Boulder 2
	if(!Boulder2TX.initialize(graphics, BOULDER2))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boulder2 texture"));
	if(!Boulder2IM.initialize(graphics, 0, 0, 0, &Boulder2TX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boulder2 image"));
	// Magic Portal
	if(!MagicPortalTX.initialize(graphics, MAGICPORTAL1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Magic portal texture"));
	if(!MagicPortalIM.initialize(graphics, 32, 32, 4, &MagicPortalTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Magic portal image"));
	// House
	if(!HouseTX.initialize(graphics, HOUSE1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing House texture"));
	if(!HouseIM.initialize(graphics, 0, 0, 0, &HouseTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing House image"));
	// River
	if(!RiverTX.initialize(graphics, RIVER1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing River texture"));
	if(!RiverIM.initialize(graphics, 0, 0, 0, &RiverTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing River image"));
	// Wood Tile
	if(!WoodTileTX.initialize(graphics, WOODTILE1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Wood Tile texture"));
	if(!WoodTileIM.initialize(graphics, 0, 0, 0, &WoodTileTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Wood Tile image"));

	// Temporary world constants
	
	/*int WORLD_WIDTH = 100;
	int WORLD_HEIGHT = 100;
	Current = new World(WORLD_WIDTH, WORLD_HEIGHT);
	initializeWorld();*/
	//Current = loadWorld("Worlds\\TestWorld.txt");
	Current = loadWorld("Worlds\\TSouthfallMap.txt");
}

World* WorldInterface::loadWorld(const string& fileName)
{
	ifstream fin(fileName);
	if(fin.fail())
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error loading world"));
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
			assignTile(W, c, x, y);
			x++;
			if(x>=width)
			{
				x = 0;
				y++;
			}
		}
		fin.get(c);
	}
	
	int npcCount;
	fin >> npcCount;
	for (int i=0; i<npcCount; i++)
	{
		int ID, x, y;
		fin >> ID >> x >> y;
		W->addNPC(new NPC(ID, VECTOR2(x,y)));
	}


	W->setInitialized(true);
	return W;
}

void WorldInterface::draw(VECTOR2& Center)
{
	if(Current != 0) Current->draw(Center);
}

void WorldInterface::initializeWorld()
{
	int width = Current->getWidth(), height = Current->getHeight();
	Current->getTile() = new Tile**[width];
	for(int x=0; x<width; x++)
	{
		Current->getTile(x) = new Tile*[height];
		for(int y=0; y<height; y++)
			Current->getTile(x,y) = new Tile(VECTOR2(x,y), &GrassIM);
	}
	Current->setInitialized(true);
}

inline void WorldInterface::assignTile(World* & W, char c, int x, int y)
{
	Tile* T;
	switch(c)
	{
		case 'g': // Grass
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &GrassIM);
			break;
		}
		case 't':	//Track (dirt or road)
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &WoodTileIM);
			break;
		}
		case 'w':	//wall
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &Boulder1IM, false);
			break;
		}
		case 'b': // Boulder
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &Boulder1IM, false);
			break;
		}
		case 'B': // Boulder 2
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &Boulder2IM, false);
			break;
		}
		case 'r': // River
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &RiverIM, false);
			break;
		}
		case 's': // Structure blocker
		{
			T = new Tile(VECTOR2(x,y), 0, false);
			if(0<x-1 && W->getTile(x-1,y)->hasStructure()) 
				T->giveStructure(W->getTile(x-1,y)->getStructure());
			else if(0<y-1 && W->getTile(x,y-1)->hasStructure()) 
				T->giveStructure(W->getTile(x,y-1)->getStructure());
			W->getTile(x,y) = T;
			break;
		}
		case 'D': // Door into a structure
		{
			T = new Tile(VECTOR2(x,y), 0, false);
			if(0<x-1 && W->getTile(x-1,y)->hasStructure()) 
			{
				T->giveStructure(W->getTile(x-1,y)->getStructure());
			}
			else if(0<y-1 && W->getTile(x,y-1)->hasStructure()) 
			{
				T->giveStructure(W->getTile(x,y-1)->getStructure());
			}
			if(y+1<W->getHeight()) 
				T->giveStructure(StructInt->createHouse(&W, VECTOR2(x,y+1))); // Create the inside of the house that the door leads to
			W->getTile(x,y) = T;
			break;
		}
		case 'H': // House corner
		{
			T = new Tile(VECTOR2(x,y), 0, false);
			House* H = new House(VECTOR2(x,y), HOUSE1WIDTH, HOUSE1HEIGHT, &HouseIM);
			T->giveStructure(H);	// Point the tile to the house
			W->addStructure(H);		// Give the house to the world
			W->getTile(x,y) = T;	// Give the tile to the world
			break;
		}
		case 'P':
		{
			T = new Tile(VECTOR2(x,y), &GrassIM, false); // For now
			W->getTile(x,y) = T;
			Portal* P = new Portal(VECTOR2(x,y),1,1,&MagicPortalIM,W,VECTOR2(12,10));
			W->addStructure(P);
			T->giveStructure(P);
			break;
		}
		case 'x':
		default: W->getTile(x,y) = new Tile(VECTOR2(x,y), 0, false);
	}
}