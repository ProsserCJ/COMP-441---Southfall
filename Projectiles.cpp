#include "Projectiles.h"

#include "World.h"

void Projectile::update(float frameTime, World* W)
{
	if(!W->collidesWithTile(this, getPosition() + velocity*frameTime*speed))
	{
		W->collidesWithEffect(this, getPosition() + velocity*frameTime*speed);
		traveled += frameTime*speed;
		setPosition(getPosition() + velocity*frameTime*speed);
		Object::update(frameTime, W);
		handleSectors(W);
	}
	else active = false;
	if(range < traveled) active = false;
}

void Projectile::end(World* W)
{
	Explosion* Exp = new Explosion(position, FIREEXPLOSIONDAMAGE, 0.4f, team, &W->getImageLibrary()->ExplosionIM, FIREEXPLOSIONTIME);
	Exp->setSingleLoop(0, 3, FIREEXPLOSIONTIME/4.0f);
	if(type == PROJ_FIREBALL) W->addEffect(Exp);
}