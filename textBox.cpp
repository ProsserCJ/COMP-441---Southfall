#include "textBox.h"
#include "constants.h"

const int OFFSET_X = 25;
const int OFFSET_Y = 15;
RECT TEXT_RECT = {135, SCREEN_HEIGHT - 175, SCREEN_WIDTH-125, SCREEN_HEIGHT};

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
	gameFont->print((*it), TEXT_RECT, DT_WORDBREAK);  
}

void TextBox::update(float frameTime)	
{		
	arrow->update(frameTime);	
}

//iterate to the next sequence of text to display
void TextBox::next(){
	if (++it == text.end()){
		setActive(false);
		text.clear();		
		if (speaker) speaker->setPaused(false);
	}
}