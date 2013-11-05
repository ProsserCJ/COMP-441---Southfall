#include "southfall.h"

//=============================================================================
// Constructor
//=============================================================================
Southfall::Southfall() : Center(new VECTOR2(ZERO))
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

	// Graphics
	initializeGraphics();

	// WorldInterface
	Interface.initialize(graphics);

	// Initialized Player here, have center point at player's position

}

//=============================================================================
// Initialize images and textures
//=============================================================================
void Southfall::initializeGraphics()
{
	graphics = new Graphics();
    graphics->initialize(hwnd, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN);
	// Character 1
	if(!Character1TX.initialize(graphics, CHARACTER1_SHEET))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Character1 texture"));
	if(!Character1IM.initialize(graphics, 32, 32, 4, &Character1TX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Character1 image"));
}

//=============================================================================
// Update all game items
//=============================================================================
void Southfall::update()
{
	//player->update(frameTime);
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
	Interface.draw(*Center);
	gameFont->print("Words!", SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
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
