#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#include "image.h"

class World;	// Forward reference to World

class Structure
{
public:
	// Constructors and destructors
	Structure() {};
	~Structure() {};

	void draw(VECTOR2 Center);

private:
	// Structures are rectangular
	VECTOR2 TL;	// Top left x,y
	VECTOR2 BR;	// Bottow right x,y
	Image* image;
};

#endif