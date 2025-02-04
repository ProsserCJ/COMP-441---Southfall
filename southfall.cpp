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
	ifstream fin(INTRO_TEXT);
	char buffer[500];
	introText = new vector<string>;
	while(!fin.eof())
	{
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
	firstTimeBattle = true;
	Entity::killCount = 0;
	done = false;
	
	// Graphics
	graphics = new Graphics();
    graphics->initialize(hwnd, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN);
	//NPC::initGraphics(graphics);
	imageLibrary = new ImageLibrary(graphics);

	// Menu
	mainMenu = new Menu();
	mainMenu->initialize(graphics, input);

	actionMenu = new GameMenu();
	actionMenu->initialize(graphics, input, "Available Actions:");

	// Font
	gameFont = new TextDX();
	gameFont->initialize(graphics, 40, false, false, "Andalus");
	gameFont->setFontColor(SETCOLOR_ARGB(255,255,255,255));	

	//Initialize global TextBox
	textbox = new TextBox(gameFont, audio, input, &imageLibrary->TextBoxIM, &imageLibrary->TextBoxArrowIM);
	textbox->setActive(false);
	
	// WorldInterface
	Interface = new WorldInterface(imageLibrary);
	Interface->initialize(graphics, audio, textbox);	
	
	// Initialized Player here, have center point at player's position
	player = new Hero(ZERO, heroNS::HERO_RADIUS, &imageLibrary->Character1IM, input, 
		audio, textbox, new Drawable(&imageLibrary->SwingingSwordIM));	
	
	//places player right by first goblin
	//player->setPosition(VECTOR2(112.5,60.5));
	
	//places player by house in Southfall
	//player->setPosition(VECTOR2(102.5,96.5));

	//places player on chair in Bar
	player->setPosition(VECTOR2(11.5,7));

	player->setWorld(Interface->getCurrent());
	player->getWorld()->addEntity(player);
	player->setSpellType(NULLTYPE);

	birm = new Birmingham(audio, &imageLibrary->BirmSpriteIM);	
	birm->setPosition(VECTOR2(113,101.5));
	birm->setController(new StationaryAI(birm));	

	fontLoc = 0;
	fontTimer = 6;

	// For testing: set up action Menu:

	/*actionMenu->addButton(new Button("Sword", &imageLibrary->SwordIconIM, 0)); 
	actionMenu->addButton(new Button("Impede Spell", &imageLibrary->ImpedeEffectIM, 1)); 
	actionMenu->addButton(new Button("Quick Portal", &imageLibrary->PortalOpenIM, 2));
	actionMenu->addButton(new Button("Blink", &imageLibrary->BlinkIconIM, 3));
	actionMenu->addButton(new Button("Fireball", &imageLibrary->FireballIconIM, 4));
	actionMenu->addButton(new Button("Shadowball", &imageLibrary->ShadowballIconIM, 5));

	actionMenu->addButton(new Button("Magic Sight On", &imageLibrary->MagicSightOnIM, 8));
	actionMenu->addButton(new Button("Magic Sight Off", &imageLibrary->MagicSightOffIM, 9));	*/
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
			}
			break;
		case INTRO:
			if (!textbox->isActive())
			{				
				audio->playCue(SOUTHFALL_THEME);
				currentState = GAME;				
				Entity* temp = player->getWorld()->getNPCFacing(player->getPosition(), entityNS::UP);
				if (temp)
				{
					temp->setDir(entityNS::DOWN);
					player->reset();
					player->setDir(entityNS::UP);
					textbox->setText((NPC*)temp);
					textbox->setActive(true);
					audio->playCue(ALERT);
					delete introText;
				}
			}
		case OPENTEXTBOX:					//fallthrough is intentional
			textbox->update(frameTime);
			if (!textbox->isActive()) currentState = GAME;
			if (input->wasKeyPressed('E'))
			{
				audio->playCue(SELECT);
				textbox->next();
			}			
			break;	
		case GAME:
			if (!birm->isActive()){ currentState = GAME_OVER; break; }			
			if(input->isKeyDown(O_KEY) && input->isKeyDown(P_KEY))
			{
				birminghamRot = .001;
				player->setHP(INT_MAX);
				birm->setHP(INT_MAX);
				currentState = BIRMINGHAMSTATE;
				imageLibrary->BirminghamIM.setScale(10);
				audio->playCue(BIRMINGHAM_SOUND);
			}
			if(player->hasSword && !player->hasAddedSword)
			{
				float birmX = birm->getPosition().x;
				float birmY = birm->getPosition().y;
				int xs[] = {76,78, birmX,birmX, 138,136};
				int ys[] = {birmY,birmY, 69,71, birmY,birmY};
				for(int j = 0; j < 2; ++j)
				{
					for(int i = 0; i < GOBLIN_WAVE_COUNT/2; ++i)
					{
						Entity* goblin = new Entity(VECTOR2(xs[i]+j,ys[i]+j-.1), 0.3, GOBLIN_HEALTH, &imageLibrary->Goblin1IM, audio, 1, HUMAN_CRECT);
						goblin->setSpeed(3); goblin->setDeathSound(GOBLIN_DEATH);
						Interface->getMain()->addEntity(goblin, new WaveAI(goblin));
						Interface->getMain()->addEnemy(goblin);
					}			
				}
				for (int i=0; i<3; i++)
				{
					Entity* guard = new Entity(VECTOR2(120-i+.5,120), 0.5, GOBLIN_HEALTH, &imageLibrary->GuardIM, audio, 0, HUMAN_CRECT);
					guard->setSpeed(2);
					npcAI* ai = new WaveAI(guard);
					ai->setSight(12);
					Interface->getMain()->addEntity(guard, ai);	
				}
			
				
				Entity* guard1 = new Entity(VECTOR2(birmX-1, birmY-1), 0.5, GOBLIN_HEALTH, &imageLibrary->GuardIM, audio, 0, HUMAN_CRECT);
				guard1->setSpeed(2);
				npcAI* ai1 = new WaveAI(guard1);
				ai1->setSight(12);
				Interface->getMain()->addEntity(guard1, ai1);
				
				Entity* guard2 = new Entity(VECTOR2(birmX, birmY-1), 0.5, GOBLIN_HEALTH, &imageLibrary->GuardIM, audio, 0, HUMAN_CRECT);
				guard2->setSpeed(2);
				npcAI* ai2 = new WaveAI(guard2);
				ai2->setSight(12);
				Interface->getMain()->addEntity(guard2, ai2);					
					
				Entity* guard3 = new Entity(VECTOR2(birmX+1, birmY-1), 0.5, GOBLIN_HEALTH, &imageLibrary->GuardIM, audio, 0, HUMAN_CRECT);
				guard3->setSpeed(2);
				npcAI* ai3 = new WaveAI(guard3);
				ai3->setSight(12);
				Interface->getMain()->addEntity(guard3, ai3);								

				Interface->getMain()->addEntity(birm);			
				actionMenu->addButton(new Button("Sword", &imageLibrary->SwordIconIM, 0)); 
				player->hasAddedSword = true;
			}
			if(player->hasFireball && !player->hasAddedFireball)
			{
				actionMenu->addButton(new Button("Fireball", &imageLibrary->FireballIconIM, 4));
				player->hasAddedFireball = true;
			}
			if (Interface->getMain()->winCondition())
			{
					currentState = GAME_OVER;
					audio->stopCue(SOUTHFALL_THEME);
					audio->stopCue(MAIN_THEME);
					audio->stopCue(BATTLE);
					audio->playCue(WIN);
			}
				
			if(input->wasKeyPressed(T_KEY))
			{// Open action menu
				pause = true;
				currentState = ACTIONMENU;
			}
			else
			{
				playerClickActions();

				//if player has died, then...
				if(!player->getWorld()->update(Center(), frameTime))
				{
					player->setWorld(Interface->getStart());
					player->reset();
					currentState = INTRO;
					loadIntro();
					textbox->setText(*introText);
					textbox->setActive(true);
					audio->stopCue(SOUTHFALL_THEME);
					audio->stopCue(MAIN_THEME);
					audio->stopCue(BATTLE);
					fontLoc = 0;
					break;
				}
			}
			if (textbox->isActive())
			{
				pause = true;
				currentState = OPENTEXTBOX;
			}
			handleFX();
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

