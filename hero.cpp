/****************************************************
Hero implementation file

Last modified: 11/4/2013

******************************************************/

#include "hero.h"
using namespace heroNS;


bool Hero::initialize(Game *g, int width, int height, int ncols, TextureManager *textureM){
	input = g->getInput();
	return image->initialize(g->getGraphics(),width,height,ncols,textureM);	
};


void Hero::update(float frameTime){
	image->update(frameTime);

	velocity = ZERO; //reset velocity to start each frame;
	
	//determine direction to move based on keypress
	DIR dir = NONE;
	if (input->isKeyDown('W')){
		dir = UP;
		if (input->isKeyDown('D')) dir = UP_RIGHT;
		else if (input->isKeyDown('A')) dir = UP_LEFT;		
	}	
	else if (input->isKeyDown('S')){
		dir = DOWN;
		if (input->isKeyDown('D')) dir = DOWN_RIGHT;
		else if (input->isKeyDown('A')) dir = DOWN_LEFT;	
	}
	else if (input->isKeyDown('A')) dir = LEFT;
	else if (input->isKeyDown('D')) dir = RIGHT;
	else setDirectionFacing();

	move(dir, frameTime);

	//attack is space key is pressed
	if (input->isKeyDown(SPACE_KEY)) attack();
}

void Hero::move(DIR d, float frameTime)
{
	facing = d;	
	switch(d)
	{
	case UP:
		image->setFrames(HERO_WALKING_UP_START, HERO_WALKING_UP_END);	
		velocity.y = frameTime * HERO_SPEED * -1;	
		break;
	case DOWN:
		image->setFrames(HERO_WALKING_DOWN_START, HERO_WALKING_DOWN_END);
		velocity.y = frameTime * HERO_SPEED;
		break;
	case LEFT:
		image->setFrames(HERO_WALKING_LEFT_START, HERO_WALKING_LEFT_END);
		velocity.x = frameTime * HERO_SPEED * -1;
		break;
	case RIGHT:
		image->setFrames(HERO_WALKING_RIGHT_START, HERO_WALKING_RIGHT_END);
		velocity.x = frameTime * HERO_SPEED;
		break;

	case UP_RIGHT:
	case UP_LEFT:
	case DOWN_RIGHT:
	case DOWN_LEFT: break;
	}

	setPosition(position + velocity);
}

void Hero::attack()
{
	VECTOR2 attackLocation(position);
	switch(facing)
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

void Hero::setDirectionFacing(){
	switch(facing){
	case UP: image->setCurrentFrame(HERO_FACING_UP); break;
	case DOWN: image->setCurrentFrame(HERO_FACING_DOWN); break;
	case LEFT: image->setCurrentFrame(HERO_FACING_LEFT); break;
	case RIGHT: image->setCurrentFrame(HERO_FACING_RIGHT); break;
	case UP_RIGHT: image->setCurrentFrame(HERO_FACING_UP_RIGHT); break;
	case UP_LEFT: image->setCurrentFrame(HERO_FACING_UP_LEFT); break;
	case DOWN_RIGHT: image->setCurrentFrame(HERO_FACING_DOWN_RIGHT); break;
	case DOWN_LEFT: image->setCurrentFrame(HERO_FACING_DOWN_LEFT); break;
	}
}