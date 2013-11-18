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
	VECTOR2 diff = (getPosition() - Center)*TILE_SIZE;
	int X = diff.x + HSCREEN_WIDTH - 0.5*getImageWidth()*getImageScale();
	int Y = diff.y + HSCREEN_HEIGHT - 0.75*getImageHeight()*getImageScale();
	getImage()->setScale(DEFAULT_SCALE);
	setFrame();
	setImageX(X); setImageY(Y);
	Drawable::draw();
}

void ImpedeEffect::effect(Object* E, World* W)
{
	E->stop();
}

void QuickPortal::effect(Object* E, World* W)
{
	E->newPosition(exit, W);
}

void QuickPortal::draw(VECTOR2 Center)
{
	if(_invisible) return;
	// Draw entrance portal
	VECTOR2 diff = (getPosition() - Center)*TILE_SIZE;
	int X = diff.x + HSCREEN_WIDTH - 0.5*getImageWidth()*getImageScale();
	int Y = diff.y + HSCREEN_HEIGHT - 0.5*getImageHeight()*getImageScale();
	getImage()->setScale(DEFAULT_SCALE);
	setFrame();
	setImageX(X); setImageY(Y);
	Drawable::draw();
	// Draw exit portal
	diff = (exit - Center)*TILE_SIZE;
	X = diff.x + HSCREEN_WIDTH - 0.5*getImageWidth()*getImageScale();
	Y = diff.y + HSCREEN_HEIGHT - 0.5*getImageHeight()*getImageScale();
	exitImage->setScale(DEFAULT_SCALE);
	exitImage->setX(X); exitImage->setY(Y);
	exitImage->draw();
}

void Damage::draw(VECTOR2 Center)
{

}

void Damage::effect(Object* E, World* W)
{

}