#include "bricks.h"

//=============================================================================
// default constructor
//=============================================================================
Brick::Brick() : Entity()
{
    spriteData.width = brickNS::WIDTH;           
    spriteData.height = brickNS::HEIGHT;
    spriteData.x = brickNS::X;                   
    spriteData.y = brickNS::Y;
    spriteData.rect.bottom = brickNS::HEIGHT/2;    
    spriteData.rect.right = brickNS::WIDTH;
    velocity.x = 0;                             
    velocity.y = 0;                             
    startFrame = 0;              
    endFrame     = 0;              
    currentFrame = startFrame;
    radius = brickNS::WIDTH/2.0;                 // collision radius
    collision = false;
    collisionType =entityNS::BOX;
    target = false;
	edge.bottom = -brickNS::HEIGHT/2;
	spriteData.scale = 1;
	active = true;

}

bool Brick::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Brick::setInvisible()
{
	Image::setVisible(false);
	active = false;
}

void Brick::setVisible()
{
	Image::setVisible(true);
	active = true;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Brick::update(float frameTime)
{
    Entity::update(frameTime);
}

	