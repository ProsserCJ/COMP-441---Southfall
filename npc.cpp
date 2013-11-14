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
};

void NPC::act(World* W)
{
	velocity = ZERO;
	DIR dir = NONE;
	if (distanceTraveled >= 1)
	{
		standing();
		rGen.range(0,1000);
		if (!moving && timeSinceLastMove > 2 && rGen.next() == 1)
		{ //0.1% chance per frame of initiating movement after 2 seconds
			timeSinceLastMove = 0;
			distanceTraveled = 0;
			rGen.range(0,3);		
			go(DIR(rGen.next()));	//returns an integer from 0-3
		}							//Corresponds to UP, DOWN, LEFT, RIGHT, in enum
	}
	else go(facing);
}

void NPC::update(float frameTime, World* W)
{
	if (paused) return;
	if(startMoving) distanceTraveled += NPC_SPEED*frameTime;
	timeSinceLastMove += frameTime;
	Entity::update(frameTime, W);
}

Image* NPC::getImage(int ID){

	switch(ID){
	case 1: return NPC_IM1; break;
	}
	return 0;
}