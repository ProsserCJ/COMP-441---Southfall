#include "WorldInterface.h"
#include <typeinfo>

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
	// Horizontal Wall
	if(!HWallTX.initialize(graphics, HWALL))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing HWall texture"));
	if(!HWallIM.initialize(graphics, 0, 0, 0, &HWallTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing HWall image"));
	// Vertical Wall
	if(!VWallTX.initialize(graphics, VWALL))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing VWall texture"));
	if(!VWallIM.initialize(graphics, 0, 0, 0, &VWallTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing VWall image"));
	// Wall Corner
	if(!CWallTX.initialize(graphics, CWALL))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing CWall texture"));
	if(!CWallIM.initialize(graphics, 0, 0, 0, &CWallTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing CWall image"));

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
	
	Current = loadWorld(SOUTHFALLMAP);
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
	
	// Read in NPCs
	int npcCount;
	fin >> npcCount;
	for (int i=0; i<npcCount; i++)
	{
		int ID, textLines, x, y;
		fin >> ID >> textLines >> x >> y;
		NPC* temp = new NPC(ID, VECTOR2(x,y));
		string* text = new string[textLines];
		char buffer[500];
		fin.get();
		for (int i=0; i<textLines; i++){ 
			fin.getline(buffer,500);
			text[i] = buffer;
		}
		temp->setText(text, textLines);
		W->addAIEntity(temp);
	}

	W->setInitialized(true);
	return W;
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
		case 'f': // Tree
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &GrassIM, false);
			W->addObject(new Object(VECTOR2(x+0.5,y+0.5), 0, 0.25, &TreeIM, CIRCLE));
			break;
		}
		case 'b': // Boulder
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &Boulder1IM, false);
			break;
		}
		/*case 'B': // Boulder 2
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &Boulder2IM, false);
			break;
		}*/
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
			{
				string l = typeid(*(T->getStructure())).name();
				if(l == "class House1") // Create the inside of the house that the door leads to
					T->giveStructure(StructInt->createHouse1(&W, VECTOR2(x+0.5,y+1.5))); 
				else if(l == "class House2") // Create the inside of the house that the door leads to
					T->giveStructure(StructInt->createHouse2(&W, VECTOR2(x+0.5,y+1.5))); 
				else if(l == "class House3") // Create the inside of the house that the door leads to
					T->giveStructure(StructInt->createHouse3(&W, VECTOR2(x+0.5,y+1.5))); 
				else if(l == "class House4") // Create the inside of the house that the door leads to
					T->giveStructure(StructInt->createHouse4(&W, VECTOR2(x+0.5,y+1.5))); 
				else if(l == "class Bar1") // Create the inside of the bar that the door leads to
					T->giveStructure(StructInt->createBar1(&W, VECTOR2(x+0.5,y+1.5))); 
				else if(l == "class Bar2") // Create the inside of the bar that the door leads to
					T->giveStructure(StructInt->createBar2(&W, VECTOR2(x+0.5,y+1.5)));
				
			}
			W->getTile(x,y) = T;
			break;
		}
		case 'B': // bar 1 corner
		{
			T = new Tile(VECTOR2(x,y), 0, false);
			Bar1* H = new Bar1(VECTOR2(x,y), HOUSE1WIDTH, HOUSE1HEIGHT, &HouseIM);
			T->giveStructure(H);	// Point the tile to the house
			W->addStructure(H);		// Give the house to the world
			W->getTile(x,y) = T;	// Give the tile to the world
			break;
		}
		case 'A': // bar 2 corner
		{
			T = new Tile(VECTOR2(x,y), 0, false);
			Bar2* H = new Bar2(VECTOR2(x,y), HOUSE1WIDTH, HOUSE1HEIGHT, &HouseIM);
			T->giveStructure(H);	// Point the tile to the house
			W->addStructure(H);		// Give the house to the world
			W->getTile(x,y) = T;	// Give the tile to the world
			break;
		}
		case 'H': // House1 corner
		{
			T = new Tile(VECTOR2(x,y), 0, false);
			House1* H = new House1(VECTOR2(x,y), HOUSE1WIDTH, HOUSE1HEIGHT, &HouseIM);
			T->giveStructure(H);	// Point the tile to the house
			W->addStructure(H);		// Give the house to the world
			W->getTile(x,y) = T;	// Give the tile to the world
			break;
		}
		case 'O': // House2 corner
		{
			T = new Tile(VECTOR2(x,y), 0, false);
			House2* H = new House2(VECTOR2(x,y), HOUSE1WIDTH, HOUSE1HEIGHT, &HouseIM);
			T->giveStructure(H);	// Point the tile to the house
			W->addStructure(H);		// Give the house to the world
			W->getTile(x,y) = T;	// Give the tile to the world
			break;
		}
		case 'U': // House3 corner
		{
			T = new Tile(VECTOR2(x,y), 0, false);
			House3* H = new House3(VECTOR2(x,y), HOUSE1WIDTH, HOUSE1HEIGHT, &HouseIM);
			T->giveStructure(H);	// Point the tile to the house
			W->addStructure(H);		// Give the house to the world
			W->getTile(x,y) = T;	// Give the tile to the world
			break;
		}
		case 'S': // House4 corner
		{
			T = new Tile(VECTOR2(x,y), 0, false);
			House4* H = new House4(VECTOR2(x,y), HOUSE1WIDTH, HOUSE1HEIGHT, &HouseIM);
			T->giveStructure(H);	// Point the tile to the house
			W->addStructure(H);		// Give the house to the world
			W->getTile(x,y) = T;	// Give the tile to the world
			break;
		}
		case 'P': // Portal
		{
			T = new Tile(VECTOR2(x,y), &GrassIM, false); // For now
			W->getTile(x,y) = T;
			Portal* P = new Portal(VECTOR2(x,y),1,1,&MagicPortalIM,W,VECTOR2(12,10));
			W->addStructure(P);
			T->giveStructure(P);
			break;
		}
		case '_': // Horizontal Wall
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &HWallIM, false);
			break;
		}
		case '|': // Vertical Wall
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &VWallIM, false);
			break;
		}
		case '#': // Wall Corner
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &CWallIM, false);
			break;
		}
		case 'x':
		default: W->getTile(x,y) = new Tile(VECTOR2(x,y), 0, false);
	}
}