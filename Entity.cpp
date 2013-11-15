#include "Entity.h"

// References to other headers
#include "World.h"
#include "Effects.h"
#include "Projectiles.h"

using namespace entityNS;

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
	if(!active) return;
	lastPosition = position;
	updateImage(frameTime);
}

void Object::draw(VECTOR2& Center, DWORD color)
{
	if(!active) return;
	VECTOR2 diff = getPosition()*TILE_SIZE - Center;
	int X = diff.x + HSCREEN_WIDTH - 0.5*getImageWidth()*getImageScale();
	int Y = diff.y + HSCREEN_HEIGHT - 0.5*getImageHeight()*getImageScale();
	getImage()->setScale(DEFAULT_SCALE);
	setFrame();
	setImageX(X); setImageY(Y);
	Drawable::draw(color);
}

void Entity::initialize()
{
	Object::initialize();
	timeSinceInteract = 0;
	timeSinceAction = 0;
	speed = 1;
	facing = DOWN;
	SpellType = NOSPELL;
	_hasTarget = false;
	_frozen = false;
	_magicSight = false;
	freezeTime = 0;
}

inline void Object::handleSectors(World* W)
{
	VECTOR2 V = getPosition();
	int LX = (int)(getLastPosition().x+0.5);
	int LY = (int)(getLastPosition().y+0.5);
	int X = (int)(V.x+0.5), Y = (int)(V.y+0.5);
	if(LX != X || LY != Y)
	{
		W->getTile(LX,LY)->remove(this);
		W->getTile(X,Y)->add(this);
	}
}

void Object::newPosition(const VECTOR2& pos, World* W)
{
	Collidable::setPosition(pos);
	handleSectors(W);
}

void Entity::update(float frameTime, World* W)
{
	if(!active) return;
	timeSinceInteract += frameTime;
	timeSinceAction += frameTime;
	move(frameTime, W);
	magic += magicRecharge*frameTime;
	if(magic > maxMagic) magic = maxMagic;	
	if(!_frozen)
	{
		Object::update(frameTime, W);
		if(startMoving && W->canMoveHere(this, getPosition() + speed*velocity*frameTime))
		{
			W->collidesWithEffect(this, getPosition() + speed*velocity*frameTime);
			setPosition(getPosition() + speed*velocity*frameTime);
		}
		else standing();
		handleSectors(W);
	}
	else
	{
		freezeTime -= frameTime;
		if(freezeTime <= 0) _frozen = false;
	}
}

void Entity::draw(VECTOR2& Center, DWORD color)
{
	if(!_frozen) Object::draw(Center, color);
	else Object::draw(Center, graphicsNS::BLUE);
}

// Makes the entity move in the direction it is going
void Entity::move(float frameTime, World* W)
{
	switch(facing)
	{
	case UP:
		if(facing != lastDir || !moving) setFrames(WALKING_UP_START, WALKING_UP_END);
		velocity.y = -1;
		break;
	case DOWN:
		if(facing != lastDir || !moving) setFrames(WALKING_DOWN_START, WALKING_DOWN_END);
		velocity.y = 1;
		break;
	case LEFT:
		if(facing != lastDir || !moving) setFrames(WALKING_LEFT_START, WALKING_LEFT_END);
		velocity.x = -1;
		break;
	case RIGHT:
		if(facing != lastDir || !moving) setFrames(WALKING_RIGHT_START, WALKING_RIGHT_END);
		velocity.x = 1;
		break;	
	case UP_RIGHT:
		if(facing != lastDir || !moving) setFrames(WALKING_UP_RIGHT_START, WALKING_UP_RIGHT_END);
		velocity.y = -DIAG_MULT;
		if (!W->canMoveHere(this, getPosition()+speed*velocity*frameTime)) velocity.y=0;
		velocity.x = DIAG_MULT;
		if (!W->canMoveHere(this, getPosition()+speed*velocity*frameTime)) velocity.x=0;
		break;
	case UP_LEFT:
		if(facing != lastDir || !moving) setFrames(WALKING_UP_LEFT_START, WALKING_UP_LEFT_END);	
		velocity.y = -DIAG_MULT;
		if (!W->canMoveHere(this, getPosition()+speed*velocity*frameTime)) velocity.y=0;
		velocity.x = -DIAG_MULT;
		if (!W->canMoveHere(this, getPosition()+speed*velocity*frameTime)) velocity.x=0;
		break;
	case DOWN_RIGHT:
		if(facing != lastDir || !moving) setFrames(WALKING_DOWN_RIGHT_START, WALKING_DOWN_RIGHT_END);
		velocity.y = DIAG_MULT;
		if (!W->canMoveHere(this, getPosition()+speed*velocity*frameTime)) velocity.y=0;
		velocity.x = DIAG_MULT;
		if (!W->canMoveHere(this, getPosition()+speed*velocity*frameTime)) velocity.x=0;
		break;
	case DOWN_LEFT:
		if(facing != lastDir || !moving) setFrames(WALKING_DOWN_LEFT_START, WALKING_DOWN_LEFT_END);	
		velocity.y = DIAG_MULT;
		if (!W->canMoveHere(this, getPosition()+speed*velocity*frameTime)) velocity.y=0;
		velocity.x = -DIAG_MULT;
		if (!W->canMoveHere(this, getPosition()+speed*velocity*frameTime)) velocity.x=0;
		break;
	case NONE:
		standing();
		break;
	}

	lastDir = facing;
	moving = true;
}

// Interact with whatever is in front of the entity
void Entity::interact(World* W)
{
	if(timeSinceInteract < INTERACTIONDELAY) return;
	timeSinceInteract = 0;
	float x = getPosition().x + 0.5, y = getPosition().y + 0.5;
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

// Tell an entity to start moving in a direction
void Entity::go(DIR face)
{
	startMoving=true;
	facing=face;
}

// Tell an entity to stand
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

void Entity::receiveDamage(Projectile* p)
{
	kill(); // Obviously, this is temporary
}

bool HandleCollision(Collidable* A, Collidable* B)
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
			break;
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
			break;
	}
	D = D3DXVec2Dot(&diff,&diff);
	if(D < R*R) return true;
	return false;
}