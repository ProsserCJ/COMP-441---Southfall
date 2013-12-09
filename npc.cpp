#include "npc.h"
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

Image* NPC::getImage(int ID)
{
	switch(ID)
	{
	case 1: return NPC_IM1; break;
	}
	return 0;
}

void NPC::updateText()
{
	for (auto it = conditionalLines.begin(); it != conditionalLines.end(); ++it)
		text.erase(text.begin() + (*it));

	conditionalLines.clear();
}