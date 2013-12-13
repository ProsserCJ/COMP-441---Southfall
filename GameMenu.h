#ifndef _GAME_MENU_H
#define _GAME_MENU_H

#include "image.h"
#include "textDX.h"
#include "input.h"
#include "Item.h"

#include <vector>
#include <string>
using std::vector;
using std::string;

const float ICONSCALE = 1.5f;
const int MENUXSHIFT = 20;
const int MENUINITIALY = 100;
const int ICONYSHIFT = 27;
const int ICONXSHIFT = 27;
const int BUTTONWIDTH = 100;
const int BUTTONHEIGHT = 100;
const int LETTERWIDTH = 8;

struct Button
{
	Button(string words, Image* icon, int type) 
		: topLeft(ZERO), width(0), height(0), words(words), icon(icon), type(type), isDown(false) {};

	Button(VECTOR2 TL, int width, int height, string words, Image* icon, int type) 
		: topLeft(TL), width(width), height(height), words(words), icon(icon), type(type), isDown(false) {};
	
	void update();
	void draw();

	VECTOR2 topLeft;
	int width, height;
	string words;

	int type;
	Image* icon;
	Image* buttonIM;
	Input* input;
	TextDX* itemNameFont;

	int wordShift;
	int imageShift;

	bool isDown;
};

class GameMenu
{
public:
	GameMenu() {};
	void initialize(Graphics* graphics, Input* input, string heading);
	void draw();
	void update(float frameTime);

	void addButton(Button* B);

	int getSelected() {return selected;}

private:
	Input* input;
	VECTOR2 anchor;
	Graphics* graphics;

	int selected;
	int selectedButton;
	int nextX, nextY;	// For arranging new buttons

	string Heading;
	TextDX* menuHeadingFont;
	TextDX* itemNameFont;

	vector<Button*> buttons;

	TextureManager BackgroundTX;
	Image BackgroundIM;
	TextureManager ButtonTX;
	Image ButtonIM;
};

#endif