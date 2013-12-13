#include "GameMenu.h"

void Button::update()
{
	if(input->getMouseLButton())
	{
		int X = input->getMouseX();
		int Y = input->getMouseY();
		if(topLeft.x < X && X < topLeft.x + width 
			&& topLeft.y < Y && Y < topLeft.y + height)
			isDown = true;
		else isDown = false;
	}
}

void Button::draw()
{
	if(isDown) buttonIM->setCurrentFrame(1);
	else buttonIM->setCurrentFrame(0);
	int X = (int)topLeft.x, Y = (int)topLeft.y;
	buttonIM->setX(X); buttonIM->setY(Y);
	buttonIM->draw();
	itemNameFont->print(words, X+wordShift, Y);
	icon->setX(X+imageShift); icon->setY(Y+ICONYSHIFT);
	icon->setScale(ICONSCALE);
	icon->draw();
}

void GameMenu::initialize(Graphics* graphics, Input* input, string heading)
{
	this->graphics = graphics;
	this->input = input;
	Heading = heading;
	selected = -1;
	selectedButton = 0;
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
	// ButtonIM
	if(!ButtonTX.initialize(graphics, BUTTON_SHEET))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Button texture"));
	if(!ButtonIM.initialize(graphics, 100, 100, 2, &ButtonTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Button image"));
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
		buttons.at(i)->draw();
}

void GameMenu::update(float frameTime)
{
	selected = -1;
	for(int i=0; i<buttons.size(); i++)
	{
		buttons.at(i)->update();
		if(buttons.at(i)->isDown) 
		{
			if(i != selectedButton) 
				buttons.at(selectedButton)->isDown = false;
			selectedButton = i;
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
	B->imageShift = ICONXSHIFT;
	B->input = input;
	B->buttonIM = &ButtonIM;
	B->itemNameFont = itemNameFont;

	buttons.push_back(B);
}