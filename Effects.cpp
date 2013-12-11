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
	if(_hidden || _invisible || noImage()) return;
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

void DamageEffect::effect(Object* E, World* W)
{
	if(E->getType() != OBJECT)
	{
		Entity* Ent = reinterpret_cast<Entity*>(E);
		if(Ent->getTeam() != team) Ent->damage(damage);
	}
}

void SwordSwing::effect(Object* E, World* W)
{
	if(E->getType() != OBJECT)
	{
		Entity* Ent = reinterpret_cast<Entity*>(E);
		if(Ent->getTeam() != team)
		{// Check for collision
			VECTOR2 disp = Ent->getPosition() - getPosition();
			float theta = atan2(disp.y, disp.x);
			float D = D3DXVec2Length(&disp);
			float diff = radianDiff(theta, orient);

			if(D < radius && diff < deltaTheta) Ent->damage(damage);
		}
	}
}