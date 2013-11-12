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

void Southfall::loadIntro()
 {
	ifstream fin("Worlds\\intro.txt");
	char buffer[500];
	introText = new vector<string>;
	while(!fin.eof()){
		fin.getline(buffer, 500);
		introText->push_back(buffer);    
	}
	fin.close();
 }

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Southfall::initialize(HWND hwnd)
{
    Game::initialize(hwnd);
	currentState = GAME;

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
	player->getWorld()->addEntity(player);

	// Impede effect
	if(!ImpedeEffectTX.initialize(graphics, IMPEDEEFFECTICON))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Impede effect texture"));
	if(!ImpedeEffectIM.initialize(graphics, 0, 0, 0, &ImpedeEffectTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Impede effect image"));
	// Portal Opening
	if(!PortalOpenTX.initialize(graphics, PORTALOPEN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Portal open texture"));
	if(!PortalOpenIM.initialize(graphics, 0, 0, 0, &PortalOpenTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Portal open image"));
	// Portal Exit
	if(!PortalCloseTX.initialize(graphics, PORTALCLOSE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Portal close texture"));
	if(!PortalCloseIM.initialize(graphics, 0, 0, 0, &PortalCloseTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Portal close image"));
	

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
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Character 1 texture"));
	if(!Character1IM.initialize(graphics, 32, 32, 8, &Character1TX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Character 1 image"));
	// Goblin 1
	if(!Goblin1TX.initialize(graphics, GOBLIN1_SHEET))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Goblin 1 texture"));
	if(!Goblin1IM.initialize(graphics, 32, 32, 8, &Goblin1TX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Goblin 1 image"));
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
	switch(currentState)
	{
		case MAIN_MENU:
			if (!mainMenu->update())
			{
				currentState = INTRO;
				loadIntro();
				textbox->setText(*introText);
				textbox->setActive(true);
				audio->playCue(INTRO_BACKGROUND);
			}
			break;
		case INTRO:
			textbox->update(frameTime);
			if (!textbox->isActive())
			{
				audio->stopCue(INTRO_BACKGROUND);
				currentState = GAME;
				audio->playCue(BACKGROUND);
				delete introText;
			}
			break;
		case GAME:
			playerClickActions();
			player->getWorld()->update(frameTime);
			textbox->update(frameTime);	
			break;
	}
}

inline void Southfall::playerClickActions()
{
	if(player->canAction() && input->getMouseLButton())
	{
		int X = input->getMouseX();
		int Y = input->getMouseY();
		VECTOR2 mouse(X,Y);
		VECTOR2 target = player->getPosition()+(mouse-HSCREEN)*INVTILE_SIZE;

		switch (player->getSpellType())
		{
		case NOSPELL:
			// Swing whatever you have in your hand
			break;
		case IMPEDE:
			player->getWorld()->addEffect(new ImpedeEffect(target, 0.2, &ImpedeEffectIM));
			player->resetAction();
			break;
		case PORTALTRAP:
			if(player->hasTarget())
			{
				player->getWorld()->addEffect(new PortalTrapEffect(player->getTarget(), target, 0.5, &PortalOpenIM, &PortalCloseIM));
				player->resetTarget();
			}
			else player->setTarget(target);
			player->resetAction();
			break;
		}
	}
	if(input->getMouseRButton()) player->resetTarget();
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
void Southfall::collisions() {}

//=============================================================================
// Render game items
//=============================================================================
void Southfall::render()
{// sprite begin and end in game now

	switch(currentState){
	case MAIN_MENU:
		mainMenu->draw();
		break;
	case INTRO:
		textbox->draw();
		break;
	case GAME:
		player->getWorld()->draw(Center());
		//player->draw(Center());	// For now
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
