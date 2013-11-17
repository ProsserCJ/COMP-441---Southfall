/***************************************************************
The header file for the entity class that living game entities
and characters inherit from. Also contains Drawable, Collidable,
and Object class definitions

Last Modified 11/14/2013

***************************************************************/

#ifndef _ENTITY_H
#define _ENTITY_H
#define WIN32_LEAN_AND_MEAN

#include "image.h"
#include "input.h"
#include "game.h"

class Item;
class World;
class Projectile;

enum SPELLTYPE{NOSPELL, IMPEDE, QUICKPORTAL, BLINK, FIREBALL, FREEZE, MAGICSIGHTON, MAGICSIGHTOFF, PORTALTRAP};

const VECTOR2 ZERO(0,0);
const VECTOR2 HSCREEN(HSCREEN_WIDTH, HSCREEN_HEIGHT);
const float DEFAULT_FRAME_DELAY = 0.2f;
const float INTERACTIONDELAY = 0.5f;

enum OBJECTTYPE {PROJECTILE, OBJECT, ENTITY, NPCTYPE, HEROTYPE};

struct ColRect
{
	ColRect(float boxRadius, float height) 
		: boxRadius(boxRadius), height(height) {};
	float boxRadius;
	float height;
};
// Collision Rectangles
const ColRect EMPTY_RECT(0.f,0.f);
const ColRect HUMAN_CRECT(0.2f,1.0f);
const ColRect WRAITH_CRECT(0.25f,6.0f);
const ColRect TREE_CRECT(0.25f, 1.2f);

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
	const int ATTACK_DOWN_START = 48;
	const int ATTACK_DOWN_END = 50;
	const int ATTACK_RIGHT_START = 44;
	const int ATTACK_RIGHT_END = 46;
	const int ATTACK_UP_START = 52;
	const int ATTACK_UP_END = 54;
	const int ATTACK_LEFT_START = 40;
	const int ATTACK_LEFT_END = 42;

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

	// Accessors
	Image* & getImage()						{return image;}
	int getFrame()							{return _frame;}
	int getEndFrame()						{return _endFrame;}
	bool noImage()							{return image == 0;}
	int getImageWidth()						{return image->getWidth();}
	int getImageHeight()					{return image->getHeight();}
	float getImageScale()					{return image->getScale();}
	// Mutators
	void setImageX(int x)					{image->setX(x);}
	void setImageY(int y)					{image->setY(y);}
	void setScale(float scale)				{image->setScale(scale);}
	void draw(DWORD color=graphicsNS::WHITE){image->draw(color);}
	void updateImage();
	void setFrame()							{image->setCurrentFrame(_frame);}
	void setFrame(int frame)				{_frame=frame;}	// Directly set the frame
	// Image updating
	void setStationaryFrame(int frame);
	void updateImage(float frameTime);
	void setFrames(int start, int end);
	void setSingleLoop(int start, int end);
	void setSingleLoop(int start, int end, float frameDelay);
	void setFrameDelay(float delay);
	void startImage();

private:
	private:
	// Image and animation control
	int _frame;			// What frame to display
	bool _singleLoop;
	float _imageTime;	// How long the current frame has displayed
	float _imageDelay;	// How long each frame should display
	float _saveImageDelay;
	int _startFrame;		// Start of the animation loop
	int _endFrame;		// End of the animation loop
	int _saveStartFrame;
	int _saveEndFrame;
	Image* image;		// The sprite sheet to display from
};

// The class that allows for positioning and collision
class Collidable
{
public:
	Collidable(VECTOR2 position, COLLISIONTYPE CT, float radius) 
		: position(position), collisionType(CT), radius(radius), active(true), 
		collisionRectangle(EMPTY_RECT), hasRect(false) {}
	Collidable(VECTOR2 position, COLLISIONTYPE CT, float radius, ColRect CR) 
		: position(position), collisionType(CT), radius(radius), active(true), 
		collisionRectangle(CR), hasRect(true) {}

	// Collision Handler
	friend bool HandleCollision(Collidable* A, Collidable* B); // True if the objects collided
	friend bool ProjectileCollision(Projectile* P, Collidable* E);

	// Accessors
	VECTOR2 getPosition()		const {return position;}
	float getRadius()			const {return radius;}
	bool isActive()				const {return active;}

	// Mutators
	void setPosition(const VECTOR2& pos)	{position = pos;}
	void deactivate()						{active = false;}

protected:
	VECTOR2 position;		// Position in the world (center)
	COLLISIONTYPE collisionType;	// For collisions with entities
	ColRect collisionRectangle;		// For collisions with projectiles
	bool hasRect;
	float radius;
	bool active;
};

