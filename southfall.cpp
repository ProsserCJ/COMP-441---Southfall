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
{ // Call onLostDevice() for every graphics item
    releaseAll();
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Southfall::initialize(HWND hwnd)
{
    Game::initialize(hwnd); 

	// Font
	gameFont = new TextDX();
	gameFont->initialize(graphics, 20, false, false, "Calibri");
	gameFont->setFontColor(SETCOLOR_ARGB(255,255,0,0));

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
{// sprite begin and end in game now
	
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Southfall::releaseAll()
{
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Southfall::resetAll()
{
    Game::resetAll();
    return;
}
