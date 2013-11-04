/***************************************************************
The header file for the entity class that living game entities
and characters inherit from.

Last Modified 11/2/2013

***************************************************************/

#ifndef _ENTITY_H
#define _ENTITY_H
#define WIN32_LEAN_AND_MEAN

#include "image.h"
#include "input.h"
#include "game.h"
#include "World.h"

//class World; // Foreward reference to world

const VECTOR2 ZERO = VECTOR2(0,0);

namespace entityNS{
	enum DIR {UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT};
	enum COLLISIONTYPE{CIRCLE, POINTCOLLISION};	
}
using namespace entityNS;

// Base for in game characters, monsters, and animals
class Entity
{
public:
	// Constructors and destructors
	Entity() : position(ZERO), velocity(ZERO), knockback(ZERO), image(0), maxHP(0), HP(0), 
		radius(0), active(false), collisionType(POINTCOLLISION) {};
	Entity(VECTOR2 pos, float radius, int HP, Image* image) 
		: position(pos), radius(radius), collisionType(CIRCLE), image(image), HP(HP), 
		maxHP(HP), velocity(ZERO), knockback(ZERO), active(true) {};
	~Entity() {};

	// Basic functions
	virtual void draw(const VECTOR2& center){};		// Draw itself (possibly needs second parameter, zoomlevel or something)
	virtual void act(World* W) = 0;					// AI and decisions
	virtual void update(float frameTime){};	// Update

	// Collision Handler
	friend bool HandleCollision(Entity* A, Entity* B) {return true; }; // True if the entities collided

	// Accessors
	VECTOR2 getPosition()	const {return position;}
	VECTOR2 getVelocity()	const {return velocity;}
	float getRadius()		const {return radius;}
	int getHP()				const {return HP;}
	virtual bool alive()	{return HP > 0;}
	virtual bool isActive() {return active;}

	// Mutators
	void setPosition(const VECTOR2& pos)	{position = pos;}
	void setVelocity(const VECTOR2& vel)	{velocity = vel;}
	void setKnockback(const VECTOR2& kb)	{knockback = kb;}
	void setActive(bool act)				{active = act;}
	void setHP(int HP)						{this->HP = HP;}
	void kill()								{HP = 0;}	

protected:
	VECTOR2 position;	// Position in the world (center)
	VECTOR2 velocity;	// Velocity of the entity
	VECTOR2 knockback;	// For knock back effects
	float radius;
	int HP;
	int maxHP;
	bool active;
	World* world;
	Image* image;		//Is this better than deriving from Image?
						
	COLLISIONTYPE collisionType;
};

#endif