#include "npcAI.h"

#include "World.h"

void npcAI::initialize()
{
	searchDelay = 0;
	delay = 0;
}

void npcAI::update(float frameTime, World* W)
{
	// Update times
	searchDelay += frameTime;
	delay += frameTime;
	// Act and update
	act(frameTime, W);
	npc->update(frameTime, W);
}

inline void npcAI::act(float frameTime, World* W)
{
	if(npc == 0) return;
	npc->act(W);
	if(searchDelay > SEARCHDELAY)
	{
		searchDelay = 0;
		// Look for a target
	}
	switch(priority)
	{
	case IDLE:
		_idle(frameTime, W);
		break;
	case ATTACK:
		_attack(frameTime, W);
		break;
	}

}

inline void npcAI::_idle(float frameTime, World* W)
{
	bool moving = false;
	if(delay > MOVEMENTLENGTH && rand()%100 == 0)
	{
		delay = 0;
		npc->standing();
		moving = false;
	}
	if(moving) npc->move(frameTime, W);
	else if(rand()%1000 == 0)
	{
		npc->go(entityNS::DIR(rand()%4));
		moving = true;
	}
	
}

inline void npcAI::_attack(float frameTime, World* W)
{

}