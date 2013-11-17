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
	evaluateDelay += frameTime;
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
	case SEARCH:
		_search(frameTime, W);
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

void WraithAI::_assessPriority(World* W)
{
	if(priority != ATTACK) priority = SEARCH;
}

void WraithAI::_attack(float frameTime, World* W)
{
	if(target == 0) 
	{
		priority = IDLE;
		return;
	}
	if(npc->canAction())
	{
		VECTOR2 launchPos = npc->getPosition() - VECTOR2(0.f,1.8f);
		float sY = static_cast<float>(target->getPosition().y - launchPos.y);
		float sX = static_cast<float>(target->getPosition().x - launchPos.x);
		float orient = atan2(sY, sX);
		if(orient < 0) orient += TPI;
		Projectile* P = new Projectile(launchPos, FIREBALLSPEED, FIREBALLRADIUS, 
			FIREBALLRANGE, orient, &W->getImageLibrary()->ShadowballSheetIM, 10, 0.f, 1.0f, npc->getTeam());
		P->setFrames(FIREBALLSTART, FIREBALLEND);
		P->setFrameDelay(0.1);
		W->addProjectile(P);
		npc->resetAction();
	}
	if(delay > MOVEMENTLENGTH)
	{
		VECTOR2 blink = npc->getPosition() + VECTOR2(rand()%2000/500.f - 2, rand()%2000/500.f - 2);
		if(rand()%100 == 0 && W->canMoveHere(npc, blink))
		{
			npc->setPosition(blink);
			delay = 0;
		}
	}
}

void WraithAI::_search(float frameTime, World* W)
{
	list<Entity*> Targets = W->search(npc->getPosition(), WRAITH_SIGHT);
	for(auto p = Targets.begin(); p != Targets.end(); p++)
		if((*p)->getType() != PROJECTILE && (*p)->getTeam() != npc->getTeam())
		{
			target = *p;
			priority = ATTACK;
		}
}