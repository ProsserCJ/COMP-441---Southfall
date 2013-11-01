// Programming 2D Games
// Copyright (c) 2011,2012 by: 
// Charles Kelly
// collisionTypes.h v1.0

#ifndef _SOUTHFALL_H      // Prevent multiple definitions if this 
#define _SOUTHFALL_H      // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class Southfall;

#include "game.h"
#include "textureManager.h"
#include "entity.h"
#include <cmath>
#include "constants.h"
#include "textDX.h"
#include "graphics.h"
#include <sstream>
using std::stringstream;

enum Type {BOX, CIRCLE, ROTBOX};

//=============================================================================
// This class is the core of the game
//=============================================================================
class Southfall : public Game
{
private:
    // game items
    TextureManager paddleTM, puckTM;   // game texture
    Image   paddleTexture, puckTexture;
    VECTOR2 collisionVector;    // collision vector
	
	int score;
	TextDX* gameFont;
	stringstream ss;
	Type type;

public:
    // Constructor
    Southfall();

    // Destructor
    virtual ~Southfall();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif
