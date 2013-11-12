/****************************************************
Hero implementation file

Last modified: 11/5/2013

******************************************************/

#include "hero.h"
#include "World.h"

using namespace heroNS;

void Hero::initialize()
{
	armor = 0;
	setFrameDelay(DEFAULT_FRAME_DELAY);
	speed = HERO_SPEED;

	SpellType = PORTALTRAP; // For testing purposes
};

void Hero::update(float frameTime, World* W)
{
	velocity = ZERO;
	DIR dir = NONE;
	Entity* NPCFacing = 0;
	if (input->isKeyDown(WKEY))
    {
            if (input->isKeyDown(DKEY))			go(UP_RIGHT);
            else if (input->isKeyDown(AKEY))	go(UP_LEFT);        
            else								go(UP);
    }        
    else if (input->isKeyDown(SKEY))
    {
            if (input->isKeyDown(DKEY))			go(DOWN_RIGHT);
            else if (input->isKeyDown(AKEY))	go(DOWN_LEFT);        
            else								go(DOWN);
    }
    else if (input->isKeyDown(AKEY))			go(LEFT);
    else if (input->isKeyDown(DKEY))			go(RIGHT);    
	else										standing();  
	
	// Test Effects

	/*if(timeSinceAction > HEROACTIONDELAY && input->getMouseLButton())
	{
		timeSinceAction = 0;
		int X = input->getMouseX();
		int Y = input->getMouseY();
		VECTOR2 mouse(X,Y);

		VECTOR2 target = getPosition()+(mouse-HSCREEN)*INVTILE_SIZE;
		W->addEffect(new ImpedeEffect(target, 0.2));
	}*/

	///////////////

	if (input->wasKeyPressed('E'))
	{
		if (textbox->isActive())
		{
			audio->playCue(SELECT);
			textbox->next();
		}
		else
		{
			NPCFacing = W->getNPCFacing(getPosition(), facing);
			if (NPCFacing)
			{
				audio->playCue(SELECT);
				turnToPlayer(NPCFacing);				
				textbox->setText(reinterpret_cast<NPC*>(NPCFacing));
				textbox->setActive(true);
			}
			else interact(W);
		}
	}

	Entity::update(frameTime, W);

	if(startMoving && !W->canMoveHere(this, getPosition() + velocity*frameTime))
	{
		audio->playCue(COLLIDE);
	}
}

void Hero::turnToPlayer(Entity* npc)
{
	switch(facing){
	case UP_RIGHT:
	case UP_LEFT:
	case UP: npc->setDir(DOWN); break;
	case DOWN_RIGHT:
	case DOWN_LEFT:
	case DOWN: npc->setDir(UP); break;
	case LEFT: npc->setDir(RIGHT); break;
	case RIGHT: npc->setDir(LEFT); break;
	};
	npc->standing();
	reinterpret_cast<NPC*>(npc)->setPaused(true);
}


void Hero::attack()
{
	// This function will need tweaking
	//Indeed
	VECTOR2 attackLocation(getPosition());
	switch(facing)
	{
	case UP:
		setFrames(ATTACK_UP_START, ATTACK_UP_END);
		attackLocation.y -= TILE_SIZE;
		break;
	case DOWN:
		setFrames(ATTACK_DOWN_START, ATTACK_DOWN_END);
		attackLocation.y += TILE_SIZE;
		break;
	case LEFT:
		setFrames(ATTACK_LEFT_START, ATTACK_LEFT_END);
		attackLocation.x -= TILE_SIZE;
		break;
	case RIGHT:
		setFrames(ATTACK_RIGHT_START, ATTACK_RIGHT_END);
		attackLocation.x += TILE_SIZE;
		break;
	case UP_RIGHT: break;
	case UP_LEFT: break;
	case DOWN_RIGHT: break;
	case DOWN_LEFT: break;
	}
}

void Hero::draw(const VECTOR2& Center)
{
	// Draw the main image
	Entity::draw(Center);

	// Draw armor on top of hero
	if(armor != 0)
	{
		VECTOR2 disp = Center - getPosition();
		armor->setX(disp.x);
		armor->setCurrentFrame(getFrame());
		armor->setScale(DEFAULT_SCALE); // Probably unneccesary 
		armor->draw();
	}

	// Draw weapon here?
}