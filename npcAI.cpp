#include "npcAI.h"

#include "World.h"

void npcAI::initialize()
{
	searchDelay = 0;
	evaluateDelay = 0;
	delay = 0;
	target = 0;
	if(npc) npc->setController(this);
}

void npcAI::update(float frameTime, World* W)
{
	// Update times
	evaluateDelay += frameTime;
	searchDelay += frameTime;
	delay += frameTime;
	// Act and update
	act(frameTime, W);
}

void npcAI::act(float frameTime, World* W)
{
	if(npc == 0 || !npc->isActive()) return;
	if(target != 0 && !target->isActive()) target = 0;
	
	VECTOR2 track;
	if(target != 0)
	{
		track = target->getPosition() - npc->getPosition();
		if(D3DXVec2Length(&track) > sight) 
		{
			target = 0;
			priority = IDLE;
		}
	}
	if(priority == WAYPOINT)
	{
		if(nextWaypoint)
		{// If at the waypoint, go to the next waypoint
			VECTOR2 track = nextWaypoint->position - npc->getPosition();
			if(D3DXVec2Length(&track) < nextWaypoint->radius)
				nextWaypoint = nextWaypoint->next;
		}
		else priority = IDLE;
	}
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
	case TRACK:
		_track(frameTime, W, track);	
		break;
	case WAYPOINT:
		_waypoint(frameTime, W);
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

void npcAI::_waypoint(float frameTime, World* W)
{
	if(!nextWaypoint) return;
	VECTOR2 disp = nextWaypoint->position - npc->getPosition();
	if(abs(disp.x) < abs(disp.y))
	{
		if(disp.y > 0) npc->go(DOWN);
		else npc->go(UP);
	}
	else
	{
		if(disp.x > 0) npc->go(RIGHT);
		else npc->go(LEFT);
	}
}

void GoblinAI::_assessPriority(World* W)
{
	switch(priority)
	{
	case SEARCH:
		break;
	case ATTACK:
		break;
	case WAYPOINT:
		break;
	case IDLE:
		priority = SEARCH;
		break;
	default: break;

	}
}

void GoblinAI::_track(float frameTime, World* W, VECTOR2 track)
{
	if (target == 0 || !target->isActive() || npc == 0 || !npc->isActive()) return;
	npc->travel(Solver.solve(W, target->getPosition(), getPosition()));

/*
	DIR facing;
	float orient = atan2(track.y, track.x);
	if (orient > PI/4 && orient <= 3*PI/4) facing = DOWN;
	else if (orient <= -3*PI/4 || orient > 3*PI/4) facing = LEFT;
	else if (orient <= -PI/4 && orient > -3*PI/4) facing = UP;
	else if (orient > -PI/4 && orient <= PI/4) facing = RIGHT;
	npc->go(facing);*/
	
}

void GoblinAI::_attack(float frameTime, World* W)
{
	if(target == 0) 
	{
		priority = IDLE;
		return;
	}
	if(npc->canAction())
	{// Launch fireballs
		VECTOR2 launchPos = npc->getPosition() - VECTOR2(0.f,0.5f);
		float sY = static_cast<float>(target->getPosition().y - launchPos.y);
		float sX = static_cast<float>(target->getPosition().x - launchPos.x);
		float orient = atan2(sY, sX);
		if(orient < 0) orient += TPI;
		Projectile* P = new Projectile(launchPos, FIREBALLSPEED, FIREBALLRADIUS, 
			FIREBALLRANGE, orient, &W->getImageLibrary()->FireballSheetIM, FIREBALLDAMAGE, PROJ_FIREBALL, 0.f, 0.f, npc->getTeam());
		P->setFrames(FIREBALLSTART, FIREBALLEND);
		P->setFrameDelay(0.1);
		W->addProjectile(P);
		npc->resetAction();		
	}
}

void GoblinAI::_search(float frameTime, World* W)
{
	list<Entity*> Targets = W->search(npc->getPosition(), WRAITH_SIGHT);
	for(auto p = Targets.begin(); p != Targets.end(); p++)
		if((*p)->getType() != PROJECTILE && (*p)->getTeam() != npc->getTeam())
		{
			target = *p;
			priority = ATTACK;
		}
	_idle(frameTime, W);
}

void WraithAI::_assessPriority(World* W)
{
	switch(priority)
	{
	case SEARCH:
		break;
	case ATTACK:
		break;
	case WAYPOINT:
		break;
	case IDLE:
		priority = SEARCH;
	default: break;
	}
}

void WraithAI::_attack(float frameTime, World* W)
{
	if(target == 0) 
	{
		priority = IDLE;
		return;
	}
	if(npc->canAction())
	{// Launch shadowbolts
		VECTOR2 launchPos = npc->getPosition() - VECTOR2(0.f,1.8f);
		float sY = static_cast<float>(target->getPosition().y - launchPos.y);
		float sX = static_cast<float>(target->getPosition().x - launchPos.x);
		float orient = atan2(sY, sX);
		if(orient < 0) orient += TPI;
		Projectile* P = new Projectile(launchPos, FIREBALLSPEED, FIREBALLRADIUS, 
			FIREBALLRANGE, orient, &W->getImageLibrary()->ShadowballSheetIM, FIREBALLDAMAGE, PROJ_SHADOWBALL, 0.f, 1.0f, npc->getTeam());
		P->setFrames(FIREBALLSTART, FIREBALLEND);
		P->setFrameDelay(0.1);
		W->addProjectile(P);
		npc->resetAction();
	}
	if(delay > MOVEMENTLENGTH)
	{// Blink around
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

void WraithAI::_track(float frameTime, World* W, VECTOR2 track)
{
	if (target == 0) return;
	
	DIR facing;
	float orient = atan2(track.y, track.x);
	if (orient > PI/4 && orient <= 3*PI/4) facing = DOWN;
	else if (orient <= -3*PI/4 || orient > 3*PI/4) facing = LEFT;
	else if (orient <= -PI/4 && orient > -3*PI/4) facing = UP;
	else if (orient > -PI/4 && orient <= PI/4) facing = RIGHT;
	npc->go(facing);
	
}
