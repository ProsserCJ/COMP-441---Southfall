/***************************************************************
The header file for the entity class that living game entities
and characters inherit from. Also contains Drawable, Collidable,
and Object class definitions

Last Modified 11/12/2013

***************************************************************/

#ifndef _ENTITY_H
#define _ENTITY_H
#define WIN32_LEAN_AND_MEAN

#include "image.h"
#include "input.h"
#include "game.h"
#include "Item.h"

class World;

const VECTOR2 ZERO = VECTOR2(0,0);
const float DEFAULT_FRAME_DELAY = 0.2f;
const float INTERACTIONDELAY = 0.5f;

// Entity Namespace
namespace entityNS
{
	enum DIR {UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT, NONE};
	enum COLLISIONTYPE{CIRCLE, POINTCOLLISION};	

	// Generic Frame Definitions
	const int WALKING_DOWN_START = 8;
	const int WALKING_DOWN_END = 11;
	const int WALKING_DOWN_RIGHT_START = 12;
	const int WALKING_DOWN_RIGHT_END = 15;
	const int WALKING_RIGHT_START = 16;
	const int WALKING_RIGHT_END = 19;
	const int WALKING_UP_RIGHT_START = 20;
	const int WALKING_UP_RIGHT_END = 23;
	const int WALKING_UP_START = 24;
	const int WALKING_UP_END = 27;
	const int WALKING_UP_LEFT_START = 28;
	const int WALKING_UP_LEFT_END = 31;
	const int WALKING_LEFT_START = 32;
	const int WALKING_LEFT_END = 35;
	const int WALKING_DOWN_LEFT_START = 36;
	const int WALKING_DOWN_LEFT_END = 39;
	// Facing 
	const int FACING_DOWN = 0;
	const int FACING_DOWN_RIGHT = 1;
	const int FACING_RIGHT = 2;
	const int FACING_UP_RIGHT = 3;
	const int FACING_UP = 4;
	const int FACING_UP_LEFT = 5;
	const int FACING_LEFT = 6;
	const int FACING_DOWN_LEFT = 7;
	// Attacking
	const int ATTACK_DOWN_START = 0;
	const int ATTACK_DOWN_END = 0;
	const int ATTACK_RIGHT_START = 0;
	const int ATTACK_RIGHT_END = 0;
	const int ATTACK_UP_START = 0;
	const int ATTACK_UP_END = 0;
	const int ATTACK_LEFT_START = 0;
	const int ATTACK_LEFT_END = 0;

}
using namespace entityNS;

class Object; // Forward reference to object

// The class that allows drawing and animation control
class Drawable
{
public:
	Drawable() : image(0) {initialize();}
	Drawable(Image* image) : image(image) {initialize();};
	void initialize();
	// Mutators
	void setImageX(int x)					{image->setX(x);}
	void setImageY(int y)					{image->setY(y);}
	void setScale(float scale)				{image->setScale(scale);}
	void draw()								{image->draw();}
	void updateImage();
	void setFrame()							{image->setCurrentFrame(_frame);}
	void setFrame(int frame)				{_frame=frame;}	// Directly set the frame
	// Image updating
	void setStationaryFrame(int frame)		{_startFrame=_endFrame=_frame=frame;}
	void updateImage(float frameTime);
	void setFrames(int start, int end)		{_startFrame=start;_endFrame=end;_frame=start;}
	void setFrameDelay(float delay)			{_imageDelay=delay;}
	void startImage()						{_frame=_startFrame;}
	// Accessors
	Image* & getImage()						{return image;}
	int getFrame()							{return _frame;}
	bool noImage()							{return image == 0;}
private:
	private:
	// Image and animation control
	int _frame;			// What frame to display
	float _imageTime;	// How long the current frame has displayed
	float _imageDelay;	// How long each frame should display
	int _startFrame;		// Start of the animation loop
	int _endFrame;		// End of the animation loop
	Image* image;		// The sprite sheet to display from
};

// The class that allows for positioning and collision
class Collidable
{
public:
	Collidable(VECTOR2 position, COLLISIONTYPE CT, float radius) 
		: position(position), collisionType(CT), radius(radius) {}

	// Collision Handler
	friend bool HandleCollision(Collidable* A, Collidable* B); // True if the objects collided

	// Accessors
	VECTOR2 getPosition()		const {return position;}
	float getRadius()			const {return radius;}

	// Mutators
	void setPosition(const VECTOR2& pos)	{position = pos;}

private:
	VECTOR2 position;	// Position in the world (center)
	COLLISIONTYPE collisionType;
	float radius;
};

// An object that can appear in the game
class Object : public Drawable, public Collidable
{
public:
	Object() 
		: Collidable(ZERO, POINTCOLLISION, 0), velocity(ZERO), Drawable(0), active(false) {initialize();}
	Object(Image* image) 
		: Collidable(ZERO, POINTCOLLISION, 0), Drawable(image) {initialize();};
	Object(VECTOR2 pos, float radius, Image* image, COLLISIONTYPE CT) 
		: Collidable(pos, CT, radius), Drawable(image), velocity(ZERO), active(true) {initialize();}

	void update(float frameTime, World* W);
	void initialize();

	// Accessors
	VECTOR2 getVelocity()		const {return velocity;}
	virtual bool isActive()		{return active;}
	World* getWorld()			const {return world;}

	// Mutators
	void setVelocity(const VECTOR2& vel)	{velocity = vel;}
	void stop()								{velocity = ZERO;}

protected:
	
	VECTOR2 velocity;	// Velocity direction of the entity
	float speed;		// Speed the object travels at
	bool moving;		// True if the object should move in the direction it is facing
	float radius;		// Interaction radius
	
	
	bool active;
	World* world;
};

// Base for in game characters, monsters, and animals
class Entity : public Object
{
public:
	// Constructors and destructors
	Entity() 
		: Object(), knockback(ZERO), maxHP(0), HP(0) {initialize();}
	Entity(VECTOR2 pos, float radius, int HP, Image* image) 
		: Object(pos, radius, image, CIRCLE), HP(HP), maxHP(HP), knockback(ZERO) {initialize();}
	~Entity() {};

	// Basic functions
	void initialize();
	virtual void draw(const VECTOR2& center);		// Draw itself (possibly needs second parameter, zoomlevel or something)
	virtual void act(World* W) = 0;					// AI and decisions
	virtual void update(float frameTime, World* W);
	void move(float frameTime, World* W);
	virtual void interact(World* W);				// Interact with a tile

	// Accessors
	int getHP()					const {return HP;}
	virtual bool alive()		{return HP > 0;}
	DIR getDirectionFacing()	{return facing;}

	// Mutators
	void setKnockback(const VECTOR2& kb)	{knockback = kb;}
	void setActive(bool act)				{active = act;}
	void setHP(int HP)						{this->HP = HP;}
	void setWorld(World* W)					{world = W;}
	void kill()								{HP = 0;}
	void setDir(DIR face)					{facing=face;}
	void go(DIR face);			
	void standing();
	virtual void setStandingImage();

protected:
	VECTOR2 knockback;	// For knock back effects
	int HP;
	int maxHP;
	float timeSinceInteract;
	//Movement control
	DIR facing;	
	DIR lastDir;
	bool startMoving;			
};

#endif