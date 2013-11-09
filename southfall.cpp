#include "Southfall.h"

//=============================================================================
// Constructor
//=============================================================================
Southfall::Southfall() {}

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

	// Graphics
	initializeGraphics();

	// Font
	gameFont = new TextDX();
	gameFont->initialize(graphics, 40, false, false, "Andalus");
	gameFont->setFontColor(SETCOLOR_ARGB(255,255,255,255));	

	// WorldInterface
	Interface.initialize(graphics);

	// Initialized Player here, have center point at player's position
	player = new Hero(ZERO, heroNS::HERO_RADIUS, &Character1IM, input, audio);	
	player->setPosition(VECTOR2(5,3));

	//Initizlize NPC
	npc1 = new NPC(&NPC1IM, VECTOR2(4,4));

	//Initialize global TextBox
	textbox = new TextBox(gameFont, audio, input, &TextBoxIM, &TextBoxArrowIM);
	/*textbox->addText("A perilous world awaits...");
	textbox->addText("...you have no idea what is coming...");
	textbox->addText("...and neither do we.");*/
	audio->playCue(BACKGROUND);

	
}

//=============================================================================
// Initialize images and textures
//=============================================================================
void Southfall::initializeGraphics()
{
	graphics = new Graphics();
    graphics->initialize(hwnd, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN);

	// Character 1
	if(!Character1TX.initialize(graphics, CHARACTER2_SHEET))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Character1 texture"));
	if(!Character1IM.initialize(graphics, 32, 32, 8, &Character1TX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Character1 image"));
	// NPC 1
	if(!NPC1TX.initialize(graphics, CHARACTER2_SHEET))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing NPC1 texture"));
	if(!NPC1IM.initialize(graphics, 32, 32, 8, &NPC1TX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing NPC1 image"));
	// Textbox
	if(!TextBoxTX.initialize(graphics, TEXTBOX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Textbox texture"));
	if(!TextBoxIM.initialize(graphics, 1000, 200, 1, &TextBoxTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Textbox image"));
	// Textbox arrow
	if(!TextBoxArrowTX.initialize(graphics, TEXTBOX_ARROW))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Textbox arrow texture"));
	if(!TextBoxArrowIM.initialize(graphics, 35, 20, 4, &TextBoxArrowTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Textbox arrow image"));
}

//=============================================================================
// Update all game items
//=============================================================================
void Southfall::update()
{	
	Interface.update(frameTime);

	player->update(frameTime, getWorld());
	npc1->update(frameTime, getWorld());
	
	//textbox->update(frameTime);	
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
	Interface.draw(Center());
	player->draw(Center());	// For now
	npc1->draw(Center());
	//textbox->draw();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Southfall::releaseAll()
{
    Game::releaseAll();
	Character1TX.onLostDevice();
	NPC1TX.onLostDevice();
	TextBoxTX.onLostDevice();
	TextBoxArrowTX.onLostDevice();
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
	NPC1TX.onResetDevice();
	TextBoxTX.onResetDevice();
	TextBoxArrowTX.onResetDevice();
    return;
}
