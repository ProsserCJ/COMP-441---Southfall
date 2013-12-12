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
const int FIREEXPLOSIONDAMAGE = 3;
const float FIREBALLRANGE = 10.0f;
const float FIREBALLSPEED = 10.0f;
const float FIREBALLRADIUS = 0.1;
const float FIREBALLDAMAGE = 98.6f;
const float FIREEXPLOSIONTIME = 0.4f;

enum PROJECTILE_TYPE {PROJ_FIREBALL, PROJ_SHADOWBALL};

class Projectile : public Object
{
public:
	Projectile(VECTOR2 position, float speed, float radius, float range, float orient,
		Image* image, int damage, PROJECTILE_TYPE type=PROJ_FIREBALL, float freezeTime=0.f, float skipTime=0.f, int team=0) 
		: Object(position, speed, radius, image, CIRCLE, EMPTY_RECT, PROJECTILE), range(range), 
		traveled(0), orientation(orient), damage(damage), type(type), freezeTime(freezeTime), skipTime(skipTime),
		team(team)
	{velocity.x = cos(orientation); velocity.y = sin(orientation);};

	virtual void update(float frameTime, World* W);
	virtual void end(World* W);

	// Accessors
	int getTeam()				const {return team;}
	PROJECTILE_TYPE getType()	const {return type;}
	int getDamage()				const {return damage;}
	int getSkipTime()			const {return skipTime;}
	float getOrient()			const {return orientation;}

private:
	int damage;	// How much damage the projectile does
	int team;	
	float orientation;
	float range;
	float traveled;

	float freezeTime;
	float skipTime;

	PROJECTILE_TYPE type;
};

#endif