#include "Structure.h"

void Structure::draw(VECTOR2 Center)
{
	if(!image) return; // if the image is null
	VECTOR2 diff = TL*TILE_SIZE - Center;
	int X = diff.x + HSCREEN_WIDTH - HTILE_SIZE;
	int Y = diff.y + HSCREEN_HEIGHT - HTILE_SIZE;
	image->setScale(DEFAULT_SCALE);
	image->setX(X); image->setY(Y);
	image->draw();
}

void Door::interact()
{
	open++;
	open %= 2;
	image->setCurrentFrame(open);
}