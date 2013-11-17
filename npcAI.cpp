#include "npcAI.h"

#include "World.h"

void npcAI::initialize()
{
	searchDelay = 0;
	delay = 0;
	target = 0;
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
	if(!target->isActive()) target = 0;
	npc->act(W);
	if(searchDelay > SEARCHDELAY)
	{
		searchDelay = 0;
		// Basic search for now
		list<Entity*> List = W->search(npc->getPosition(), WRAITH_SIGHT);
		if(!List.empty())
		{
			for(auto p = List.begin(); p != List.end(); p++)
			{
				if((*p)->getTeam() != npc->getTeam())
				{
					target = *p;
				}
			}
		}
	}
	switch(priority)
	{
	case IDLE:
		_attack(frameTime, W);
		//_idle(frameTime, W);
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
	if(target == 0) return;
	if(npc->canAction())
	{
		float sY = static_cast<float>(target->getPosition().y - npc->getPosition().y);
		float sX = static_cast<float>(target->getPosition().x - npc->getPosition().x);
		float orient = atan2(sY, sX);

		Projectile* P = new Projectile(npc->getPosition(), FIREBALLSPEED, FIREBALLRADIUS, 
			FIREBALLRANGE, orient, &npcAI::imageLibrary->ShadowballSheetIM, 10, 0.f, 1.0f, npc->getTeam());
		P->setFrames(FIREBALLSTART, FIREBALLEND);
		P->setFrameDelay(0.1);
		W->addProjectile(P);
		npc->resetAction();
	}
}