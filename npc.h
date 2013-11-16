/***************************************************************
The header file for NPC classes

Last Modified 11/2/2013

***************************************************************/
#ifndef _NPC_H
#define _NPC_H

#include "entity.h"
#include <vector>
#include "random.h"
using std::string;
using std::vector;

namespace npcNS
{
	//assign constants here
	const float NPC_SPEED = 2.0f; //arbitrarily chosen to be slower than Hero
	const float RADIUS = 0.25f;
	const int HP = 100;
	const int PIXELS_PER_MOVE = TILE_SIZE;
}

class NPC: public Entity
{
public:
	NPC() : Entity() {}
	NPC(int ID, VECTOR2 pos)
		: Entity(pos, npcNS::RADIUS, npcNS::HP, getImage(ID), 0, NPCTYPE)
	{
		initialize(); 
		distanceTraveled = npcNS::PIXELS_PER_MOVE + 1;
		timeSinceLastMove = 0;
		paused = false;
	}
	~NPC() {}

	//inherited functions
	virtual void update(float frameTime, World* W);

	void initialize();
	static void initGraphics(Graphics* graphics);
	Image* getImage(int ID);
	void setPaused(bool b)					{paused = b;}

	
	vector<string> getText()				{return text;}
	void setText(string t[], int count)		{text = vector<string>(t, t + count);}

private:
	double distanceTraveled;
	double timeSinceLastMove;
	vector<string> text;		//text to be returned for dialogue
	bool paused;
	Random rGen;

	static TextureManager* NPC_TX1;
	static Image* NPC_IM1;
};

#endif
