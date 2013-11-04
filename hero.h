/****************************************************
Hero header file, containts the definition
of a hero class

Last modified: 11/3/2013

******************************************************/

#ifndef _HERO_H
#define _HERO_H

#include "entity.h"


class Hero: public Entity
{
public:
	void attack(DIR);
	void move(DIR);

	virtual void draw();	
	virtual void update();	
	virtual void act();

	DIR getDirectionFacing(){return facing;}

private:
	DIR facing;

};

#endif