// An object that can appear in the game
class Object : public Drawable, public Collidable
{
public:
	Object() 
		: Collidable(ZERO, POINTCOLLISION, 0), velocity(ZERO), Drawable(0), speed(1), type(OBJECT) 
	{initialize();}
	Object(Image* image)
		: Collidable(ZERO, POINTCOLLISION, 0), Drawable(image), speed(1), type(OBJECT) {initialize();}
	Object(VECTOR2 pos, float speed, float radius, Image* image, COLLISIONTYPE CT, ColRect CR, OBJECTTYPE type=OBJECT) 
		: Collidable(pos, CT, radius, CR), Drawable(image), velocity(ZERO), speed(speed), type(type) {initialize();}

	void update(float frameTime, World* W);
	virtual void draw(VECTOR2& Center, DWORD color = graphicsNS::WHITE);
	void initialize();

	// Accessors
	VECTOR2 getVelocity()		const {return velocity;}
	VECTOR2 getLastPosition()	const {return lastPosition;}
	World* getWorld()			const {return world;}
	OBJECTTYPE getType()		const {return type;}
	int LTileX()				const {return (int)lastPosition.x;}
	int LTileY()				const {return (int)lastPosition.y;}

	// Mutators
	void newPosition(const VECTOR2& pos, World* W);
	void setVelocity(const VECTOR2& vel)	{velocity = vel;}
	void stop()								{velocity = ZERO;}

protected:
	inline void handleSectors(World* W);

	VECTOR2 lastPosition;	// Last position (for sectorization)
	VECTOR2 velocity;		// Velocity direction of the entity
	float speed;			// Speed the object travels at
	bool moving;			// True if the object should move in the direction it is facing
	float radius;			// Interaction radius
	
	OBJECTTYPE type;
	World* world;
};

// Base for in game characters, monsters, and animals
class Entity : public Object
{
public:
	// Constructors and destructors
	Entity() 
		: Object(), knockback(ZERO), maxHP(0), HP(0), team(0) {initialize();}
	Entity(VECTOR2 pos, float radius, int HP, Image* image, int team, ColRect CR, OBJECTTYPE type=ENTITY) 
		: Object(pos, 1.0f, radius, image, CIRCLE, CR, type), HP(HP), maxHP(HP), knockback(ZERO), team(team) {initialize();}
	~Entity() {};

	// Basic functions
	void initialize();
	virtual void draw(VECTOR2& center, DWORD color=graphicsNS::WHITE);
	virtual void act(World* W);					// AI and decisions
	virtual void update(float frameTime, World* W);
	void move(float frameTime, World* W);
	virtual void interact(World* W);				// Interact with a tile
	virtual void attack(float orient);

	// Accessors
	int getHP()					const {return HP;}
	int getTeam()				const {return team;}
	virtual bool alive()		{return HP > 0;}
	bool hasTarget()			{return _hasTarget;}
	bool usingMagicSight()		const {return _magicSight;}
	bool isAttacking()			{return attacking;}
	DIR getDirectionFacing()	{return facing;}
	VECTOR2 getTarget()			{return target;}
	SPELLTYPE getSpellType()	{return SpellType;}

	// Mutators
	void setKnockback(const VECTOR2& kb)	{knockback = kb;}
	void setActive(bool act)				{active = act;}
	void setHP(int HP)						{this->HP = HP;}
	void setWorld(World* W)					{world = W;}
	void setTarget(VECTOR2 T)				{target = T; _hasTarget = true;}
	void setSpellType(SPELLTYPE S)			{SpellType = S;}
	void resetTarget()						{_hasTarget = false;}
	void kill()								{HP = 0; active = false;}
	void receiveDamage(Projectile* p);
	void setDir(DIR face)					{facing=face;}
	void go(DIR face);			
	void standing();
	virtual void setStandingImage();
	void freeze(float time)					{_frozen=true;freezeTime=time;}
	void switchMagicSight()					{_magicSight = !_magicSight;}
	void setMagicSight(bool s)				{_magicSight = s;}

protected:
	VECTOR2 knockback;	// For knock back effects
	int HP;
	int maxHP;
	int team;
	float timeSinceInteract;
	float timeSinceAction;
	float timeSinceAttack;
	//Movement control
	DIR facing;	
	DIR lastDir;
	bool startMoving;
	bool attacking;
	SPELLTYPE SpellType;
	VECTOR2 target;
	bool _hasTarget;

	bool _frozen;
	float freezeTime;

	bool _magicSight;
	float magic;
	float maxMagic;
	float magicRecharge;
};

#endif
