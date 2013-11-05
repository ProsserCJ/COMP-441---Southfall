/****************************************************
Hero implementation file

Last modified: 11/4/2013

******************************************************/

#include "hero.h"
using namespace heroNS;


void Hero::initialize(Image* image)
{
	this->image = image;
	armor = 0;
	image->setFrameDelay(.25);
	image->setLoop(true);
};


void Hero::update(float frameTime)
{
	updateImage(frameTime);

	velocity = ZERO; //reset velocity to start each frame;
	
	DIR dir = NONE;
	
	if (input->isKeyDown(WKEY))
        {
                if (input->isKeyDown(DKEY))                        go(UP_RIGHT);
                else if (input->isKeyDown(AKEY))        go(UP_LEFT);        
                else                                                                go(UP);
        }        
        else if (input->isKeyDown(SKEY))
        {
                if (input->isKeyDown(DKEY))                        go(DOWN_RIGHT);
                else if (input->isKeyDown(AKEY))        go(DOWN_LEFT);        
                else                                                                go(DOWN);
        }
        else if (input->isKeyDown(AKEY))                go(LEFT);
        else if (input->isKeyDown(DKEY))                go(RIGHT);
        else                                                                        standing();

	if(startMoving) move(frameTime);

	// attack is space key is pressed
	// We should change this to the mouse at some point
	//if (input->isKeyDown(SPACE_KEY)) attack();
}


void Hero::go(DIR face)
{
	startMoving=true;
	facing=face;
}


void Hero::move(float frameTime)
{
	switch(facing)
	{
	case UP:
		if(facing != lastDir || !moving) setFrames(HERO_WALKING_UP_START, HERO_WALKING_UP_END);
		velocity.y = -HERO_SPEED;
		break;

	case DOWN:
		if(facing != lastDir || !moving) setFrames(HERO_WALKING_DOWN_START, HERO_WALKING_DOWN_END);
		velocity.y = HERO_SPEED;
		break;

	case LEFT:
		if(facing != lastDir || !moving) setFrames(HERO_WALKING_LEFT_START, HERO_WALKING_LEFT_END);
		velocity.x = -HERO_SPEED;
		break;

	case RIGHT:
		if(facing != lastDir || !moving) setFrames(HERO_WALKING_RIGHT_START, HERO_WALKING_RIGHT_END);
		velocity.x = HERO_SPEED;
		break;
	
	case UP_RIGHT:
		if(facing != lastDir || !moving) setFrames(HERO_WALKING_UP_RIGHT_START, HERO_WALKING_UP_RIGHT_END);
		velocity.y = -0.707f * HERO_SPEED;
		velocity.x = 0.707f * HERO_SPEED;
		break;

	case UP_LEFT:
		if(facing != lastDir || !moving) setFrames(HERO_WALKING_UP_LEFT_START, HERO_WALKING_UP_LEFT_END);	
		velocity.y = HERO_SPEED * -1 * 0.707f;	
		velocity.x = HERO_SPEED * -1 * 0.707f;
		break;

	case DOWN_RIGHT:
		if(facing != lastDir || !moving) setFrames(HERO_WALKING_DOWN_RIGHT_START, HERO_WALKING_DOWN_RIGHT_END);
		velocity.y = HERO_SPEED * 0.707f;
		velocity.x = HERO_SPEED * 0.707f;
		break;

	case DOWN_LEFT:
		if(facing != lastDir || !moving) setFrames(HERO_WALKING_DOWN_LEFT_START, HERO_WALKING_DOWN_LEFT_END);	
		velocity.y = HERO_SPEED * 0.707f;
		velocity.x = HERO_SPEED * -1 * 0.707f;
		break;
	case NONE:
		standing();
		break;
	}

	lastDir = facing;
	moving = true;
	setPosition(position + velocity*frameTime);
}

void Hero::attack()
{
	// This function will need tweaking
	//Indeed
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
		armor->setX(disp.x); image->setY(disp.y);
		armor->setCurrentFrame(frame);
		armor->setScale(DEFAULT_SCALE); // Probably unneccesary 
		armor->draw();
	}

	// Draw weapon here?
}

void Hero::standing(){
	startMoving = false;
	moving=false;
	setStandingImage();
}

void Hero::setStandingImage()
{
	switch(facing)
	{
		case UP: setStationaryFrame(HERO_FACING_UP); break;
		case DOWN: setStationaryFrame(HERO_FACING_DOWN); break;
		case LEFT: setStationaryFrame(HERO_FACING_LEFT); break;
		case RIGHT: setStationaryFrame(HERO_FACING_RIGHT); break;
		case UP_RIGHT: setStationaryFrame(HERO_FACING_UP_RIGHT); break;
		case UP_LEFT: setStationaryFrame(HERO_FACING_UP_LEFT); break;
		case DOWN_RIGHT: setStationaryFrame(HERO_FACING_DOWN_RIGHT); break;
		case DOWN_LEFT: setStationaryFrame(HERO_FACING_DOWN_LEFT); break;
	}
}