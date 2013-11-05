/****************************************************
Hero header file, containts the definition
of a hero class

Last modified: 11/4/2013

******************************************************/

#ifndef _HERO_H
#define _HERO_H

#include "Entity.h"

namespace heroNS{
	//store hero constants here
	const float HERO_SPEED = 1.f; //arbitrarily chosen for now
	const float HEIGHT = TILE_SIZE;
	const float WIDTH = TILE_SIZE;
	const int COLS = 4;	
		
	//assign frame numbers here
	enum {
		HERO_FACING_UP, 
		HERO_FACING_DOWN,  
		HERO_FACING_LEFT,  
		HERO_FACING_RIGHT,
		HERO_FACING_UP_RIGHT, 
		HERO_FACING_UP_LEFT,
		HERO_FACING_DOWN_RIGHT,
		HERO_FACING_DOWN_LEFT,

		HERO_WALKING_UP_START,
		HERO_WALKING_UP_END,
		HERO_WALKING_DOWN_START,
		HERO_WALKING_DOWN_END,
		HERO_WALKING_LEFT_START,
		HERO_WALKING_LEFT_END,
		HERO_WALKING_RIGHT_START,
		HERO_WALKING_RIGHT_END,
		HERO_WALKING_UP_RIGHT_START,
		HERO_WALKING_UP_RIGHT_END,
		HERO_WALKING_UP_LEFT_START,
		HERO_WALKING_UP_LEFT_END,
		HERO_WALKING_DOWN_RIGHT_START,
		HERO_WALKING_DOWN_RIGHT_END,
		HERO_WALKING_DOWN_LEFT_START,
		HERO_WALKING_DOWN_LEFT_END,

		HERO_SWINGING_UP_START,
		HERO_SWINGING_UP_END,
		HERO_SWINGING_DOWN_START,
		HERO_SWINGING_DOWN_END,
		HERO_SWINGING_LEFT_START,
		HERO_SWINGING_LEFT_END,
		HERO_SWINGING_RIGHT_START,
		HERO_SWINGING_RIGHT_END,
		HERO_SWINGING_UP_RIGHT_START,
		HERO_SWINGING_UP_RIGHT_END,
		HERO_SWINGING_UP_LEFT_START,
		HERO_SWINGING_UP_LEFT_END,
		HERO_SWINGING_DOWN_RIGHT_START,
		HERO_SWINGING_DOWN_RIGHT_END,
		HERO_SWINGING_DOWN_LEFT_START,
		HERO_SWINGING_DOWN_LEFT_END
	};

}

// The player's character
class Hero: public Entity
{
public:
	Hero() : Entity() {};
	Hero(Image* image) : Entity() {initialize(image);}
	void attack(DIR);
	void move(DIR);
	void attack();
	void move(float);

	virtual void draw(const VECTOR2& Center);
	virtual void act(World* W)					{}
	virtual void update(float frameTime);

	void initialize(Image* image);

	// Accessors
	DIR getDirectionFacing()	{return facing;}

	// Mutators
	void setDir(DIR face)		{facing=face;}
	void go(DIR face)			{startMoving=true;facing=face;}
	void setStandingImage();
	void standing()				{startMoving=moving=false;setStandingImage();}

private:
	DIR facing;
	DIR lastDir;
	bool moving;	// True if the hero should move in the direction it is facing
	bool startMoving;
	Input* input;
	
	Image* armor;
};

#endif
