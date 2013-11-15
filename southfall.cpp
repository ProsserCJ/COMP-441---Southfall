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
	currentState = MAIN_MENU;
	pause = false;

	// Graphics
	initializeGraphics();

	// Menu
	mainMenu = new Menu();
	mainMenu->initialize(graphics, input);

	actionMenu = new GameMenu();
	actionMenu->initialize(graphics, input, "Available Actions:");

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
	player->setPosition(VECTOR2(102,96));
	player->setWorld(Interface.getCurrent());
	player->getWorld()->addEntity(player);

	//Set up region fonts
	if(!SouthfallFontTX[0].initialize(graphics, SOUTHFALLFONT))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing southfallFont texture"));
	if(!SouthfallFontTX[1].initialize(graphics, ESBURGFONT))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing esburgFont texture"));
	if(!SouthfallFontTX[2].initialize(graphics, WESELLYNFONT))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wesellynFont texture"));
	if(!SouthfallFontTX[3].initialize(graphics, NORSTAFFFONT))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing norstaffFont texture"));
	for(int i = 0; i < 4; ++i)
	{
		if(!SouthfallFontIM[i].initialize(graphics, 0, 0, 0, &SouthfallFontTX[i]))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing southfallFont image: " + i));
		SouthfallFontIM[i].setX(SCREEN_WIDTH/2-SouthfallFontIM[0].getWidth()/2);
		SouthfallFontIM[i].setY(SCREEN_HEIGHT/4-SouthfallFontIM[0].getHeight()/2);
	}
	fontLoc = 0;
	fontTimer = 6;

	// For testing: set up action Menu:

	actionMenu->addButton(new Button("No Spell", &SwordIconIM, 0)); 
	actionMenu->addButton(new Button("Impede Spell", &ImpedeEffectIM, 1)); 
	actionMenu->addButton(new Button("Portal Trap", &PortalOpenIM, 2));
	actionMenu->addButton(new Button("Blink", &BlinkIconIM, 3));
	actionMenu->addButton(new Button("Fireball", &FireballIconIM, 4));

	actionMenu->addButton(new Button("Magic Sight On", &MagicSightOnIM, 6));
	actionMenu->addButton(new Button("Magic Sight Off", &MagicSightOffIM, 7));

}

