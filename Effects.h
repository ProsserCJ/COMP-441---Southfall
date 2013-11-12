#ifndef _EFFECTS_H
#define _EFFECTS_H

#include "image.h"

class World;
class Entity;

class Effect
{
public:

	void update(float frameTime, World* W);
	void effect(Entity* E);
private:
	bool hidden;	// True if the effect is by default hidden
	bool invisible;	// True if the effect can never be seen

	Image* image;	// What the effect looks like (if it is not invisible)

	VECTOR2 position;
	float radius;
};

#endif