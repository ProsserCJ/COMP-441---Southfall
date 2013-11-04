/****************************************************
Hero implementation file

Last modified: 11/4/2013

******************************************************/

#include "hero.h"
using namespace heroNS;

void Hero::attack(DIR d)
{
	VECTOR2 attackLocation(position);
	switch(d)
	{
	case UP:
		image->setFrames(HERO_SWINGING_UP_START, HERO_SWINGING_UP_END);
		attackLocation.y -= TILE_SIZE;
		break;
	case DOWN:
		image->setFrames(HERO_SWINGING_DOWN_START, HERO_SWINGING_DOWN_END);
		attackLocation.y += TILE_SIZE;
		break;
	case LEFT:
		image->setFrames(HERO_SWINGING_LEFT_START, HERO_SWINGING_LEFT_END);
		attackLocation.x -= TILE_SIZE;
		break;
	case RIGHT:
		image->setFrames(HERO_SWINGING_RIGHT_START, HERO_SWINGING_RIGHT_END);
		attackLocation.x += TILE_SIZE;
		break;

	case UP_RIGHT:
	case UP_LEFT:
	case DOWN_RIGHT:
	case DOWN_LEFT: break;
	}

	/*NOTE TO CONSIDER:
		Do we have mechanics issues with being able to attack diagonally on a rectangular grid?
		If diagonal attacks can hit two squares, regular attacks are obsolete.
		How should diagonal attacks work?
	*/
}


void Hero::move(DIR d)
{
	VECTOR2 newLocation(position);
	switch(d)
	{
	case UP:
		image->setFrames(HERO_WALKING_UP_START, HERO_WALKING_UP_END);
		newLocation.y -= TILE_SIZE;
		break;
	case DOWN:
		image->setFrames(HERO_WALKING_DOWN_START, HERO_WALKING_DOWN_END);
		newLocation.y += TILE_SIZE;
		break;
	case LEFT:
		image->setFrames(HERO_WALKING_LEFT_START, HERO_WALKING_LEFT_END);
		newLocation.x -= TILE_SIZE;
		break;
	case RIGHT:
		image->setFrames(HERO_WALKING_RIGHT_START, HERO_WALKING_RIGHT_END);
		newLocation.x += TILE_SIZE;
		break;

	case UP_RIGHT:
	case UP_LEFT:
	case DOWN_RIGHT:
	case DOWN_LEFT: break;
	}

	setPosition(newLocation);
}
