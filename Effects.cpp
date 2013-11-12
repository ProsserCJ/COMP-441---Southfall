#include "Effects.h"

#include "World.h"
#include "Entity.h"

void Effect::update(float frameTime, World* W)
{
	updateImage(frameTime);
	time += frameTime;
	if(_timed && time > maxTime) _done = true;
}

void Effect::draw(VECTOR2 Center)
{
	if(_invisible) return;
	VECTOR2 diff = getPosition()*TILE_SIZE - Center;
	int X = diff.x + HSCREEN_WIDTH - HTILE_SIZE;
	int Y = diff.y + HSCREEN_HEIGHT - HTILE_SIZE;
	getImage()->setScale(DEFAULT_SCALE);
	setFrame();
	setImageX(X); setImageY(Y);
	Drawable::draw();
}

void ImpedeEffect::effect(Object* E)
{
	E->stop();
}

void PortalTrapEffect::effect(Object* E)
{
	E->setPosition(exit);
}

void PortalTrapEffect::draw(VECTOR2 Center)
{
	if(_invisible) return;
	// Draw entrance portal
	VECTOR2 diff = getPosition()*TILE_SIZE - Center;
	int X = diff.x + HSCREEN_WIDTH - HTILE_SIZE;
	int Y = diff.y + HSCREEN_HEIGHT - HTILE_SIZE;
	getImage()->setScale(DEFAULT_SCALE);
	setFrame();
	setImageX(X); setImageY(Y);
	Drawable::draw();
	// Draw exit portal
	diff = exit*TILE_SIZE - Center;
	X = diff.x + HSCREEN_WIDTH - HTILE_SIZE;
	Y = diff.y + HSCREEN_HEIGHT - HTILE_SIZE;
	exitImage->setScale(DEFAULT_SCALE);
	exitImage->setX(X); exitImage->setY(Y);
	exitImage->draw();
}