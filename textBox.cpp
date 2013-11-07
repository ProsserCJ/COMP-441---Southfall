#include "textBox.h"
#include "constants.h"

const int OFFSET_X = 25;
const int OFFSET_Y = 15;

void TextBox::initialize(){	
	position = VECTOR2(100,SCREEN_HEIGHT - background->getHeight());
	background->setX(position.x);
	background->setY(position.y);
	arrow->setX(position.x + background->getWidth()/2-arrow->getWidth()/2);
	arrow->setY(background->getY() + background->getHeight() - arrow->getHeight());
	arrow->setFrames(0,3); 
	arrow->setFrameDelay(.1);
	arrow->setLoop(true);
	active = true;
}
void TextBox::draw()
{
	if (!active) return;
	background->draw();
	arrow->draw();
	gameFont->print(text, position.x + OFFSET_X, position.y + OFFSET_Y);
}