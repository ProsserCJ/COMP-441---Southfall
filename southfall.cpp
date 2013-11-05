#include "Southfall.h"

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

	// Font
	gameFont = new TextDX();
	gameFont->initialize(graphics, 20, false, false, "Calibri");
	gameFont->setFontColor(SETCOLOR_ARGB(255,255,0,0));

	// Graphics
	initializeGraphics();

	// WorldInterface
	Interface.initialize(graphics);

	// Initialized Player here, have center point at player's position
	player = new Hero(&Character1IM);
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
	float TESTVELOCITY = 640;
	// The code here just moves the camera untill we get a working player hero
	if(input->isKeyDown(WKEY) && input->isKeyDown(DKEY))
	{// UP-RIGHT
		Center->y -= frameTime*TESTVELOCITY*0.707f;
		Center->x += frameTime*TESTVELOCITY*0.707f;
	}
	else if(input->isKeyDown(WKEY) && input->isKeyDown(AKEY))
	{// UP-LEFT
		Center->y -= frameTime*TESTVELOCITY*0.707f;
		Center->x -= frameTime*TESTVELOCITY*0.707f;
	}
	else if(input->isKeyDown(SKEY) && input->isKeyDown(DKEY))
	{// DOWN-RIGHT
		Center->y += frameTime*TESTVELOCITY*0.707f;
		Center->x += frameTime*TESTVELOCITY*0.707f;
	}
	else if(input->isKeyDown(SKEY) && input->isKeyDown(AKEY))
	{// DOWN-LEFT
		Center->y += frameTime*TESTVELOCITY*0.707f;
		Center->x -= frameTime*TESTVELOCITY*0.707f;
	}
	else
	{// Single or opposite Key/s Down
		if(input->isKeyDown(WKEY))
		{
			Center->y -= frameTime*TESTVELOCITY;
		}
		if(input->isKeyDown(AKEY))
		{
			Center->x -= frameTime*TESTVELOCITY;
		}
		if(input->isKeyDown(SKEY))
		{
			Center->y += frameTime*TESTVELOCITY;
		}
		if(input->isKeyDown(DKEY))
		{
			Center->x += frameTime*TESTVELOCITY;
		}
	}
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

	player->draw(*Center);	// For now


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
