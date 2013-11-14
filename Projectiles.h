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
const int FIREBALLEND = 0;

class Projectile : public Object
{
public:
	Projectile(VECTOR2 position, float radius, float range, float orient, Image* image) 
		: Object(position, radius, image, CIRCLE), range(range), traveled(0), orientation(orient) 
	{velocity.x = cos(orientation); velocity.y = sin(orientation);};

	virtual void update(float frameTime, World* W);
	virtual void interact(World* W);

private:
	int damage;	// How much damage the projectile does
	float orientation;
	float range;
	float traveled;
};

#endif