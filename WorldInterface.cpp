#include "WorldInterface.h"
#include <typeinfo>

void WorldInterface::initialize(Graphics* graphics, Audio* audio)
{
	StructInt = new StructureInterface(imageLibrary);
	main = loadWorld(SOUTHFALLMAP, audio);
	
	//add dead guys
	main->addObject(new Object(VECTOR2(109.5,61.5),0,0, &imageLibrary->DeadGuyIM, entityNS::POINTCOLLISION, HUMAN_CRECT));
	main->addObject(new Object(VECTOR2(110.5,61.5),0,0, &imageLibrary->DeadGuyIM, entityNS::POINTCOLLISION, HUMAN_CRECT));
	main->addObject(new Object(VECTOR2(111.5,61.5),0,0, &imageLibrary->DeadGuyIM, entityNS::POINTCOLLISION, HUMAN_CRECT));

	//move into bar 1 to start game
	Current = bar1;

}

World* WorldInterface::loadWorld(const string& fileName, Audio* audio)
{
	ifstream fin(fileName);
	if(fin.fail())
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error loading world"));
	int type, width, height;
	fin >> type; fin>>width; fin>>height;
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
			assignTile(W, c, x, y, type);
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
		int ID, textLines;
		float x, y;
		fin >> ID;
		if(ID == 1)
		{
			fin >> textLines >> x >> y;
			x += .5;y += .5;
			NPC* temp = new NPC(ID, VECTOR2(x,y), &imageLibrary->Character1IM, audio);
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
		else if(ID == 2)
		{
			fin >> x >> y;
			x += .5;y += .5;
			Entity* goblin = new Entity(VECTOR2(x,y), 0.3, GOBLIN_HEALTH, &imageLibrary->Goblin1IM, audio, 1, HUMAN_CRECT);
			goblin->setSpeed(3); goblin->setDeathSound(GOBLIN_DEATH);
			W->addEntity(goblin, new GoblinAI(goblin));
			W->addEnemy(goblin);
		}
		else if(ID == 3)
		{
			fin >> x >> y;
			x += .5;y += .5;
			Entity* wraith = new Entity(VECTOR2(x,y), 0.5, WRAITH_HEALTH, &imageLibrary->WraithIM, audio, 1, WRAITH_CRECT);
			
			wraith->setSpeed(5);
			W->addEntity(wraith, new WraithAI(wraith));
			W->addEnemy(wraith);
		}	
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

inline void WorldInterface::assignTile(World* & W, char c, int x, int y, int type)
{
	Tile* T;
	switch(c)
	{
		// Base tiles
		case 'g': // Default ground cover (Grass, sand, or cave floor by type)
		{
			if(type == 0) W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->GrassIM);
			else if(type == 1) W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->SandIM);
			else W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->CavefloorIM);
			break;
		}
		case 'f':	// Default Growth (Tree, cactus by type)
		{
			if(type == 0)
			{
				W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->GrassIM, false);
				W->addObject(new Object(VECTOR2(x+0.5,y+0.5), 0, 0.25, &imageLibrary->TreeIM, CIRCLE, TREE_CRECT));
			}
			else if(type == 1) 
			{
				W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->SandIM, false);
				W->addObject(new Object(VECTOR2(x+0.5,y+0.5), 0, 0.25, &imageLibrary->CactusIM, CIRCLE, TREE_CRECT));
			}
			else 
			{
				W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->CavefloorIM, false);
				// None yet, large mushroom?
			}
			break;
		}
		case 'G':	// Grass (Explicit)
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->GrassIM);
			break;
		}
		case 'q':	// Sand (Explicit)
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->SandIM);
			break;
		}
		case 'c':	// Rock surface (Explicit)
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->CavefloorIM);
			break;
		}
		case 't':	//Track (dirt or road)
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->WoodTileIM);
			break;
		}
		case 'F':	// Tree (Explicit)
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->GrassIM, false);
			W->addObject(new Object(VECTOR2(x+0.5,y+0.5), 0, 0.25, &imageLibrary->TreeIM, CIRCLE, TREE_CRECT));
			break;
		}
		case 'T':	// Cactus (Explicit)
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->SandIM, false);
			W->addObject(new Object(VECTOR2(x+0.5f,y+0.5f), 0, 0.25, &imageLibrary->CactusIM, CIRCLE, TREE_CRECT));
			break;
		}
		case 'b': // Boulder
		{
			if(type == 0) W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->GrassIM, false);
			else if(type == 1) W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->SandIM, false);
			else W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->CavefloorIM, false);

			W->addObject(new Object(VECTOR2(x+0.5f,y+0.95f), 0, 0.25, &imageLibrary->Boulder1IM, CIRCLE, BOULDER_CRECT));
			break;
		}
		case 'r':	// River
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->RiverIM, false);
			break;
		}
		// Structures
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
				{ 
					Structure* temp = StructInt->createBar1(&W, VECTOR2(x+0.5,y+1.5)); 
					T->giveStructure(temp);
					bar1 = temp->getWorld();
				}
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
		// Walls
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
		// Cave / Dungeon
		case 'C':	// Cave wall
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->CavewallIM, false);
			break;
		}
		case 'x':
		default: W->getTile(x,y) = new Tile(VECTOR2(x,y), 0, false);
	}
}