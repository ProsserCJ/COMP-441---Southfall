/****************************************************
Southfall game header file, containts the definition
for our game class.

Last modified: 11/4/2013

******************************************************/

#ifndef _SOUTHFALL_H
#define _SOUTHFALL_H
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include <cmath>
#include "constants.h"
#include "textDX.h"
#include "graphics.h"
#include <sstream>
#include "hero.h"
#include "WorldInterface.h"
#include "npc.h"
#include "textBox.h"
#include "menu.h"
#include "GameMenu.h"
using std::stringstream;

enum gameState {MAIN_MENU, INTRO, GAME, ACTIONMENU, CREDITS, GAME_OVER};

const float SELECTDELAY = 0.5;

class Southfall : public Game
{
public:
    // Constructor
    Southfall();
    // Destructor
    ~Southfall();

    // Game functions
    void initialize(HWND hwnd);
    void update(); 
    void ai();         
    void collisions(); 
    void render();    
    void releaseAll();
    void resetAll();

	// Accessors
	VECTOR2 heroPosition()	{return player->getPosition();}
	World* getWorld()		{return Interface.getCurrent();}
	VECTOR2 Center()		{return TILE_SIZE*player->getPosition();}

private:
    Menu* mainMenu;
	GameMenu* actionMenu;
	bool pause;

	inline void playerClickActions();
	
	TextDX* gameFont;
	stringstream ss;

	// Images and Textures
	TextureManager Character1TX, NPC1TX, Goblin1TX, TextBoxTX, TextBoxArrowTX, SouthfallFontTX[4];
	Image Character1IM, NPC1IM, TextBoxIM, Goblin1IM, TextBoxArrowIM, SouthfallFontIM[4];
	WorldInterface worldInterface;

	double fontTimer;
	int fontLoc; //southfall:0 esburg:1,wesellyn:2,norstaff:3

	void initializeGraphics();
	void loadIntro();
	vector<string>* introText;
	
	Hero* player;
	gameState currentState;

	TextBox* textbox;
	WorldInterface Interface;  

	// Images and Textures
	TextureManager ImpedeEffectTX;
	Image ImpedeEffectIM;
	TextureManager PortalOpenTX;
	Image PortalOpenIM;
	TextureManager PortalCloseTX;
	Image PortalCloseIM;
	TextureManager SwordIconTX;
	Image SwordIconIM;
	TextureManager BlinkIconTX;
	Image BlinkIconIM;
	TextureManager FireballIconTX;
	Image FireballIconIM;

	TextureManager FireballSheetTX;
	Image FireballSheetIM;

};

#endif
