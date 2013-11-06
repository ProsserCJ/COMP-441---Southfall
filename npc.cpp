#include "npc.h"
#include "random.h"
using namespace npcNS;

Random rGen(0,999); //Homebrew Random number object
					//rgen.next() returns a random number from 0-99 inclusive
					//rgen.range(low, high) sets the range

void NPC::initialize(Image* image)
{
	this->image = image;	
	image->setFrameDelay(DEFAULT_FRAME_DELAY);
	image->setLoop(true);
};

void NPC::setStandingImage()
{
	switch(facing)
	{
		case UP: setStationaryFrame(NPC_FACING_UP); break;
		case DOWN: setStationaryFrame(NPC_FACING_DOWN); break;
		case LEFT: setStationaryFrame(NPC_FACING_LEFT); break;
		case RIGHT: setStationaryFrame(NPC_FACING_RIGHT); break;

	}
}

void NPC::update(float frameTime)
{
	updateImage(frameTime);
	velocity = ZERO;
	DIR dir = NONE;	
	
	if (distanceTraveled >= 1){
		standing();
		rGen.range(0,100);
		if (!moving && timeSinceLastMove > 2 && rGen.next() < 50){ //50% chance of initiating movement after 2 seconds
			timeSinceLastMove = 0;
			distanceTraveled = 0;
			rGen.range(0,3);		
			go(DIR(rGen.next()));	//returns an integer from 0-3
		}							//Corresponds to UP, DOWN, LEFT, RIGHT, in enum
	}
	
	else{ 
		move(frameTime);
		distanceTraveled += NPC_SPEED*frameTime;		
	}
	timeSinceLastMove += frameTime;
}

void NPC::move(float frameTime){

	switch(facing)
	{
	case UP:
		if(facing != lastDir || !moving) setFrames(NPC_WALKING_UP_START, NPC_WALKING_UP_END);
		velocity.y = -NPC_SPEED;
		break;

	case DOWN:
		if(facing != lastDir || !moving) setFrames(NPC_WALKING_DOWN_START, NPC_WALKING_DOWN_END);
		velocity.y = NPC_SPEED;
		break;

	case LEFT:
		if(facing != lastDir || !moving) setFrames(NPC_WALKING_LEFT_START, NPC_WALKING_LEFT_END);
		velocity.x = -NPC_SPEED;
		break;

	case RIGHT:
		if(facing != lastDir || !moving) setFrames(NPC_WALKING_RIGHT_START, NPC_WALKING_RIGHT_END);
		velocity.x = NPC_SPEED;
		break;	
	}

	lastDir = facing;
	moving = true;
	setPosition(position + velocity*frameTime);

}