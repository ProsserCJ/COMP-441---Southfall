
#include "menu.h"
#include <iterator>
using namespace menuNS;

Menu::Menu()
{
	selectedItem = -1;	//nothing return
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
}

void Menu::initialize(Graphics *g, Input *i)
{	
	selectChoice(SOUTHFALL);

	highlightColor = graphicsNS::RED;
	normalColor = graphicsNS::WHITE;
	menuAnchor = D3DXVECTOR2(270,10);
	input = i;
	verticalOffset = 35;
	linePtr = 1;
	selectedItem = -1;
	graphics = g;
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
	menuItemFontHighlight = new TextDX();
	

	if(menuItemFont->initialize(graphics, 25, true, false, "Andalus") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuItemFontHighlight->initialize(graphics, 28, true, false, "Andalus") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuHeadingFont->initialize(graphics, 40, true, false, "Andalus") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuHeading font"));

	menuHeadingFont->setFontColor(normalColor);
	menuItemFont->setFontColor(normalColor);
	menuItemFontHighlight->setFontColor(highlightColor);
	upDepressedLastFrame = false;
	downDepressedLastFrame = false;
	stay = true;
}

bool Menu::update()
{
	if (!input->isKeyDown('W')) upDepressedLastFrame = false;
	if (input->isKeyDown('W') && !upDepressedLastFrame)
	{
		linePtr--;
		upDepressedLastFrame = true;
	}

	if (!input->isKeyDown('S')) downDepressedLastFrame = false;	
	if (input->isKeyDown('S') && !downDepressedLastFrame)
	{
		linePtr++;
		downDepressedLastFrame = true;
	}
	if (linePtr > menuEnd) linePtr = menuStart;
	if (linePtr < menuStart) linePtr = menuEnd;

	if (input->wasKeyPressed(VK_RETURN) || input->wasKeyPressed('E')){
		selectedItem = linePtr;
		selectChoice(selectedItem);
	}
	return stay;
}

void Menu::draw()
{
	menuHeadingFont->print(menuItems[0], menuAnchor.x, menuAnchor.y);
	for (int i=1; i<menuItems.size(); i++){
		if (linePtr-menuStart+1 == i) menuItemFontHighlight->print(menuItems[i], menuAnchor.x, menuAnchor.y+verticalOffset*i);
		else menuItemFont->print(menuItems[i], menuAnchor.x, menuAnchor.y+verticalOffset*i);
	}
}

void Menu::selectChoice(int selected){
			
	switch(selected){
	case LOADGAME:
	case NEWGAME: stay = false;

	case SOUTHFALL:
		menuItems.clear();
		menuItems.push_back("Southfall");
		menuItems.push_back("New Game");
		menuItems.push_back("Load Game");
		menuItems.push_back("Exit");
		menuStart = NEWGAME;
		menuEnd = EXIT;
		break;	

	case EXIT: PostQuitMessage(0);
	}
	linePtr = menuStart;
}