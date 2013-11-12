/***************************************************************
The header file for the Effect class

Last Modified 11/12/2013

***************************************************************/

#ifndef _EFFECTS_H
#define _EFFECTS_H
#define WIN32_LEAN_AND_MEAN

#include "image.h"
#include "Entity.h"

class World;

class Effect : public Drawable, public Collidable
{
public:
	Effect() 
		: time(0), _timed(false), _hidden(false), _invisible(false), _done(false), Collidable(ZERO, POINTCOLLISION, 0) {};
	Effect(VECTOR2 position, float radius, COLLISIONTYPE CT, Image* image)
		: time(0), _timed(false), _hidden(true), _invisible(false), _done(false), Collidable(position, CT, radius), Drawable(image) {};

	void update(float frameTime, World* W);
	virtual void effect(Object* E) = 0;
	virtual void draw(VECTOR2 Center);

	// Accessors
	bool done() {return _done;}

protected:
	bool _hidden;	// True if the effect is by default hidden
	bool _invisible;// True if the effect can never be seen
	bool _timed;	// True if the effect only lasts for a certain duration
	float time;		// How long the effect has existed
	float maxTime;	// How long the effect can exist
	bool _done;		// True if the effect is over
};

class ImpedeEffect : public Effect
{
public:
	ImpedeEffect(VECTOR2 position, float radius, Image* image) 
		: Effect(position, radius, CIRCLE, image) {};
	virtual void effect(Object* E);
};

class PortalTrapEffect : public Effect
{
public:
	PortalTrapEffect(VECTOR2 opening, VECTOR2 exit, float radius, Image* image, Image* exitImage)
		: Effect(opening, radius, CIRCLE, image), exit(exit), exitImage(exitImage) {};
	virtual void effect(Object* E);
	virtual void draw(VECTOR2 Center);
private:
	VECTOR2 exit;
	Image* exitImage;
};

#endif