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
	player = new Hero(&Character1IM, input);	
	player->setPosition(VECTOR2(5,3));
	npc1 = new NPC(&NPC1IM, VECTOR2(4,4));
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
	if(!NPC1TX.initialize(graphics, CHARACTER1_SHEET))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing NPC1 texture"));
	if(!NPC1IM.initialize(graphics, 32, 32, 4, &NPC1TX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing NPC1 image"));
}

//=============================================================================
// Update all game items
//=============================================================================
void Southfall::update()
{
	/*if (input->isKeyDown(WKEY))
	{
		if (input->isKeyDown(DKEY)) player->go(UP_RIGHT);
		else if (input->isKeyDown(AKEY)) player->go(UP_LEFT);	
		else player->go(UP);
	}	
	else if (input->isKeyDown(SKEY))
	{
		if (input->isKeyDown(DKEY)) player->go(DOWN_RIGHT);
		else if (input->isKeyDown(AKEY)) player->go(DOWN_LEFT);	
		else player->go(DOWN);
	}
	else if (input->isKeyDown(AKEY)) player->go(LEFT);
	else if (input->isKeyDown(DKEY)) player->go(RIGHT);
	else player->standing();*/

	//// Move camera
	//float TESTVELOCITY = 640;
	//// The code here just moves the camera untill we get a working player hero
	//if(input->isKeyDown(WKEY) && input->isKeyDown(DKEY))
	//{// UP-RIGHT
	//	Center->y -= frameTime*TESTVELOCITY*0.707f;
	//	Center->x += frameTime*TESTVELOCITY*0.707f;
	//}
	//else if(input->isKeyDown(WKEY) && input->isKeyDown(AKEY))
	//{// UP-LEFT
	//	Center->y -= frameTime*TESTVELOCITY*0.707f;
	//	Center->x -= frameTime*TESTVELOCITY*0.707f;
	//}
	//else if(input->isKeyDown(SKEY) && input->isKeyDown(DKEY))
	//{// DOWN-RIGHT
	//	Center->y += frameTime*TESTVELOCITY*0.707f;
	//	Center->x += frameTime*TESTVELOCITY*0.707f;
	//}
	//else if(input->isKeyDown(SKEY) && input->isKeyDown(AKEY))
	//{// DOWN-LEFT
	//	Center->y += frameTime*TESTVELOCITY*0.707f;
	//	Center->x -= frameTime*TESTVELOCITY*0.707f;
	//}
	//else
	//{// Single or opposite Key/s Down
	//	if(input->isKeyDown(WKEY))
	//	{
	//		Center->y -= frameTime*TESTVELOCITY;
	//	}
	//	if(input->isKeyDown(AKEY))
	//	{
	//		Center->x -= frameTime*TESTVELOCITY;
	//	}
	//	if(input->isKeyDown(SKEY))
	//	{
	//		Center->y += frameTime*TESTVELOCITY;
	//	}
	//	if(input->isKeyDown(DKEY))
	//	{
	//		Center->x += frameTime*TESTVELOCITY;
	//	}
	//}

	player->update(frameTime, Interface.getCurrent());
	npc1->update(frameTime, Interface.getCurrent());
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Southfall::ai()
{
	npc1->act(Interface.getCurrent());
}

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
	Interface.draw(TILE_SIZE*player->getPosition());
	player->draw(TILE_SIZE*player->getPosition());	// For now
	npc1->draw(TILE_SIZE*player->getPosition());

}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Southfall::releaseAll()
{
    Game::releaseAll();
	Character1TX.onLostDevice();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Southfall::resetAll()
{
    Game::resetAll();
	Character1TX.onResetDevice();
    return;
}
