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

const VECTOR2 ZERO = VECTOR2(0,0);
const float DEFAULT_FRAME_DELAY = 0.2;

namespace entityNS
{
	enum DIR {UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT, NONE};
	enum COLLISIONTYPE{CIRCLE, POINTCOLLISION};	
}
using namespace entityNS;

// Base for in game characters, monsters, and animals
class Entity
{
public:
	// Constructors and destructors
	Entity() : position(ZERO), velocity(ZERO), knockback(ZERO), image(0), maxHP(0), HP(0), 
		radius(0), active(false), collisionType(POINTCOLLISION) {initialize();}
	Entity(VECTOR2 pos, float radius, int HP, Image* image) 
		: position(pos), radius(radius), collisionType(CIRCLE), image(image), HP(HP), 
		maxHP(HP), velocity(ZERO), knockback(ZERO), active(true) {initialize();}
	~Entity() {};

	// Basic functions
	void initialize();
	virtual void draw(const VECTOR2& center);		// Draw itself (possibly needs second parameter, zoomlevel or something)
	virtual void act(World* W) = 0;					// AI and decisions
	virtual void update(float frameTime){}			// Update

	// Collision Handler
	friend bool HandleCollision(Entity* A, Entity* B) {return true; }; // True if the entities collided

	// Accessors
	VECTOR2 getPosition()		const {return position;}
	VECTOR2 getVelocity()		const {return velocity;}
	float getRadius()			const {return radius;}
	int getHP()					const {return HP;}
	virtual bool alive()		{return HP > 0;}
	virtual bool isActive()		{return active;}
	DIR getDirectionFacing()	{return facing;}

	// Mutators
	void setPosition(const VECTOR2& pos)	{position = pos; image->setX(pos.x); image->setY(pos.y);}
	void setVelocity(const VECTOR2& vel)	{velocity = vel;}
	void setKnockback(const VECTOR2& kb)	{knockback = kb;}
	void setActive(bool act)				{active = act;}
	void setHP(int HP)						{this->HP = HP;}
	void kill()								{HP = 0;}	
	
	// Image updating
	void setFrame(int frame)				{this->frame=frame;}	// Directly set the frame
	void setStationaryFrame(int frame)		{startFrame=endFrame=this->frame=frame;}
	void updateImage(float frameTime)		{_imageTime+=frameTime;}
	void setFrames(int start, int end)		{startFrame=start;endFrame=end;frame=start;}
	void setFrameDelay(float delay)			{_imageDelay=delay;}
	void startImage()						{frame=startFrame;}
	void setDir(DIR face)					{facing=face;}
	void go(DIR face);			
	void standing();
	virtual void setStandingImage()=0;

protected:
	VECTOR2 position;	// Position in the world (center)
	VECTOR2 velocity;	// Velocity of the entity
	VECTOR2 knockback;	// For knock back effects
	RECT collisionRectangle;
	float radius;
	int HP;
	int maxHP;
	bool active;
	World* world;

	// Image and animation control
	int frame;			// What frame to display
	float _imageTime;	// How long the current frame has displayed
	float _imageDelay;	// How long each frame should display
	int startFrame;		// Start of the animation loop
	int endFrame;		// End of the animation loop
	Image* image;		// The sprite sheet to display from

	//Movement control
	DIR facing;	
	DIR lastDir;
	bool moving;		// True if the entity should move in the direction it is facing
	bool startMoving;
						
	COLLISIONTYPE collisionType;
};

#endif