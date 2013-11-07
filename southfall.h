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
using std::stringstream;

class Southfall : public Game
{
public:
    // Constructor
    Southfall();
    // Destructor
    ~Southfall();

    // Initialize the game
    void initialize(HWND hwnd);
    void update(); 
    void ai();         
    void collisions(); 
    void render();    
    void releaseAll();
    void resetAll();

private:
    TextDX* gameFont;
	stringstream ss;

	// Images and Textures
	TextureManager Character1TX, NPC1TX, TextBoxTX, TextBoxArrowTX;
	Image Character1IM, NPC1IM, TextBoxIM, TextBoxArrowIM;
	WorldInterface worldInterface;

	void initializeGraphics();
	
	VECTOR2* Center;
	
	Hero* player;
	NPC* npc1;
	TextBox* textbox;
	WorldInterface Interface; 

};

#endif
