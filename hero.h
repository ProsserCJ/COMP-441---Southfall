/****************************************************
Hero header file, containts the definition
of a hero class

Last modified: 11/4/2013

******************************************************/

#ifndef _HERO_H
#define _HERO_H

#include "entity.h"

namespace heroNS{
	//store hero constants here
	const float HERO_SPEED = 90.f; //arbitrarily chosen for now
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

class Hero: public Entity
{
public:
	void attack();
	void move(DIR, float);

	virtual void draw(const VECTOR2& center){image->draw(); armor->draw();}
	virtual void act(World* W){}				
	virtual void update(float frameTime);

	bool initialize(Game* g, int width, int height, int ncols, TextureManager *textureM);

	DIR getDirectionFacing(){return facing;}

private:
	DIR facing;
	Input* input;
	Image* armor;

	void setStandingImage();

};

#endif
