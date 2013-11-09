#include "Structure.h"

void Structure::draw(VECTOR2 Center)
{
	if(noImage()) return; // if the image is null
	VECTOR2 diff = TL*TILE_SIZE - Center;
	int X = diff.x + HSCREEN_WIDTH - HTILE_SIZE;
	int Y = diff.y + HSCREEN_HEIGHT - HTILE_SIZE;
	setFrame();
	setScale(DEFAULT_SCALE);
	setImageX(X); setImageY(Y);
	Drawable::draw();
}

void Structure::update(float frameTime)
{
	updateImage(frameTime);
}

void Portal::interact(Entity* E)
{
	E->setWorld(out);
	E->setPosition(vOut);
}

void Door::draw(VECTOR2 Center)
{
	if(noImage()) return;
	setFrame(open);
	Structure::draw(Center);
}

void Door::interact(Entity*)
{
	open++;
	open %= 2;
	setFrame(open);
}