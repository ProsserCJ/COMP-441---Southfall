/****************************************************
Hero header file, containts the definition
of a hero class

Last modified: 11/5/2013

******************************************************/

#ifndef _HERO_H
#define _HERO_H
#define WIN32_LEAN_AND_MEAN

#include "Entity.h"
#include "textBox.h"

// Hero Namespace
namespace heroNS
{ //Store hero constants here
	const float HERO_SPEED = 5.0f;
	const float HEIGHT = TILE_SIZE;
	const float WIDTH = TILE_SIZE;
	const float HEROACTIONDELAY = 0.3;
	const int COLS = 4;	
	const int HERO_HP = 100;
	const float HERO_RADIUS = 0.15;
};
using namespace heroNS;

// The player's character
class Hero: public Entity
{
public:
	Hero() : Entity() {};
	Hero(VECTOR2 position, float radius, Image* image, Input* input, Audio* audio, TextBox* tb, int HP=heroNS::HERO_HP) 
		: Entity(position, radius, HP, image, 0, HUMAN_CRECT, HEROTYPE), input(input), audio(audio), textbox(tb) {initialize();}
	
	virtual void draw(VECTOR2& Center);
	virtual void act(World* W) {}
	virtual void update(float frameTime, World* W);
	void turnToPlayer(Entity* n);

	void initialize();

private:	
	Input* input;	
	Audio* audio;
	Image* armor;
	TextBox* textbox;
};

#endif
