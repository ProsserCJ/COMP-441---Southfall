#include "Projectiles.h"

#include "World.h"

void Projectile::update(float frameTime, World* W)
{
	if(!W->collidesWithTile(this, getPosition() + velocity*frameTime*speed))
	{
		traveled += frameTime*speed;
		setPosition(getPosition() + velocity*frameTime*speed);
		Object::update(frameTime, W);
	}
	else active = false;
	if(range < traveled) active = false;
}

void Projectile::interact(World* W)
{

}