#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#include "image.h"

class World;	// Forward reference to World

class Structure
{
public:
	// Constructors and destructors
	Structure() {};
	Structure(VECTOR2 TL, int width, int height, Image* image) 
		: TL(TL), BR(VECTOR2(TL.x+width,TL.y+height)), image(image) {};
	~Structure() {};

	void draw(VECTOR2 Center);

private:
	// Structures are rectangular
	VECTOR2 TL;	// Top left x,y
	VECTOR2 BR;	// Bottow right x,y
	Image* image;
};

class House : public Structure
{
public:
	House(VECTOR2 TL, int width, int height, Image* image) 
		: Structure(TL,width,height,image) {};
	~House();
private:

};

class Bar : public Structure
{
public:
	Bar(VECTOR2 TL, int width, int height, Image* image) 
		: Structure(TL,width,height,image) {};
	~Bar();
private:

};

#endif