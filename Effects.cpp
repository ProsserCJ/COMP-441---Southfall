#include "Effects.h"

#include "World.h"

void Effect::update(float frameTime, World* W)
{
	updateImage(frameTime);
	time += frameTime;
	if(_timed && time > maxTime) _done = true;
}

void ImpeadEffect::effect(Object* E)
{
	E->stop();
}