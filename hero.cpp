/****************************************************
Hero implementation file

Last modified: 11/5/2013

******************************************************/

#include "hero.h"
using namespace heroNS;

void Hero::initialize()
{
	armor = 0;
	setFrameDelay(DEFAULT_FRAME_DELAY);
	speed = HERO_SPEED;
};

void Hero::update(float frameTime, World* W)
{
	velocity = ZERO;
	DIR dir = NONE;
	if (input->isKeyDown(WKEY))
    {
            if (input->isKeyDown(DKEY))			go(UP_RIGHT);
            else if (input->isKeyDown(AKEY))	go(UP_LEFT);        
            else								go(UP);
    }        
    else if (input->isKeyDown(SKEY))
    {
            if (input->isKeyDown(DKEY))			go(DOWN_RIGHT);
            else if (input->isKeyDown(AKEY))	go(DOWN_LEFT);        
            else								go(DOWN);
    }
    else if (input->isKeyDown(AKEY))			go(LEFT);
    else if (input->isKeyDown(DKEY))			go(RIGHT);
    else										standing();

	Entity::update(frameTime, W);

	if(startMoving && !W->canMoveHere(position + velocity*frameTime, radius))
	{
		audio->playCue(COLLIDE);
	}
}

void Hero::attack()
{
	// This function will need tweaking
	//Indeed
	VECTOR2 attackLocation(position);
	switch(facing)
	{
	case UP:
		setFrames(ATTACK_UP_START, ATTACK_UP_END);
		attackLocation.y -= TILE_SIZE;
		break;
	case DOWN:
		setFrames(ATTACK_DOWN_START, ATTACK_DOWN_END);
		attackLocation.y += TILE_SIZE;
		break;
	case LEFT:
		setFrames(ATTACK_LEFT_START, ATTACK_LEFT_END);
		attackLocation.x -= TILE_SIZE;
		break;
	case RIGHT:
		setFrames(ATTACK_RIGHT_START, ATTACK_RIGHT_END);
		attackLocation.x += TILE_SIZE;
		break;
	case UP_RIGHT: break;
	case UP_LEFT: break;
	case DOWN_RIGHT: break;
	case DOWN_LEFT: break;
	}

	/*NOTE TO CONSIDER:
		Do we have mechanics issues with being able to move and attack diagonally on a rectangular grid? 
			- I don't think so, our entities themselves aren't confined to the grid
		Is diagonal movement twice as fast as along the axes? 
			- Not anymore.
		Do diagonal attacks miss the squares to the sides? 
			- An attack should put a hit sphere on the map at the appropriate location (in front of the player) approximating a sword swipe
			- So it will be pretty accurate. We will need to implement this
	*/
}

void Hero::draw(const VECTOR2& Center)
{
	// Draw the main image
	Entity::draw(Center);

	// Draw armor on top of hero
	if(armor != 0)
	{
		VECTOR2 disp = Center - position;
		armor->setX(disp.x);
		armor->setCurrentFrame(getFrame());
		armor->setScale(DEFAULT_SCALE); // Probably unneccesary 
		armor->draw();
	}

	// Draw weapon here?
}