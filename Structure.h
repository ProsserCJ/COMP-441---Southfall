/*************************************************************
Structure header file, defines classes of structures

Last Modified: 11/8/2013

*************************************************************/

#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#include "image.h"
#include "Entity.h"

class World;	// Forward reference to World
class WorldInterface;

class Structure : public Drawable
{
public:
	// Constructors and destructors
	Structure() {};
	Structure(VECTOR2 TL, int width, int height, Image* image, World* out) 
		: TL(TL), BR(VECTOR2(TL.x+width,TL.y+height)), Drawable(image), out(out) {};
	~Structure() {};

	virtual void draw(VECTOR2 Center);
	virtual void update(float frameTime); // Mostly for updating images
	virtual void interact(Entity* E)=0;
	virtual bool isPassable()=0;

	World* getWorld()  {return out;}

protected:
	// Structures are rectangular
	VECTOR2 TL;	// Top left x,y
	VECTOR2 BR;	// Bottow right x,y
	World* out;
	
};

class Portal : public Structure
{
public:
	Portal() {};
	Portal(VECTOR2 TL, int width, int height, Image* image, World* out, VECTOR2 vout, WorldInterface* w) 
		: Structure(TL,width,height,image,out), open(true), vOut(vout), WI(w) 
		{Drawable::setFrames(0,3);}

	virtual void interact(Entity* E);
	virtual bool isPassable() {return false;}

	void closePortal()	{open = false;}
	void openPortal()	{open = true;}
private:
	bool open;
	VECTOR2 vOut;
	WorldInterface* WI;
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

class House1 : public Structure
{
public:
	House1(VECTOR2 TL, int width, int height, Image* image) 
		: Structure(TL,width,height,image,0) {};
	~House1();
	virtual void interact(Entity*) {};
	virtual bool isPassable() {return false;}
private:
};
class House2 : public Structure
{
public:
	House2(VECTOR2 TL, int width, int height, Image* image) 
		: Structure(TL,width,height,image,0) {};
	~House2();
	virtual void interact(Entity*) {};
	virtual bool isPassable() {return false;}
private:
};
class House3 : public Structure
{
public:
	House3(VECTOR2 TL, int width, int height, Image* image) 
		: Structure(TL,width,height,image,0) {};
	~House3();
	virtual void interact(Entity*) {};
	virtual bool isPassable() {return false;}
private:
};
class House4 : public Structure
{
public:
	House4(VECTOR2 TL, int width, int height, Image* image) 
		: Structure(TL,width,height,image,0) {};
	~House4();
	virtual void interact(Entity*) {};
	virtual bool isPassable() {return false;}
private:
};

class Bar1 : public Structure
{
public:
	Bar1(VECTOR2 TL, int width, int height, Image* image) 
		: Structure(TL,width,height,image,0){};
	~Bar1() {};
	virtual void interact(Entity*) {};
	virtual bool isPassable() {return false;}
private:
};

class Bar2 : public Structure
{
public:
	Bar2(VECTOR2 TL, int width, int height, Image* image) 
		: Structure(TL,width,height,image,0){};
	~Bar2() {};
	virtual void interact(Entity*) {};
	virtual bool isPassable() {return false;}
private:
};

class HWall : public Structure
{
public:
	HWall(VECTOR2 TL, Image* image) 
		: Structure(TL,1,3,image,0){};
	~HWall() {};
	virtual void interact(Entity*) {};
	virtual bool isPassable() {return false;}
private:
};

#endif