#ifndef _NPC_AI_H
#define _NPC_AI_H
#define WIN32_LEAN_AND_MEAN

#include "npc.h"
#include "entity.h"
#include "ImageLibrary.h"

enum PRIORITY {IDLE, ATTACK};

const float SEARCHDELAY = 0.2;
const float MOVEMENTLENGTH = 1.0f;

const float WRAITH_SIGHT = 10.0f;

class World;

class npcAI
{
public:
	npcAI() : priority(IDLE), npc(0), imageLibrary(0) {initialize();}
	npcAI(Entity* E, ImageLibrary* IL) : npc(E), priority(IDLE), imageLibrary(IL) {initialize();}

	void update(float frameTime, World* W);
	void initialize();
	
	VECTOR2 getLastPosition()	{return npc->getLastPosition();}
	VECTOR2 getPosition()		{return npc->getPosition();}
	Entity* & getNPC()			{return npc;}
	bool isActive()				{return npc->isActive();}

private:
	Entity* npc;	// The npc the ai controls
	Entity* target;
	PRIORITY priority;

	ImageLibrary* imageLibrary;

	inline void act(float frameTime, World* W);

	inline void _idle(float frameTime, World* W);
	inline void _attack(float frameTime, World* W);

	float searchDelay;
	float delay;
};

#endif