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
	currentState = MAIN_MENU;

	// Graphics
	initializeGraphics();

	// Menu
	mainMenu = new Menu();
	mainMenu->initialize(graphics, input);

	// Font
	gameFont = new TextDX();
	gameFont->initialize(graphics, 40, false, false, "Andalus");
	gameFont->setFontColor(SETCOLOR_ARGB(255,255,255,255));	

	// WorldInterface
	Interface.initialize(graphics);

	//Initialize global TextBox
	textbox = new TextBox(gameFont, audio, input, &TextBoxIM, &TextBoxArrowIM);
	textbox->setActive(false);
	
	// Initialized Player here, have center point at player's position
	player = new Hero(ZERO, heroNS::HERO_RADIUS, &Character1IM, input, audio, textbox);	
	player->setPosition(VECTOR2(23,13));
	player->setWorld(Interface.getCurrent());
	
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

	NPC::initGraphics(graphics);
}

//=============================================================================
// Update all game items
//=============================================================================
void Southfall::update()
{	
	switch(currentState){
	case MAIN_MENU:
		if (!mainMenu->update()) currentState = GAME;
		break;
	case GAME:
		player->getWorld()->update(frameTime);
		player->update(frameTime, player->getWorld());	
		textbox->update(frameTime);	
		break;
	};	
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Southfall::ai()
{
	Interface.act();
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

	switch(currentState){
	case MAIN_MENU:
		mainMenu->draw();
		break;
	case GAME:
		player->getWorld()->draw(Center());
		player->draw(Center());	// For now
		textbox->draw();
		break;
	}
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
