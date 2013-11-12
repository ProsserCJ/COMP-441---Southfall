/***************************************************************
The header file for the Projectile class

Last Modified 11/12/2013

***************************************************************/

#ifndef _PROJECTILES_H
#define _PROJECTILES_H
#define WIN32_LEAN_AND_MEAN

#include "Entity.h"

class Projectile : public Object
{
public:
	Projectile(VECTOR2 position, float radius, Image* image) 
		: Object(position, radius, image, CIRCLE) {};
	virtual void draw(const VECTOR2& center);
	virtual void update(float frameTime, World* W);
	virtual void interact(World* W);

private:

};

#endif