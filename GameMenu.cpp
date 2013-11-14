#include "GameMenu.h"

bool Button::clicked(int X, int Y)
{
	if(topLeft.x < X && X < topLeft.x + width 
		&& topLeft.y < Y && Y < topLeft.y + height)
		return true;
	return false;
}

void GameMenu::initialize(Graphics* graphics, Input* input, string heading)
{
	this->graphics = graphics;
	this->input = input;
	Heading = heading;
	selected = -1;
	// Fonts
	menuHeadingFont = new TextDX;
	if(menuHeadingFont->initialize(graphics, 35, true, false, "Andalus") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuHeading font"));
	menuHeadingFont->setFontColor(graphicsNS::WHITE);
	itemNameFont = new TextDX;
	if(itemNameFont->initialize(graphics, 25, true, false, "Andalus") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing itemName font"));
	itemNameFont->setFontColor(graphicsNS::WHITE);
	// Background
	if(!BackgroundTX.initialize(graphics, GAMEMENUBACK))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Background texture"));
	if(!BackgroundIM.initialize(graphics, 0, 0, 0, &BackgroundTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Background image"));
	anchor.x = SCREEN_WIDTH - BackgroundIM.getWidth();
	anchor.y = 0;
	BackgroundIM.setX(anchor.x);
	BackgroundIM.setY(anchor.y);

	nextX = MENUXSHIFT;
	nextY = MENUINITIALY;
}

void GameMenu::draw()
{
	BackgroundIM.draw();
	menuHeadingFont->print(Heading, anchor.x + 30, anchor.y + 30);
	for(int i = 0; i<buttons.size(); i++)
	{
		Button* B = buttons.at(i);
		int X = B->topLeft.x;
		int Y = B->topLeft.y;
		
		itemNameFont->print(B->words, X+B->wordShift, Y);
		
		B->icon->setX(X+B->imageShift); B->icon->setY(Y + ICONYSHIFT);
		B->icon->setScale(ICONSCALE);
		B->icon->draw();
	}
}

void GameMenu::update(float frameTime)
{
	selected = -1;
	if(input->getMouseLButton())
	{
		int X = input->getMouseX();
		int Y = input->getMouseY();
		for(int i=0; i<buttons.size(); i++)
			if(buttons.at(i)->clicked(X,Y)) 
			{
				selected = buttons.at(i)->type;
				return;
			}
	}
}

void GameMenu::addButton(Button* B)
{
	B->topLeft.x = nextX + anchor.x;
	B->topLeft.y = nextY + anchor.y;

	nextX += BUTTONWIDTH + MENUXSHIFT;
	if(nextX > BackgroundIM.getWidth() - BUTTONWIDTH)
	{
		nextX = MENUXSHIFT;
		nextY += 120;
	}
	// What if it runs off the bottom of the screen? Have a second page! Make a next, back button.
	B->width = BUTTONWIDTH;
	B->height = BUTTONHEIGHT;
	int length = B->words.length();
	B->wordShift = max((BUTTONWIDTH - length*LETTERWIDTH)*0.5,0);
	B->imageShift = max((BUTTONWIDTH - B->icon->getWidth())*0.5,0);

	buttons.push_back(B);
}