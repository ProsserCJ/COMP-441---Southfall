#include "npcAI.h"

#include "World.h"

void npcAI::initialize()
{
	searchDelay = 0;
	evaluateDelay = 0;
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

void npcAI::act(float frameTime, World* W)
{
	if(npc == 0) return;
	if(target != 0 && !target->isActive()) target = 0;
	npc->act(W);
	if(evaluateDelay > EVALUATEDELAY)
	{
		evaluateDelay = 0;
		_assessPriority(W);
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

void npcAI::_idle(float frameTime, World* W)
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

void WraithAI::_attack(float frameTime, World* W)
{
	if(target == 0) return;
	if(npc->canAction())
	{
		float sY = static_cast<float>(target->getPosition().y - npc->getPosition().y);
		float sX = static_cast<float>(target->getPosition().x - npc->getPosition().x);
		float orient = atan2(sY, sX);

		Projectile* P = new Projectile(npc->getPosition(), FIREBALLSPEED, FIREBALLRADIUS, 
			FIREBALLRANGE, orient, &W->getImageLibrary()->ShadowballSheetIM, 10, 0.f, 1.0f, npc->getTeam());
		P->setFrames(FIREBALLSTART, FIREBALLEND);
		P->setFrameDelay(0.1);
		W->addProjectile(P);
		npc->resetAction();
	}
}