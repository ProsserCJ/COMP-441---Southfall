#include "image.h"
#include "textDX.h"
#include "string"
using std::string;

class TextBox{
public:
	TextBox(): gameFont(0) {}
	TextBox(TextDX* font, Image* bg, Image* arr, string t)
		:gameFont(font), background(bg), arrow(arr), text(t){initialize();}

	void initialize();
	virtual void draw();
	virtual void update(float frameTime)	{arrow->update(frameTime);}
	void changeText(string newText)			{text = newText;}
	void toggle()							{active = !active;}

private:
	VECTOR2 position;
	Image* background;
	Image* arrow;
	TextDX* gameFont;	
	string text;
	bool active;
};