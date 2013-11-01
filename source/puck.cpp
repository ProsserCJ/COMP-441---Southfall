#include "puck.h"

//=============================================================================
// default constructor
//=============================================================================
Puck::Puck() : Entity()
{
    spriteData.width = puckNS::WIDTH;           
    spriteData.height = puckNS::HEIGHT;
    spriteData.x = puckNS::X;                   
    spriteData.y = puckNS::Y;
	setPosition(VECTOR2(puckNS::X, puckNS::Y));
    spriteData.rect.bottom = puckNS::HEIGHT/2;    // rectangle to select parts of an image
    spriteData.rect.right = puckNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    startFrame = 0;              // first frame of ship animation
    endFrame     = 0;              // last frame of ship animation
    currentFrame = startFrame;
    collision = false;
    collisionType =entityNS::BOX;
    target = false;
	spriteData.scale = 1;

}

bool Puck::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
	directionY = -1;
	directionX = 1;
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));

}
void Puck::changeDirectionY()
{
	 directionY *= -1;
}
void Puck::changeDirectionX()
{
	 directionX *= -1;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Puck::update(float frameTime)
{
    Entity::update(frameTime);

	//ADD code for puck to move left/right here
	setX(getX() + velocity.x * directionX * frameTime);

	//ADD "bounce" code here. Use the changeDirectionX() or changeDirectionY() functions
    if (getX() + puckNS::WIDTH > GAME_WIDTH || getX() < 0) changeDirectionX();
	
	//ADD spriteData.x, spriteData.y assignments here from Entity::position
	
}

