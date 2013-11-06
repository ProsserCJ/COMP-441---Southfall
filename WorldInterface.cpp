#include "WorldInterface.h"

void WorldInterface::initialize(Graphics* graphics)
{
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
	// Boulder
	if(!BoulderTX.initialize(graphics, BOULDER1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boulder texture"));
	if(!BoulderIM.initialize(graphics, 0, 0, 0, &BoulderTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boulder image"));

	// Temporary world constants
	int WORLD_WIDTH = 100;
	int WORLD_HEIGHT = 100;
	Current = new World(WORLD_WIDTH, WORLD_HEIGHT);
	//initializeWorld();
	Current = loadWorld("Worlds\\TestWorld.txt");
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
			/*switch(c)
			{
			case 'g':
				W->getTile(x,y) = new Tile(VECTOR2(x,y), &GrassIM);
				break;
			default:
				break;
			}*/
			//W->getTile(x,y) = new Tile(VECTOR2(x,y), &GrassIM);
			x++;
			if(x>=width)
			{
				x = 0;
				y++;
			}
		}
		fin.get(c);
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
	switch(c)
	{
	case 'g':
		W->getTile(x,y) = new Tile(VECTOR2(x,y), &GrassIM);
		break;
	case 'b':
		W->getTile(x,y) = new Tile(VECTOR2(x,y), &BoulderIM, false);
		break;
	}
}