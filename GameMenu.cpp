#include "GameMenu.h"

bool Button::clicked(int X, int Y)
{
	if(topLeft.x < X && X < topLeft.x + width 
		&& topLeft.y < Y && Y < topLeft.y + height)
		return true;
	return false;
}

void GameMenu::initialize(Graphics* graphics, Input* input)
{
	this->graphics = graphics;
	this->input = input;
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
	menuHeadingFont->print("Action Choices:", anchor.x + 30, anchor.y + 30);
	for(int i = 0; i<buttons.size(); i++)
	{
		int X = buttons.at(i)->topLeft.x;
		int Y = buttons.at(i)->topLeft.y;
		itemNameFont->print(buttons.at(i)->words, X, Y);
		buttons.at(i)->icon->setX(X); buttons.at(i)->icon->setY(Y + 25);
		buttons.at(i)->icon->setScale(ICONSCALE);
		buttons.at(i)->icon->draw();
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
		nextX = 15;
		nextY += 120;
	}
	// What if it runs off the bottom of the screen?
	B->width = BUTTONWIDTH;
	B->height = BUTTONHEIGHT;

	buttons.push_back(B);
}