#ifndef _HOSTILE_AI_H
#define _HOSTILE_AI_H
#define WIN32_LEAN_AND_MEAN

#include "npc.h"

enum PRIORITY {IDLE, ATTACK};

class HostileAI
{
public:
	HostileAI() : priority(IDLE), npc(0) {};
	void AI();
private:
	NPC* npc;	// The npc the ai controls
	Entity* target;
	PRIORITY priority;
};

#endif