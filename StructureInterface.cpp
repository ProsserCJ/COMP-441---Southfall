#include "StructureInterface.h"

World* StructureInterface::loadStructure(string fileName, World** external, VECTOR2 Vout)
{
	ifstream fin(fileName);
	if(fin.fail())
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error loading structure"));
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
			NPC* temp = new NPC(ID, VECTOR2(x,y), &imageLibrary->Character1IM, 0);
			string* text = new string[textLines];
			char buffer[500];
			fin.get();
			for (int i=0; i<textLines; i++){ 
				fin.getline(buffer,500);
				text[i] = buffer;
				if(text[i] == "(sword acquired)")
					temp->item = "sword";
				else if(text[i] == "(learned fireball attack)")
					temp->item = "fireball";
			}
			temp->setText(text, textLines);
			W->addEntity(temp, new PassiveAI(temp));
		}
		else if(ID == 2)
		{
			fin >> x >> y;
			x += .5;y += .5;
			Entity* wraith = new Entity(VECTOR2(x,y), 0.5, 150, &imageLibrary->WraithIM, 0, 1, WRAITH_CRECT);
			W->addEntity(wraith, new WraithAI(wraith));
		}
		else if(ID == 3)
		{
			fin >> x >> y;
			x += .5;y += .5;
			Entity* goblin = new Entity(VECTOR2(x,y), 0.5, 150, &imageLibrary->WraithIM, 0, 1, WRAITH_CRECT);
			W->addEntity(goblin, new GoblinAI(goblin));
		}
	
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
		T = new Tile(V, &imageLibrary->HouseDoorIM, false);
		T->giveStructure(new Portal(V,1,1,&imageLibrary->HouseDoorIM,external[N],Vout));
		W->getTile(x,y) = T;
		entrance = VECTOR2(x,y-1);
		return;
	}
	switch(c)
	{
		case 't': // Wood floor tile
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->WoodTileIM);
			break;
		}
		case '-': // Wooden wall
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->HouseWallIM, false);
			break;
		}
		case 'd': // Inside Horizontal door
		{
			T = new Tile(VECTOR2(x,y), &imageLibrary->WoodTileIM, false);
			T->giveStructure(new Door(VECTOR2(x,y),1,1,&imageLibrary->HorizInHouseDoorIM)); 
			W->getTile(x,y) = T;
			break;
		}
		case '|': // Inside Vertical door
		{
			T = new Tile(VECTOR2(x,y), &imageLibrary->WoodTileIM, false);
			T->giveStructure(new Door(VECTOR2(x,y),1,1,&imageLibrary->VertInHouseDoorIM)); 
			W->getTile(x,y) = T;
			break;
		}
		case 'b': // Bed (Horizontal)
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->BedIM, false);
			break;
		}
		case 'c': // Bar Counter - for now
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->BarCounterIM, false);
			break;
		}
		case '[': // Bar backdrop - for now
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->BarBack1IM, false, rand()%4);
			break;
		}
		case ']': // Lower Bar backdrop- for now
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->BarBack2IM);
			break;
		}
		case 'T': // Table
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->TableIM, false);
			break;
		}
		case 'r': // Right facing chair
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->RChairIM);
			break;
		}
		case 'l': // Left facing chair
		{
			W->getTile(x,y) = new Tile(VECTOR2(x,y), &imageLibrary->LChairIM);
			break;
		}
		case 'x':
		default: W->getTile(x,y) = new Tile(VECTOR2(x,y), 0, false);
	}
}

Portal* StructureInterface::createBar1(World** external, VECTOR2 vOut)
{
	World* W = loadStructure(BAR1STRUCTURE, external, vOut);
	return new Portal(vOut,1,1,0,W,entrance);
}
Portal* StructureInterface::createBar2(World** external, VECTOR2 vOut)
{
	World* W = loadStructure(BAR2STRUCTURE, external, vOut);
	return new Portal(vOut,1,1,0,W,entrance);
}

Portal* StructureInterface::createHouse1(World** external, VECTOR2 vOut)
{
	World* W = loadStructure(HOUSE1STRUCTURE, external, vOut);
	return new Portal(vOut,1,1,0,W,entrance);
}
Portal* StructureInterface::createHouse2(World** external, VECTOR2 vOut)
{
	World* W = loadStructure(HOUSE2STRUCTURE, external, vOut);
	return new Portal(vOut,1,1,0,W,entrance);
}
Portal* StructureInterface::createHouse3(World** external, VECTOR2 vOut)
{
	World* W = loadStructure(HOUSE3STRUCTURE, external, vOut);
	return new Portal(vOut,1,1,0,W,entrance);
}
Portal* StructureInterface::createHouse4(World** external, VECTOR2 vOut)
{
	World* W = loadStructure(HOUSE4STRUCTURE, external, vOut);
	return new Portal(vOut,1,1,0,W,entrance);
}