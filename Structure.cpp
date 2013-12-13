#include "Structure.h"
#include "World.h"
#include "WorldInterface.h"
#include "hero.h"

void Structure::draw(VECTOR2 Center)
{
	if(noImage()) return; // if the image is null
	VECTOR2 diff = (TL - Center)*TILE_SIZE;
	int X = diff.x + HSCREEN_WIDTH;
	int Y = diff.y + HSCREEN_HEIGHT;
	setFrame();
	setScale(DEFAULT_SCALE);
	setImageX(X); setImageY(Y);
	Drawable::draw();
}

void Structure::update(float frameTime)
{
	updateImage(frameTime);}


void Portal::interact(Entity* E)
{
	if (out == WI->getBar2())
	{
		WI->getAudio()->stopCue(SOUTHFALL_THEME);
		WI->getAudio()->stopCue(BATTLE);
		WI->getAudio()->playCue(BAR_BACKGROUND);
	}
	if (out == WI->getMain() && E->getWorld() == WI->getBar2())
	{	
		WI->getAudio()->stopCue(BAR_BACKGROUND);
		WI->getAudio()->playCue(BATTLE);

		vector<string> text; text.push_back("Help! Our leader is being attacked!");
		WI->getTextBox()->setText(text);
		WI->getTextBox()->setActive(true);		
	}
	Hero* idiot = dynamic_cast<Hero*>(E);
	if (out == WI->getMain() && (Entity::killCount < GOBLIN_WAVE_COUNT) && idiot->hasAddedSword)
	{
		WI->getAudio()->playCue(BATTLE);
		WI->getAudio()->stopCue(SOUTHFALL_THEME);
	}
	
	E->getWorld()->removeEntity(E);
	E->setWorld(out);
	E->setPosition(vOut);
	out->addEntity(E);	
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