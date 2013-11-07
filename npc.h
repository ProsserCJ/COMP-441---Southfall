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
}

class NPC: public Entity
{
public:
	NPC() : Entity() {}
	NPC(Image* image, VECTOR2 pos)
		: Entity(pos, npcNS::RADIUS, npcNS::HP, image)
	{
		initialize(); 
		distanceTraveled = npcNS::PIXELS_PER_MOVE + 1;
		timeSinceLastMove = 0;	
	}
	~NPC() {}

	//inherited functions
	virtual void act(World* w);
	virtual void update(float frameTime, World* W);

	void initialize();

private:
	double distanceTraveled;
	double timeSinceLastMove;
};

#endif
