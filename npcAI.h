#ifndef _NPC_AI_H
#define _NPC_AI_H
#define WIN32_LEAN_AND_MEAN

#include "npc.h"
#include "entity.h"
#include "ImageLibrary.h"
#include "Waypoint.h"
#include "MazeSolver.h"

enum PRIORITY {IDLE, SEARCH, TRACK, ATTACK, WAYPOINT};

const float SEARCHDELAY = 0.2;
const float EVALUATEDELAY = 0.5;
const float MOVEMENTLENGTH = 1.0f;

const float WRAITH_SIGHT = 14.0f;
const float PASSIVE_SIGHT = 6.0f;
const float GOBLIN_SIGHT = 7.5f;

class World;

class npcAI
{
public:
	npcAI() : priority(IDLE), npc(0) {initialize();}
	npcAI(Entity* E, float sight) : npc(E), priority(IDLE), sight(sight) {initialize();}
	~npcAI() {};

	void update(float frameTime, World* W);
	void initialize();
	
	// Accessors
	VECTOR2 getPosition()		{return npc->getPosition();}
	Entity* & getNPC()			{return npc;}
	bool isActive()				{return npc->isActive();}
	void setSight(float s)		{sight = s;}

protected:
	Entity* npc;	// The npc the ai controls
	Entity* target;
	PRIORITY priority;
	Waypoint* nextWaypoint;

	MazeSolver Solver;
	float sight;

	void act(float frameTime, World* W);

	virtual void _assessPriority(World* W) = 0;
	virtual void _idle(float frameTime, World* W);
	virtual void _attack(float frameTime, World* W) = 0;
	virtual void _search(float frameTime, World* W) = 0;
	virtual void _track(float frameTime, World* W, VECTOR2 track) = 0;
	virtual void _waypoint(float frameTime, World* W);	

	float searchDelay;
	float evaluateDelay;
	float delay;
};

class PassiveAI : public npcAI
{
public:
	PassiveAI(Entity* E) : npcAI(E, PASSIVE_SIGHT) {};
	void update(float frameTime, World* W); 
protected:
	virtual void _assessPriority(World* W) {};
	virtual void _attack(float frameTime, World* W) {};
	virtual void _search(float frameTime, World* W) {};
	virtual void _track(float frameTime, World* W, VECTOR2 track) {};
};

class StationaryAI : public npcAI
{
public:
	StationaryAI(Entity* E) : npcAI(E, PASSIVE_SIGHT) {};
	void update(float frameTime, World* W); 
protected:
	virtual void _assessPriority(World* W) {};
	virtual void _idle(float frameTime, World* W){npc->standing();}
	virtual void _attack(float frameTime, World* W) {};
	virtual void _search(float frameTime, World* W) {};
	virtual void _track(float frameTime, World* W, VECTOR2 track) {};
};

class GoblinAI : public npcAI
{
public:
	GoblinAI(Entity* E) : npcAI(E, GOBLIN_SIGHT){nextWaypoint = 0;}
protected:
	virtual void _assessPriority(World* W);
	virtual void _attack(float frameTime, World* W);
	virtual void _search(float frameTime, World* W);
	virtual void _track(float frameTime, World* W, VECTOR2 track);
};

class WaveAI : public npcAI
{
public:
	WaveAI(Entity* E) : npcAI(E, GOBLIN_SIGHT) {nextWaypoint = new Waypoint(113,101.5);}
protected:
	virtual void _idle(float frameTime, World* W);
	virtual void _assessPriority(World* W);
	virtual void _attack(float frameTime, World* W);
	virtual void _search(float frameTime, World* W);
	virtual void _track(float frameTime, World* W, VECTOR2 track);
};

class WraithAI : public npcAI
{
public:
	WraithAI(Entity* E) : npcAI(E, WRAITH_SIGHT) {nextWaypoint = 0;};
protected:
	virtual void _assessPriority(World* W);
	virtual void _attack(float frameTime, World* W);
	virtual void _search(float frameTime, World* W);
	virtual void _track(float frameTime, World* W, VECTOR2 track);
};


#endif