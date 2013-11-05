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

	// Hero	
	/*if(!heroTexture.initialize(graphics, HERO_SPRITE_SHEET))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize hero texture."));

	if (!player->initialize(this, heroNS::WIDTH, heroNS::HEIGHT, heroNS::COLS, &heroTexture)) 
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize hero."));*/

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
	player->update(frameTime);
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
void Southfall::render() // sprite begin and end in game now
						//...where they should have been all along. brilliant

{
	gameFont->print("Words!", GAME_WIDTH/2, GAME_HEIGHT/2);
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Southfall::releaseAll()
{
    Game::releaseAll();
	heroTexture.onLostDevice();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Southfall::resetAll()
{
    Game::resetAll();
	heroTexture.onResetDevice();
    return;
}
