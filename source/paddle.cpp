
#include "paddle.h"

//=============================================================================
// default constructor
//=============================================================================
Paddle::Paddle() : Entity()
{
    spriteData.width = paddleNS::WIDTH;           
    spriteData.height = paddleNS::HEIGHT;
    spriteData.x = paddleNS::X;                   
    spriteData.y = paddleNS::Y;
    spriteData.rect.bottom = paddleNS::HEIGHT/2;    
    spriteData.rect.right = paddleNS::WIDTH;
    velocity.x = 0;                             
    velocity.y = 0;                             
    startFrame = 0;              
    endFrame     = 0;              
    currentFrame = startFrame;
    collision = false;
    collisionType =entityNS::BOX;
    target = false;
	edge.bottom = -paddleNS::HEIGHT/2;
	edge.top = paddleNS::HEIGHT/2;
	edge.right = -paddleNS::WIDTH/2;
	edge.left = paddleNS::WIDTH/2;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Paddle::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Paddle::update(float frameTime)
{
    Entity::update(frameTime);
    //ADD POSITION UPDATING HERE
	setX(getX() + velocity.x*frameTime);
	setY(getY() + velocity.y*frameTime);
	
    // ADD WRAPPING CODE HERE.
   
	if (getX()+paddleNS::WIDTH > GAME_WIDTH) setX(1);
	if (getX() < 0) setX(GAME_WIDTH-paddleNS::WIDTH);

	// ADD "Top of screen" CODE HERE
	if (getY() <= 0){
		setY(paddleNS::Y);
		setX(paddleNS::X);
		velocity.y=0;
	}
	
	//ADD spriteData.x, spriteData.y assignments here from Entity::position
	
	

}