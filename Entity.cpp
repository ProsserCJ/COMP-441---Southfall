#include "Entity.h"

// References to other headers
#include "World.h"

void Entity::initialize()
{
	frame = 0;
	_imageTime = 0;
	_imageDelay = DEFAULT_FRAME_DELAY;
	startFrame = 0;
	endFrame = 0;
}

void Entity::update(float frameTime, World* W)
{
	updateImage(frameTime);
	if(W->canMoveHere(position + velocity*frameTime, radius) && startMoving)
		move(frameTime);
}

void Entity::draw(const VECTOR2& Center)
{
	if(_imageTime > _imageDelay)
	{
		_imageTime = 0;
		++frame;
		if(frame > endFrame) frame = startFrame;
	}
	VECTOR2 diff = position*TILE_SIZE - Center;
	int X = diff.x + HSCREEN_WIDTH - HTILE_SIZE;
	int Y = diff.y + HSCREEN_HEIGHT - HTILE_SIZE;
	image->setScale(DEFAULT_SCALE);
	image->setCurrentFrame(frame);
	image->setX(X); image->setY(Y);
	image->draw();
}

void Entity::move(float frameTime)
{
	switch(facing)
	{
	case UP:
		if(facing != lastDir || !moving) setFrames(WALKING_UP_START, WALKING_UP_END);
		velocity.y = -speed;
		break;

	case DOWN:
		if(facing != lastDir || !moving) setFrames(WALKING_DOWN_START, WALKING_DOWN_END);
		velocity.y = speed;
		break;

	case LEFT:
		if(facing != lastDir || !moving) setFrames(WALKING_LEFT_START, WALKING_LEFT_END);
		velocity.x = -speed;
		break;

	case RIGHT:
		if(facing != lastDir || !moving) setFrames(WALKING_RIGHT_START, WALKING_RIGHT_END);
		velocity.x = speed;
		break;
	
	case UP_RIGHT:
		if(facing != lastDir || !moving) setFrames(WALKING_UP_RIGHT_START, WALKING_UP_RIGHT_END);
		velocity.y = -DIAG_MULT * speed;
		velocity.x = DIAG_MULT * speed;
		break;

	case UP_LEFT:
		if(facing != lastDir || !moving) setFrames(WALKING_UP_LEFT_START, WALKING_UP_LEFT_END);	
		velocity.y = DIAG_MULT * -1 * speed;	
		velocity.x = -DIAG_MULT * speed;
		break;

	case DOWN_RIGHT:
		if(facing != lastDir || !moving) setFrames(WALKING_DOWN_RIGHT_START, WALKING_DOWN_RIGHT_END);
		velocity.y = DIAG_MULT * speed;
		velocity.x = DIAG_MULT * speed;
		break;

	case DOWN_LEFT:
		if(facing != lastDir || !moving) setFrames(WALKING_DOWN_LEFT_START, WALKING_DOWN_LEFT_END);	
		velocity.y = DIAG_MULT * speed;
		velocity.x = -DIAG_MULT * speed;
		break;
	case NONE:
		standing();
		break;
	}

	lastDir = facing;
	moving = true;
	setPosition(position + velocity*frameTime);
}

void Entity::go(DIR face)
{
	startMoving=true;
	facing=face;
}

void Entity::standing()
{
	startMoving = false;
	moving=false;
	setStandingImage();
}

void Entity::setStandingImage()
{
	switch(facing)
	{
		case UP: setStationaryFrame(FACING_UP); break;
		case DOWN: setStationaryFrame(FACING_DOWN); break;
		case LEFT: setStationaryFrame(FACING_LEFT); break;
		case RIGHT: setStationaryFrame(FACING_RIGHT); break;
		case UP_RIGHT: setStationaryFrame(FACING_UP_RIGHT); break;
		case UP_LEFT: setStationaryFrame(FACING_UP_LEFT); break;
		case DOWN_RIGHT: setStationaryFrame(FACING_DOWN_RIGHT); break;
		case DOWN_LEFT: setStationaryFrame(FACING_DOWN_LEFT); break;
	}
}

