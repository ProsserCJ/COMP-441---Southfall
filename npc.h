/***************************************************************
The header file for NPC classes

Last Modified 11/2/2013

***************************************************************/
#ifndef _NPC_H
#define _NPC_H

#include "entity.h"
#include <vector>
#include "random.h"
#include <list>
using std::string;
using std::vector;
using std::list;

namespace npcNS
{
	//assign constants here
	const float NPC_SPEED = 1.5f; //arbitrarily chosen to be slower than Hero
	const float RADIUS = 0.25f;
	const int HP = 100;
	const int PIXELS_PER_MOVE = TILE_SIZE;
}

// Human Non Player Character class
class NPC: public Entity
{
public:
	NPC() : Entity() {}
	NPC(int ID, VECTOR2 pos, Image* image, Audio* audio, Drawable* attackImage=0)
		: Entity(pos, npcNS::RADIUS, npcNS::HP, image, audio, 0, HUMAN_CRECT, attackImage, NPCTYPE)
	{initialize();}
	~NPC() {}

	//inherited functions
	virtual void update(float frameTime, World* W);

	void initialize();
	/*static void initGraphics(Graphics* graphics);	*/
	void setPaused(bool b)					{paused = b;}

	virtual vector<string> getText()		{return text;}
	void setText(string t[], int count)		{text = vector<string>(t, t + count);}
	void addConditionalLine(int i)			{conditionalLines.push_front(i);}
	void updateText();
	
	/*static TextureManager* NPC_TX1;
	static Image* NPC_IM1;*/

private:
	double distanceTraveled;
	double timeSinceLastMove;
	vector<string> text;		//text to be returned for dialogue
	list<int> conditionalLines;	//list of text lines to be excluded after displayed once
	bool paused;
	Random rGen;

	
};


class Birmingham: public NPC
{
public:
	Birmingham(Audio* audio, Image* img):
	  NPC(0, ZERO, img, audio) {initialize();}

	  virtual vector<string> getText();
	  virtual void update(float frameTime, World* W) {NPC::update(frameTime,W); knockback = ZERO;}
	  void initialize();

private:
	list<vector<string>> texts;
	list<vector<string>>::iterator it;
};

#endif
