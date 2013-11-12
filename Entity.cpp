#include "Entity.h"

// References to other headers
#include "World.h"

void Drawable::initialize()
{
	_frame = 0;
	_imageTime = 0;
	_imageDelay = DEFAULT_FRAME_DELAY;
	_startFrame = 0;
	_endFrame = 0;
}

void Drawable::updateImage(float frameTime)
{
	_imageTime += frameTime;
	if(_imageTime > _imageDelay)
	{
		_imageTime = 0;
		++_frame;
		if(_frame > _endFrame) _frame = _startFrame;
	}
}

void Object::initialize()
{
	Drawable::initialize();
}

void Object::update(float frameTime, World* W)
{
	updateImage(frameTime);
}

void Entity::initialize()
{
	Object::initialize();
	timeSinceInteract = 0;
	speed = 0;
	facing = DOWN;
}

void Entity::update(float frameTime, World* W)
{
	timeSinceInteract += frameTime;
	move(frameTime, W);

	updateImage(frameTime);
	if(startMoving && W->canMoveHere(this, position + velocity*frameTime))
		setPosition(position + velocity*frameTime);
	else standing();
}

void Entity::draw(const VECTOR2& Center)
{
	
	VECTOR2 diff = position*TILE_SIZE - Center;
	int X = diff.x + HSCREEN_WIDTH - HTILE_SIZE;
	int Y = diff.y + HSCREEN_HEIGHT - HTILE_SIZE;
	getImage()->setScale(DEFAULT_SCALE);
	setFrame();
	setImageX(X); setImageY(Y);
	Drawable::draw();
}

void Entity::move(float frameTime, World* W)
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
		if (!W->canMoveHere(this, position+velocity*frameTime)) velocity.y=0;
		velocity.x = DIAG_MULT * speed;
		if (!W->canMoveHere(this, position+velocity*frameTime)) velocity.x=0;
		break;
	case UP_LEFT:
		if(facing != lastDir || !moving) setFrames(WALKING_UP_LEFT_START, WALKING_UP_LEFT_END);	
		velocity.y = DIAG_MULT * -1 * speed;
		if (!W->canMoveHere(this, position+velocity*frameTime)) velocity.y=0;
		velocity.x = -DIAG_MULT * speed;
		if (!W->canMoveHere(this, position+velocity*frameTime)) velocity.x=0;
		break;
	case DOWN_RIGHT:
		if(facing != lastDir || !moving) setFrames(WALKING_DOWN_RIGHT_START, WALKING_DOWN_RIGHT_END);
		velocity.y = DIAG_MULT * speed;
		if (!W->canMoveHere(this, position+velocity*frameTime)) velocity.y=0;
		velocity.x = DIAG_MULT * speed;
		if (!W->canMoveHere(this, position+velocity*frameTime)) velocity.x=0;
		break;
	case DOWN_LEFT:
		if(facing != lastDir || !moving) setFrames(WALKING_DOWN_LEFT_START, WALKING_DOWN_LEFT_END);	
		velocity.y = DIAG_MULT * speed;
		if (!W->canMoveHere(this, position+velocity*frameTime)) velocity.y=0;
		velocity.x = -DIAG_MULT * speed;
		if (!W->canMoveHere(this, position+velocity*frameTime)) velocity.x=0;
		break;
	case NONE:
		standing();
		break;
	}

	lastDir = facing;
	moving = true;
}

void Entity::interact(World* W)
{
	if(timeSinceInteract < INTERACTIONDELAY) return;
	timeSinceInteract = 0;
	float x = position.x + 0.5, y = position.y + 0.5;
	float range = 0.6;
	switch(facing)
	{
	case UP:
		if(0<y)
		{
			W->getTile(x,y-range)->interact(this);
		}
		break;
	case DOWN:
		if(y+range<W->getHeight())
		{
			W->getTile(x,y+range)->interact(this);
		}
		break;
	case RIGHT:
		if(x+range<W->getWidth())
		{
			W->getTile(x+range,y)->interact(this);
		}
		break;
	case LEFT:
		if(0<x)
		{
			W->getTile(x-range,y)->interact(this);
		}
		break;
	}
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

bool HandleCollision(Object* A, Object* B)
{
	float D, R;
	VECTOR2 diff = A->position - B->position;
	switch(A->collisionType)
	{
		case CIRCLE:
			switch (B->collisionType)
			{
			case CIRCLE:
				R = A->radius+B->radius;
				break;
			case POINTCOLLISION:
				R = A->radius;
				break;
			}
		case POINTCOLLISION:
			switch (B->collisionType)
			{
			case CIRCLE:
				R = A->radius+B->radius;
				break;
			case POINTCOLLISION:
				return A->position == B->position;
				break;
			}
	}
	D = D3DXVec2Dot(&diff,&diff);
	if(D < R*R) return true;
	return false;
}