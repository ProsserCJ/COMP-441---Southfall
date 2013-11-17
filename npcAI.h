#ifndef _NPC_AI_H
#define _NPC_AI_H
#define WIN32_LEAN_AND_MEAN

#include "npc.h"
#include "entity.h"
#include "ImageLibrary.h"

enum PRIORITY {IDLE, ATTACK};

const float SEARCHDELAY = 0.2;
const float EVALUATEDELAY = 0.5;
const float MOVEMENTLENGTH = 1.0f;

const float WRAITH_SIGHT = 10.0f;

class World;

class npcAI
{
public:
	npcAI() : priority(IDLE), npc(0) {initialize();}
	npcAI(Entity* E) : npc(E), priority(IDLE) {initialize();}
	~npcAI() {};

	void update(float frameTime, World* W);
	void initialize();
	
	VECTOR2 getLastPosition()	{return npc->getLastPosition();}
	VECTOR2 getPosition()		{return npc->getPosition();}
	Entity* & getNPC()			{return npc;}
	bool isActive()				{return npc->isActive();}

protected:
	Entity* npc;	// The npc the ai controls
	Entity* target;
	PRIORITY priority;

	void act(float frameTime, World* W);

	virtual void _assessPriority(World* W) = 0;
	virtual void _idle(float frameTime, World* W);
	virtual void _attack(float frameTime, World* W) = 0;

	float searchDelay;
	float evaluateDelay;
	float delay;
};

class PassiveAI : public npcAI
{
public:
	PassiveAI(Entity* E) : npcAI(E) {};
	void update(float frameTime, World* W); 
protected:
	virtual void _assessPriority(World* W) {};
	virtual void _attack(float frameTime, World* W) {};
};

class WraithAI : public npcAI
{
public:
	WraithAI(Entity* E) : npcAI(E) {};
protected:
	virtual void _assessPriority(World* W) {};
	//virtual void _idle(float frameTime, World* W);
	virtual void _attack(float frameTime, World* W);
};

#endif