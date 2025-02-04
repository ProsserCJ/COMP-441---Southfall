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
	hasSword = 0;
	hasFireball = 0;
	hasAddedSword = 0;
	hasAddedFireball = 0;
	//SpellType = PORTALTRAP; // For testing purposes
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
	if(input->wasKeyPressed('E'))
	{// Interaction key
		NPCFacing = W->getNPCFacing(getPosition(), facing);
		if (NPCFacing && NPCFacing->getType() == NPCTYPE)
		{
			audio->playCue(SELECT);
			turnToPlayer(NPCFacing);
			if(NPCFacing->item == "sword")
				hasSword = true;
			else if(NPCFacing->item == "fireball")
				hasFireball = true;
			textbox->setText(reinterpret_cast<NPC*>(NPCFacing));
			textbox->setActive(true);
			if (NPCFacing->getTalkSound() == LIFE_RESTORE)
			{
				audio->playCue(LIFE_RESTORE);
				setHP(HERO_HP);
			}			
		}
		else interact(W);
	}

	Entity::update(frameTime, W);

	if(startMoving && !W->canMoveHere(this, getPosition() + speed*velocity*frameTime))
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

void Hero::draw(VECTOR2& Center)
{
	// Draw the main image
	Object::draw(Center);

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

void Hero::reset()
{
	setHP(maxHP);
	//setPosition(VECTOR2(102.5,96.5));
	setPosition(VECTOR2(11.5,7));
	setActive(true);
	setDir(UP);
	getWorld()->addEntity(this);
}