inline void Southfall::handleFX()
{
	if(player->getWorld() == Interface->getMain())
		{
			if (player->getPosition().x < 133 && player->getPosition().x > 86 && player->getPosition().y > 80 && fontLoc != 0)
			{
				audio->stopCue(BATTLE);
				audio->stopCue(MAIN_THEME);
				audio->playCue(SOUTHFALL_THEME);
				fontTimer = 6; fontLoc = 0;
			}
			else if (player->getPosition().x > 160 && fontLoc != 1)
			{
				audio->stopCue(BATTLE);
				audio->stopCue(SOUTHFALL_THEME);
				audio->playCue(MAIN_THEME);					
				fontTimer = 6; fontLoc = 1;
			}
			else if (player->getPosition().y < 65 && fontLoc != 3)
			{
				fontTimer = 6; fontLoc = 3; 
				audio->stopCue(SOUTHFALL_THEME);				
				audio->stopCue(MAIN_THEME);
				if (firstTimeBattle)
				{
					audio->playCue(BATTLE_INTRO);
					Sleep(3400);
					firstTimeBattle = false;					
				}
				audio->playCue(BATTLE);
			}
			else if (player->getPosition().x < 50 && fontLoc != 2)
			{
				audio->stopCue(BATTLE);
				audio->stopCue(SOUTHFALL_THEME);
				audio->playCue(MAIN_THEME);
				fontTimer = 6; fontLoc = 2;
			}
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
			if (!player->isAttacking()) audio->playCue(HOOH);
			player->attack(orient);			
			break;
		case IMPEDE:
			player->getWorld()->addEffect(new ImpedeEffect(target, 0.2, &imageLibrary->ImpedeEffectIM));
			player->resetAction();
			break;
		case QUICKPORTAL:
			if(player->hasTarget())
			{
				if(!player->getWorld()->collidesWithTile(player, target))
				{
					player->getWorld()->addEffect(new QuickPortal(player->getTarget(),
						target, 0.5, &imageLibrary->PortalOpenIM, &imageLibrary->PortalCloseIM));
					player->resetTarget();
				}
			}
			else if(!player->getWorld()->collidesWithTile(player, target)) player->setTarget(target);
			player->resetAction();
			break;
		case BLINK:
			if(player->getWorld()->canMoveHere(player, target))
			{
				player->newPosition(target, player->getWorld());
				player->resetAction();
			}
			break;
		case FIREBALL:
			P = new Projectile(player->getPosition(), FIREBALLSPEED, FIREBALLRADIUS, 
				FIREBALLRANGE, orient, &imageLibrary->FireballSheetIM, FIREBALLDAMAGE, PROJ_FIREBALL);
			P->setFrames(FIREBALLSTART, FIREBALLEND);
			P->setFrameDelay(0.1);
			player->getWorld()->addProjectile(P);
			player->resetAction();
			audio->playCue(FIREBALL_SOUND);
			break;
		case FREEZE:
			break;
		case SHADOWBALL:
			P = new Projectile(player->getPosition(), FIREBALLSPEED, FIREBALLRADIUS, 
				FIREBALLRANGE, orient, &imageLibrary->ShadowballSheetIM, 10, PROJ_SHADOWBALL, 0.f, 1.0f);
			P->setFrames(FIREBALLSTART, FIREBALLEND);
			P->setFrameDelay(0.1);
			player->getWorld()->addProjectile(P);
			player->resetAction();
			break;
		case MAGICSIGHTON: // Not a castable spell
		case MAGICSIGHTOFF: // Not a castable spell
		case NULLTYPE:
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
		char out[100];
		sprintf(out, "Goblins killed: %i", Entity::killCount);
		gameFont->print(out, 0, 0);
		if(fontTimer >= 0)
		{			
			if(fontTimer >= 4)
				imageLibrary->SouthfallFontIM[fontLoc].draw(SETCOLOR_ARGB(int((6-fontTimer)*80),255,255,255));
			else if(fontTimer < 2)
				imageLibrary->SouthfallFontIM[fontLoc].draw(SETCOLOR_ARGB(int(fontTimer*80),255,255,255));
			else
				imageLibrary->SouthfallFontIM[fontLoc].draw(SETCOLOR_ARGB(160,255,255,255));
			fontTimer -= frameTime;
		}
		break;
	case BIRMINGHAMSTATE:
		renderBirmingham();
		break;
	case ACTIONMENU:
		player->getWorld()->draw(Center(), player->usingMagicSight());
		actionMenu->draw();
		break;
	case OPENTEXTBOX:
		player->getWorld()->draw(Center(), player->usingMagicSight());
		textbox->draw();
		break;	
	case GAME_OVER:
		Image* temp;
		if (Interface->getMain()->winCondition()) temp = &imageLibrary->WinIM;
		else temp = &imageLibrary->DeadIM;

		temp->setX(SCREEN_WIDTH/2 - temp->getWidth()/2);
		temp->setY(SCREEN_HEIGHT/2 - temp->getHeight()/2);
		temp->draw();

		//if (input->anyKeyPressed()) done = true;

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

void Southfall::renderBirmingham()
{
	Image *BirminghamIM = &imageLibrary->BirminghamIM;
	if(BirminghamIM->getScale() < .1)
		currentState = GAME;
	BirminghamIM->setX(SCREEN_WIDTH/2-BirminghamIM->getWidth()*BirminghamIM->getScale()/2);
	BirminghamIM->setY(SCREEN_HEIGHT/2-BirminghamIM->getHeight()*BirminghamIM->getScale()/2);
	BirminghamIM->draw();
	BirminghamIM->setScale(BirminghamIM->getScale()*.996);
	BirminghamIM->setRadians(BirminghamIM->getRadians()+birminghamRot);
	birminghamRot += .0001;
}