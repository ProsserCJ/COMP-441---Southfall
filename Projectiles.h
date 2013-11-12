#ifndef _PROJECTILES_H
#define _PROJECTILES_H

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