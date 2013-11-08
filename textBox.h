#include "image.h"
#include "textDX.h"
#include "string"
#include "audio.h"
#include "input.h"
#include <vector>
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
	void addText(string newText)			{text.push_back(newText); it=text.begin();}
	void setActive(bool b)					{active = b;}
	void next();

private:
	VECTOR2 position;
	Audio* audio;
	Input* input;
	Image* background;
	Image* arrow;
	TextDX* gameFont;
	vector<string> text;
	vector<string>::iterator it;
	bool active;
};