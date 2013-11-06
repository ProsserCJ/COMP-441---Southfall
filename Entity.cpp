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

void Entity::go(DIR face)
{
	startMoving=true;
	facing=face;
}

void Entity::standing(){
	startMoving = false;
	moving=false;
	setStandingImage();
}

