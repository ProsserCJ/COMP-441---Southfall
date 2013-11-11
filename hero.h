/****************************************************
Hero header file, containts the definition
of a hero class

Last modified: 11/5/2013

******************************************************/

#ifndef _HERO_H
#define _HERO_H

#include "Entity.h"
#include "textBox.h"

namespace heroNS
{ //Store hero constants here
	const float HERO_SPEED = 3.5f;
	const float HEIGHT = TILE_SIZE;
	const float WIDTH = TILE_SIZE;
	const int COLS = 4;	
	const int HERO_HP = 100;
	const float HERO_RADIUS = 0.25;
}

// The player's character
class Hero: public Entity
{
public:
	Hero() : Entity() {};
	Hero(VECTOR2 position, float radius, Image* image, Input* input, Audio* audio, TextBox* tb, int HP=heroNS::HERO_HP) 
		: Entity(position, radius, HP, image), input(input), audio(audio), textbox(tb) {initialize();}
	void attack(DIR);
	void attack();

	virtual void draw(const VECTOR2& Center);
	virtual void act(World* W) {}
	virtual void update(float frameTime, World* W);
	void turnToPlayer(NPC* n);

	void initialize();

private:	
	Input* input;	
	Audio* audio;
	Image* armor;
	TextBox* textbox;

	
};

#endif
