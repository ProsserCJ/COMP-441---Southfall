#include "npc.h"
#include <fstream>
using std::ifstream;
using namespace npcNS;

//initialize static NPC images and textures;
TextureManager* NPC::NPC_TX1 = new TextureManager();
Image* NPC::NPC_IM1 = new Image();

//called once to initialize all graphics
void NPC::initGraphics(Graphics* graphics)
{
	if(!NPC_TX1->initialize(graphics, CHARACTER1_SHEET))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing NPC1 texture"));
	if(!NPC_IM1->initialize(graphics, 32, 32, 8, NPC_TX1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing NPC1 image"));
}

void NPC::initialize()
{	
	setFrameDelay(DEFAULT_FRAME_DELAY);
	speed = NPC_SPEED;
	distanceTraveled = npcNS::PIXELS_PER_MOVE + 1;
	timeSinceLastMove = 0;
	paused = false;
	item = "";
};

void NPC::update(float frameTime, World* W)
{
	if (paused) return;
	Entity::update(frameTime, W);
}


void NPC::updateText()
{
	for (auto it = conditionalLines.begin(); it != conditionalLines.end(); ++it)
		text.erase(text.begin() + (*it));

	conditionalLines.clear();
}

void Birmingham::initialize()
{
	ifstream fin(BIRM_TEXT);
	while (!fin.eof())
	{
		vector<string> line(1);
		char temp[500];
		fin.getline(temp,500);
		line[0] = temp;
		texts.push_back(line);
	}
	it = texts.begin();
}

vector<string> Birmingham::getText()
{
	auto ret = *(it); it++;	
	if (it == texts.end()) it = texts.begin();
	return ret;
}