#include "WorldInterface.h"
#include <typeinfo>

void WorldInterface::initialize(Graphics* graphics)
{
	StructInt = new StructureInterface(imageLibrary);
	Current = loadWorld(SOUTHFALLMAP);
}

World* WorldInterface::loadWorld(const string& fileName)
{
	ifstream fin(fileName);
	if(fin.fail())
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error loading world"));
	int width, height;
	fin>>width; fin>>height;
	World* W = new World(width, height, imageLibrary);
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
		NPC* temp = new NPC(ID, VECTOR2(x,y), &imageLibrary->Character1IM);
		string* text = new string[textLines];
		char buffer[500];
		fin.get();
		for (int i=0; i<textLines; i++){ 
			fin.getline(buffer,500);
			text[i] = buffer;
		}
		temp->setText(text, textLines);
		W->addEntity(temp, new PassiveAI(temp));
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
			Current->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->GrassIM);
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
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->GrassIM);
			break;
		}
		case 't':	//Track (dirt or road)
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->WoodTileIM);
			break;
		}
		case 'w':	//wall
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->Boulder1IM, false);
			break;
		}
		case 'f': // Tree
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->GrassIM, false);
			W->addObject(new Object(VECTOR2(x+0.5,y+0.5), 0, 0.25, &imageLibrary->TreeIM, CIRCLE, TREE_CRECT));
			break;
		}
		case 'b': // Boulder
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->Boulder1IM, false);
			break;
		}
		/*case 'B': // Boulder 2
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &Boulder2IM, false);
			break;
		}*/
		case 'r': // River
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->RiverIM, false);
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
			Bar1* H = new Bar1(VECTOR2(x,y), HOUSE1WIDTH, HOUSE1HEIGHT, &imageLibrary->HouseIM);
			T->giveStructure(H);	// Point the tile to the house
			W->addStructure(H);		// Give the house to the world
			W->getTile(x,y) = T;	// Give the tile to the world
			break;
		}
		case 'A': // bar 2 corner
		{
			T = new Tile(VECTOR2(x,y), 0, false);
			Bar2* H = new Bar2(VECTOR2(x,y), HOUSE1WIDTH, HOUSE1HEIGHT, &imageLibrary->HouseIM);
			T->giveStructure(H);	// Point the tile to the house
			W->addStructure(H);		// Give the house to the world
			W->getTile(x,y) = T;	// Give the tile to the world
			break;
		}
		case 'H': // House1 corner
		{
			T = new Tile(VECTOR2(x,y), 0, false);
			House1* H = new House1(VECTOR2(x,y), HOUSE1WIDTH, HOUSE1HEIGHT, &imageLibrary->HouseIM);
			T->giveStructure(H);	// Point the tile to the house
			W->addStructure(H);		// Give the house to the world
			W->getTile(x,y) = T;	// Give the tile to the world
			break;
		}
		case 'O': // House2 corner
		{
			T = new Tile(VECTOR2(x,y), 0, false);
			House2* H = new House2(VECTOR2(x,y), HOUSE1WIDTH, HOUSE1HEIGHT, &imageLibrary->HouseIM);
			T->giveStructure(H);	// Point the tile to the house
			W->addStructure(H);		// Give the house to the world
			W->getTile(x,y) = T;	// Give the tile to the world
			break;
		}
		case 'U': // House3 corner
		{
			T = new Tile(VECTOR2(x,y), 0, false);
			House3* H = new House3(VECTOR2(x,y), HOUSE1WIDTH, HOUSE1HEIGHT, &imageLibrary->HouseIM);
			T->giveStructure(H);	// Point the tile to the house
			W->addStructure(H);		// Give the house to the world
			W->getTile(x,y) = T;	// Give the tile to the world
			break;
		}
		case 'S': // House4 corner
		{
			T = new Tile(VECTOR2(x,y), 0, false);
			House4* H = new House4(VECTOR2(x,y), HOUSE1WIDTH, HOUSE1HEIGHT, &imageLibrary->HouseIM);
			T->giveStructure(H);	// Point the tile to the house
			W->addStructure(H);		// Give the house to the world
			W->getTile(x,y) = T;	// Give the tile to the world
			break;
		}
		case 'P': // Portal
		{
			T = new Tile(VECTOR2(x,y), &imageLibrary->GrassIM, false); // For now
			W->getTile(x,y) = T;
			Portal* P = new Portal(VECTOR2(x,y),1,1,&imageLibrary->MagicPortalIM,W,VECTOR2(12,10));
			W->addStructure(P);
			T->giveStructure(P);
			break;
		}
		case '_': // Horizontal Wall
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->HWallIM, false);
			break;
		}
		case '|': // Vertical Wall
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->VWallIM, false);
			break;
		}
		case '#': // Wall Corner
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->CWallIM, false);
			break;
		}
		case 'x':
		default: W->getTile(x,y) = new Tile(VECTOR2(x,y), 0, false);
	}
}