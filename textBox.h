#include "image.h"
#include "textDX.h"
#include "string"
#include "audio.h"
#include "input.h"
using std::string;

class TextBox{
public:
	TextBox(): gameFont(0) {}
	TextBox(TextDX* font, Audio* a, Input* i, Image* bg, Image* arr, string t)
		:gameFont(font), audio(a), input(i), background(bg), arrow(arr), text(t)
		{initialize();}

	void initialize();
	virtual void draw();
	virtual void update(float frameTime);
	void changeText(string newText)			{text = newText;}
	void setActive(bool b)					{active = b;}
	void next();

private:
	VECTOR2 position;
	Audio* audio;
	Input* input;
	Image* background;
	Image* arrow;
	TextDX* gameFont;	
	string text; //maybe a vector of strings?
	bool active;
};