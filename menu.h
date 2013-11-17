
              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#ifndef MENU_H                 // Prevent multiple definitions if this 
#define MENU_H 

class Menu;

#include "graphics.h"
#include "constants.h"
#include "textDX.h"
#include <string>
#include <sstream>
#include "input.h"
#include <vector>
using std::vector;
using std::string;

namespace menuNS
{
	enum{
		//Main menu items
		SOUTHFALL,
		NEWGAME,
		LOADGAME,
		CONTROLS,
		EXIT,

		//Control menu items
		CONTROLS_SUB,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		INTERACT,
		MENU,
		ATTACK_CAST,
		BACK
	};
}
using namespace menuNS;


// inherits from Entity class
//...no it doesn't?
class Menu 
{
private:
   TextDX *menuItemFont;
   TextDX *menuItemFontHighlight;
   TextDX *menuHeadingFont;
   Input   *input;         // pointer to the input system
   Graphics *graphics;   
   int selectedItem;
   vector<string> menuItems; //menuItems[0] is the header
   D3DXVECTOR2 menuAnchor;
   int verticalOffset;
   int linePtr;
   int menuStart, menuEnd;
   COLOR_ARGB highlightColor;
   COLOR_ARGB normalColor;
   bool upDepressedLastFrame;
   bool downDepressedLastFrame;
   bool stay;				//false when it is time to leave the menu

public:
    // constructor
    Menu();
	void initialize(Graphics *g, Input *i);
	bool update();
	int getSelectedItem() {return selectedItem;}
	void draw();	
	void selectChoice(int selected);
};
#endif