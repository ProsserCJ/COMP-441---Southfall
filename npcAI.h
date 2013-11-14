#ifndef _NPC_AI_H
#define _NPC_AI_H
#define WIN32_LEAN_AND_MEAN

#include "npc.h"
#include "entity.h"

enum PRIORITY {IDLE, ATTACK};

const float SEARCHDELAY = 0.2;
const float MOVEMENTLENGTH = 1.0f;

class World;

class npcAI
{
public:
	npcAI() : priority(IDLE), npc(0) {initialize();}
	npcAI(NPC* E) : npc(E), priority(IDLE) {initialize();}

	void update(float frameTime, World* W);
	void initialize();
	
private:
	NPC* npc;	// The npc the ai controls
	Entity* target;
	PRIORITY priority;

	inline void act(float frameTime, World* W);

	inline void _idle(float frameTime, World* W);
	inline void _attack(float frameTime, World* W);

	float searchDelay;
	float delay;
};

#endif