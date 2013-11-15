/***************************************************************
The header file for the Projectile class

Last Modified 11/12/2013

***************************************************************/

#ifndef _PROJECTILES_H
#define _PROJECTILES_H
#define WIN32_LEAN_AND_MEAN

#include "Entity.h"

class World;

const int FIREBALLSTART = 0;
const int FIREBALLEND = 3;
const float FIREBALLRANGE = 10.0f;
const float FIREBALLSPEED = 10.0f;
const float FIREBALLRADIUS = 0.2;

class Projectile : public Object
{
public:
	Projectile(VECTOR2 position, float speed, float radius, float range, float orient,
		Image* image, float freezeTime, int team=0) 
		: Object(position, speed, radius, image, CIRCLE, PROJECTILE), range(range), traveled(0), 
		orientation(orient), freezeTime(freezeTime), team(team)
	{velocity.x = cos(orientation); velocity.y = sin(orientation);};

	virtual void update(float frameTime, World* W);
	virtual void interact(World* W);
	virtual void interact(Entity* E) {}

	int getTeam()	{return team;}

private:
	int damage;	// How much damage the projectile does
	int team;	
	float orientation;
	float range;
	float traveled;

	float freezeTime;
};

#endif