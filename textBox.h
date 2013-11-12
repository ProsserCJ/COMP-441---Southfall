#ifndef __TEXTBOX_H
#define __TEXTBOX_H

#include "image.h"
#include "textDX.h"
#include "string"
#include "audio.h"
#include "input.h"
#include <vector>
#include "npc.h"
using std::string;
using std::vector;

class TextBox{
public:
	TextBox(): gameFont(0) {}
	TextBox(TextDX* font, Audio* a, Input* i, Image* bg, Image* arr)
		:gameFont(font), audio(a), input(i), background(bg), arrow(arr)
		{initialize();}

	void initialize();
	virtual void draw();
	virtual void update(float frameTime);	
	void setText(NPC* n)					{speaker = n; text = n->getText(); it=text.begin();}
	void setText(vector<string>& t)			{speaker = 0; text = t; it=text.begin();}
	void setActive(bool b)					{active = b;}
	void next();
	bool isActive()							{return active;}

private:
	VECTOR2 position;
	Audio* audio;
	Input* input;
	Image* background;
	Image* arrow;
	NPC* speaker;
	TextDX* gameFont;
	vector<string> text;
	vector<string>::iterator it;
	bool active;
};

#endif