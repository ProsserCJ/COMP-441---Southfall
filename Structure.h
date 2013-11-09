/*************************************************************
Structure header file, defines classes of structures

Last Modified: 11/8/2013

*************************************************************/

#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#include "image.h"

class World;	// Forward reference to World

class Structure
{
public:
	// Constructors and destructors
	Structure() {};
	Structure(VECTOR2 TL, int width, int height, Image* image, World* out) 
		: TL(TL), BR(VECTOR2(TL.x+width,TL.y+height)), image(image), out(out) {};
	~Structure() {};

	void draw(VECTOR2 Center);
	virtual void interact()=0;
	virtual bool isPassable()=0;

protected:
	// Structures are rectangular
	VECTOR2 TL;	// Top left x,y
	VECTOR2 BR;	// Bottow right x,y
	Image* image;
	World* out;
};

class Door : public Structure
{
public:
	Door(VECTOR2 TL, int width, int height, Image* image, World* out) 
		: Structure(TL,width,height,image,out), open(0) {};
	~Door() {};
	virtual void interact();
	virtual bool isPassable() {return static_cast<bool>(open);}
private:
	int open;
};

class House : public Structure
{
public:
	House(VECTOR2 TL, int width, int height, Image* image, World* out) 
		: Structure(TL,width,height,image,out) {};
	~House();
	virtual void interact() {};
	virtual bool isPassable() {return false;}
private:

};

class Bar : public Structure
{
public:
	Bar(VECTOR2 TL, int width, int height, Image* image, World* out) 
		: Structure(TL,width,height,image,out) {};
	~Bar();
	virtual void interact() {};
	virtual bool isPassable() {return false;}
private:

};

#endif