//=============================================================================
// Initialize images and textures
//=============================================================================
void Southfall::initializeGraphics()
{
	graphics = new Graphics();
    graphics->initialize(hwnd, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN);

	// Characters and npcs

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
	
	// Icons and spells

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
	// Sword Icon
	if(!SwordIconTX.initialize(graphics, SWORDICON))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing SwordIcon texture"));
	if(!SwordIconIM.initialize(graphics, 0, 0, 0, &SwordIconTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing SwordIcon image"));
	// Blink Icon
	if(!BlinkIconTX.initialize(graphics, BLINKICON))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing BlinkIcon texture"));
	if(!BlinkIconIM.initialize(graphics, 0, 0, 0, &BlinkIconTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing BlinkIcon image"));
	// Fireball Icon
	if(!FireballIconTX.initialize(graphics, FIREBALLICON))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing FireballIcon texture"));
	if(!FireballIconIM.initialize(graphics, 0, 0, 0, &FireballIconTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing FireballIcon image"));
	// Magic Sight On Icon
	if(!MagicSightOnTX.initialize(graphics, MAGICSIGHTONICON))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing MagicSightOn texture"));
	if(!MagicSightOnIM.initialize(graphics, 0, 0, 0, &MagicSightOnTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing MagicSightOn image"));
	// Magic Sight Off Icon
	if(!MagicSightOffTX.initialize(graphics, MAGICSIGHTOFFICON))
	  throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing MagicSightOff texture"));
	if(!MagicSightOffIM.initialize(graphics, 0, 0, 0, &MagicSightOffTX))
	  throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing MagicSightOff image"));

	// Fireball projectile
	if(!FireballSheetTX.initialize(graphics, FIREBALLSHEET))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Fireball sheet texture"));
	if(!FireballSheetIM.initialize(graphics, 16, 16, 4, &FireballSheetTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Fireball sheet image"));

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
			player->update(frameTime, player->getWorld());
			if (!textbox->isActive())
			{
				audio->stopCue(INTRO_BACKGROUND);
				currentState = GAME;
				audio->playCue(BACKGROUND);
				delete introText;
			}
		case OPENTEXTBOX:					//fallthrough is intentional
			textbox->update(frameTime);
			if (input->wasKeyPressed('E'))
			{
				audio->playCue(SELECT);
				textbox->next();
			}
			if (!textbox->isActive()) currentState = GAME;
			break;	
		case GAME:
			if(input->wasKeyPressed(T_KEY))
			{// Open action menu
				pause = true;
				currentState = ACTIONMENU;
			}
			else
			{
				playerClickActions();
				player->getWorld()->update(frameTime);
				player->update(frameTime, player->getWorld());
			}
			if (textbox->isActive())
			{
				pause = true;
				currentState = OPENTEXTBOX;
			}
			if (player->getPosition().x < 133 && player->getPosition().x > 86 && player->getPosition().y > 80 && fontLoc != 0)
			{
				fontTimer = 6; fontLoc = 0;
			}
			else if (player->getPosition().x > 160 && fontLoc != 1)
			{
				fontTimer = 6; fontLoc = 1;
			}
			else if (player->getPosition().y < 65 && fontLoc != 3)
			{
				fontTimer = 6; fontLoc = 3;
			}
			else if (player->getPosition().x < 50 && fontLoc != 2)
			{
				fontTimer = 6; fontLoc = 2;
			}
			break;
		case ACTIONMENU:
			actionMenu->update(frameTime);
			if(input->wasKeyPressed(T_KEY))
				currentState = GAME;
			if(actionMenu->getSelected() != -1)
			{
				if(actionMenu->getSelected() == MAGICSIGHTON)
					player->setMagicSight(true);
				else if(actionMenu->getSelected() == MAGICSIGHTOFF)
					player->setMagicSight(false);
				else player->setSpellType(SPELLTYPE(actionMenu->getSelected()));
				player->resetTarget();
			}
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
		float sY = static_cast<float>(Y - (int)HSCREEN_HEIGHT);
		float sX = static_cast<float>(X - (int)HSCREEN_WIDTH);
		float orient = atan2(sY, sX);
		Projectile* P;

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
				if(!player->getWorld()->collidesWithTile(player, target))
				{
					player->getWorld()->addEffect(new PortalTrapEffect(player->getTarget(),
						target, 0.5, &PortalOpenIM, &PortalCloseIM));
					player->resetTarget();
				}
			}
			else if(!player->getWorld()->collidesWithTile(player, target)) player->setTarget(target);
			player->resetAction();
			break;
		case BLINK:
			if(player->getWorld()->canMoveHere(player, target))
			{
				player->setPosition(target);
				player->resetAction();
			}
			break;
		case FIREBALL:
			P = new Projectile(player->getPosition(), FIREBALLSPEED, FIREBALLRADIUS, 
				FIREBALLRANGE, orient, &FireballSheetIM, 0);
			P->setFrames(FIREBALLSTART, FIREBALLEND);
			P->setFrameDelay(0.1);
			player->getWorld()->addProjectile(P);
			player->resetAction();
			break;
		case FREEZE:
			break;
		case MAGICSIGHTON: // Not a castable spell
		case MAGICSIGHTOFF: // Not a castable spell
		default:
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
	player->getWorld()->act();
}

//=============================================================================
// Handle collisions
//=============================================================================
void Southfall::collisions() 
{
	player->getWorld()->collisions();
}

//=============================================================================
// Render game items
//=============================================================================
void Southfall::render()
{// sprite begin and end in game now

	switch(currentState)
	{
	case MAIN_MENU:
		mainMenu->draw();
		break;
	case INTRO:
		textbox->draw();
		break;
	case GAME:
		player->getWorld()->draw(Center(), player->usingMagicSight());		
		if(fontTimer >= 0)
		{
			if(fontTimer >= 4)
				SouthfallFontIM[fontLoc].draw(SETCOLOR_ARGB(int((6-fontTimer)*80),255,255,255));
			else if(fontTimer < 2)
				SouthfallFontIM[fontLoc].draw(SETCOLOR_ARGB(int(fontTimer*80),255,255,255));
			else
				SouthfallFontIM[fontLoc].draw(SETCOLOR_ARGB(160,255,255,255));
			fontTimer -= frameTime;
		}
		break;
	case ACTIONMENU:
		player->getWorld()->draw(Center(), player->usingMagicSight());
		actionMenu->draw();
		break;
	case OPENTEXTBOX:
		player->getWorld()->draw(Center(), player->usingMagicSight());
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
