/***************************************************************
The header file for NPC classes

Last Modified 11/2/2013

***************************************************************/
#ifndef _NPC_H
#define _NPC_H

#include "entity.h"

namespace npcNS{
	//assign constants here
	const float NPC_SPEED = 2.f; //arbitrarily chosen to be slower than Hero
	const int RADIUS = 0.25;
	const int HP = 100;
	const int PIXELS_PER_MOVE = TILE_SIZE;

	//assign frame numbers here
	/*enum {
		NPC_FACING_UP = 12, 
		NPC_FACING_DOWN = 0,  
		NPC_FACING_LEFT = 4,  
		NPC_FACING_RIGHT = 8,

		NPC_WALKING_UP_START = 12,
		NPC_WALKING_UP_END = 15,
		NPC_WALKING_DOWN_START = 0,
		NPC_WALKING_DOWN_END = 3,
		NPC_WALKING_LEFT_START = 4,
		NPC_WALKING_LEFT_END = 7,
		NPC_WALKING_RIGHT_START = 8,
		NPC_WALKING_RIGHT_END = 11,
	};*/
}

class NPC: public Entity
{
public:
	NPC() : Entity() {}
	NPC(Image* image, VECTOR2 pos)
		: Entity(pos, npcNS::RADIUS, npcNS::HP, image)
	{
		initialize(image); 
		distanceTraveled = npcNS::PIXELS_PER_MOVE + 1;
		timeSinceLastMove = 0;	
	}
	~NPC() {}

	//inherited functions
	virtual void act(World* w);
	virtual void update(float frameTime, World* W);

	void initialize(Image* image);

private:
	double distanceTraveled;
	double timeSinceLastMove;
};

#endif
