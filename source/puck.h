
              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#ifndef PUCK_H                 // Prevent multiple definitions if this 
#define PUCK_H   
class Puck;

#include "entity.h"
#include "constants.h"

namespace puckNS
{
    const int WIDTH = 64;                   // image width
    const int HEIGHT = 64;                  // image height
  //ADD position initialization here
	const int X = 0;   // location on screen
    const int Y = 10;
    const float SPEED = 30;                
 
}

// inherits from Entity class
class Puck : public Entity
{
private:   
    bool collision;                 
    bool target;  
	int directionX;
	int directionY;

public:
    // constructor
    Puck();

    // inherited member functions
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);

    // Set collision Boolean
    void setCollision(bool c)
    {collision = c;}

    // Set collision type (NONE, CIRCLE, BOX, ROTATED_BOX)
    virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)
    {collisionType = ctype;}

    // Set RECT structure used for BOX and ROTATED_BOX collision detection.
    void setEdge(RECT e) {edge = e;}

    // Set target
    void setTarget(bool t) {target = t;}

    // Get collision
    bool getCollision() {return collision;}

    // Get collision type
    entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}

	void changeDirectionX();
	void changeDirectionY();
	void setInvisible() {Image::setVisible(false); Entity::setActive(false);}
	void setVisible() {Image::setVisible(true); Entity::setActive(true);}
};
#endif

