// Programming 2D Games
// Copyright (c) 2011, 2012 by: 
// Charles Kelly
// Collision types demo


#include "southfall.h"

//=============================================================================
// Constructor
//=============================================================================
Southfall::Southfall()
{
	
}

//=============================================================================
// Destructor
//=============================================================================
Southfall::~Southfall()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Southfall::initialize(HWND hwnd)
{
    Game::initialize(hwnd); 

	/*if (!puckTM.initialize(graphics,PUCK_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing puck texture"));
	
    if (!paddleTM.initialize(graphics,PADDLE_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing paddle texture"));

	if (!puck.initialize(this, 80, 80, 1, &puckTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing puck"));

	if (!paddle.initialize(this, 60, 80, 1, &paddleTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing paddle"));
    
	puck.setCollisionType(entityNS::BOX);
	puck.setEdge(COLLISION_BOX_PUCK);
	paddle.setCollisionType(entityNS::BOX);
	paddle.setEdge(COLLISION_BOX_PADDLE);*/

	//ADD Font initialization code here
	gameFont = new TextDX();
	gameFont->initialize(graphics, 20, false, false, "Calibri");
	gameFont->setFontColor(SETCOLOR_ARGB(255,255,0,0));
	
	
	score = 0;
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Southfall::update()
{
	
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Southfall::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Southfall::collisions()
{

}

//=============================================================================
// Render game items
//=============================================================================
void Southfall::render()
{
	graphics->spriteBegin();                // begin drawing sprites
	
	ss.str(std::string());
	ss << "Hits: " << score;
	gameFont->print(ss.str(), GAME_WIDTH/2, GAME_HEIGHT/2);

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Southfall::releaseAll()
{
	paddleTM.onLostDevice();
	puckTM.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Southfall::resetAll()
{
	paddleTM.onResetDevice();
	puckTM.onResetDevice();
    Game::resetAll();
    return;
}
