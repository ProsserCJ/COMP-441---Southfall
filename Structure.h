/*************************************************************
Structure header file, defines classes of structures

Last Modified: 11/8/2013

*************************************************************/

#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#include "image.h"
#include "Entity.h"

class World;	// Forward reference to World

class Structure
{
public:
	// Constructors and destructors
	Structure() {};
	Structure(VECTOR2 TL, int width, int height, Image* image, World* out) 
		: TL(TL), BR(VECTOR2(TL.x+width,TL.y+height)), image(image), out(out) {};
	~Structure() {};

	virtual void draw(VECTOR2 Center);
	virtual void interact(Entity* E)=0;
	virtual bool isPassable()=0;

protected:
	// Structures are rectangular
	VECTOR2 TL;	// Top left x,y
	VECTOR2 BR;	// Bottow right x,y
	Image* image;
	World* out;
};

class Portal : public Structure
{
public:
	Portal() {};
	Portal(VECTOR2 TL, int width, int height, Image* image, World* out, VECTOR2 vout) 
		: Structure(TL,width,height,image,out), open(true), vOut(vout) {};

	virtual void interact(Entity* E);
	virtual bool isPassable() {return false;}

	void closePortal()	{open = false;}
	void openPortal()	{open = true;}
private:
	bool open;
	VECTOR2 vOut;
};

// An open and closeable door for use in buildings
class Door : public Structure
{
public:
	Door(VECTOR2 TL, int width, int height, Image* image) 
		: Structure(TL,width,height,image,0), open(0) {};
	~Door() {};
	virtual void interact(Entity*);
	virtual void draw(VECTOR2 Center);
	virtual bool isPassable() {return open == 1;}
private:
	int open;
};

class House : public Structure
{
public:
	House(VECTOR2 TL, int width, int height, Image* image) 
		: Structure(TL,width,height,image,0) {};
	~House();
	virtual void interact(Entity*) {};
	virtual bool isPassable() {return false;}
private:

};

class Bar : public Structure
{
public:
	Bar(VECTOR2 TL, int width, int height, Image* image) 
		: Structure(TL,width,height,image,0) {};
	~Bar();
	virtual void interact(Entity*) {};
	virtual bool isPassable() {return false;}
private:

};

#endif