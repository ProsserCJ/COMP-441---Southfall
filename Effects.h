/***************************************************************
The header file for the Effect class

Last Modified 11/12/2013

***************************************************************/

#ifndef _EFFECTS_H
#define _EFFECTS_H
#define WIN32_LEAN_AND_MEAN

#include "image.h"
#include "Entity.h"

inline float radianDiff(float R1, float R2)
{
	if(R1 < 0) R1 += TPI;
	if(R2 < 0) R2 += TPI;
	float m = min(R1,R2), M = max(R1,R2);
	float diff = abs(R1 - R2);
	if(diff > PI) diff = m - M + TPI;
	return diff;
}

class World;

class Effect : public Drawable, public Collidable
{
public:
	Effect() 
		: time(0), maxTime(0), _timed(false), _hidden(false), _invisible(false), 
		_done(false), Collidable(ZERO, POINTCOLLISION, 0) {};
	Effect(VECTOR2 position, float radius, COLLISIONTYPE CT, Image* image, bool timed=false, float time=0, bool hidden=true)
		:  _timed(timed), _hidden(hidden), _invisible(false), _done(false), time(0), 
		maxTime(time), Collidable(position, CT, radius), Drawable(image) {};

	void update(float frameTime, World* W);
	virtual void effect(Object* E, World* W) = 0;
	virtual void draw(VECTOR2 Center);

	bool isInvisible()	const {return _invisible;}
	bool isHidden()		const {return _hidden;}

	void setHidden(bool hidden)	{_hidden = hidden;}

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
	virtual void effect(Object* E, World* W);
};

class PortalTrapEffect : public Effect
{
public:
	PortalTrapEffect(VECTOR2 opening, VECTOR2 exit, float radius, Image* image, Image* exitImage)
		: Effect(opening, radius, CIRCLE, image), exit(exit), exitImage(exitImage) {};
	virtual void effect(Object* E, World* W);
	virtual void draw(VECTOR2 Center);
private:
	VECTOR2 exit;
	Image* exitImage;
};

class QuickPortal : public Effect
{
public:
	QuickPortal(VECTOR2 opening, VECTOR2 exit, float radius, Image* image, Image* exitImage)
		: Effect(opening, radius, CIRCLE, image), exit(exit), exitImage(exitImage) {};
	virtual void effect(Object* E, World* W);
	virtual void draw(VECTOR2 Center);
private:
	VECTOR2 exit;
	Image* exitImage;
};

class DamageEffect : public Effect
{
public:
	DamageEffect(VECTOR2 pos, int damage, float radius, int team, Image* image=0, bool timed=false, float time=0) 
		: Effect(pos, radius, CIRCLE, image, timed, time, false), team(team), damage(damage) {};
	virtual void effect(Object* E, World* W);
private:
	float damage;
	int team;
};

class SwordSwing : public Effect
{
public:
	SwordSwing(VECTOR2 pos, int damage, float radius, float orient, float deltaTheta, int team, Image* image=0, float time=0)
		:Effect(pos, radius, SWING, image, true, time), team(team), damage(damage), orient(orient), deltaTheta(deltaTheta) {};
	virtual void effect(Object* E, World* W);
private:
	float damage;
	float orient;
	float deltaTheta;
	int team;
};

class Explosion : public Effect
{
public:
	Explosion(VECTOR2 pos, int damage, float radius, int team, Image* image, float delay=1.0f)
		:Effect(pos, radius, CIRCLE, image, true, delay, false), team(team), damage(damage) 
	{setFrameDelay(time);}

	virtual void effect(Object* E, World* W);
private:
	float damage;
	int team;
};

#endif