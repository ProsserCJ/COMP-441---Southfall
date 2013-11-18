#ifndef _IMAGE_LIBRARY_H
#define _IMAGE_LIBRARY_H

#include "graphics.h"
#include "image.h"

class ImageLibrary
{
public:
	ImageLibrary() : _initialized(false) {};
	ImageLibrary(Graphics* graphics) 
		: _initialized(false) {initialize(graphics);}
	void initialize(Graphics* graphics);

	// Images
	Image Character1IM, NPC1IM, TextBoxIM, Goblin1IM, WraithIM, TextBoxArrowIM, SouthfallFontIM[4];
	// Images and Textures
	Image ShadowballSheetIM;
	Image FireballSheetIM;
	Image ShadowballIconIM;
	Image MagicSightOffIM;
	Image MagicSightOnIM;
	Image FireballIconIM;
	Image BlinkIconIM;
	Image SwordIconIM;
	Image PortalCloseIM;
	Image ImpedeEffectIM;
	Image PortalOpenIM;
	Image GrassIM;
	Image WaterIM;
	Image Boulder1IM;
	Image WoodTileIM;
	Image Boulder2IM;
	Image RiverIM;
	Image MagicPortalIM;
	Image HWallIM;
	Image VWallIM;
	Image CWallIM;
	Image HouseIM;
	Image TreeIM;
	Image HouseWallIM;
	Image HouseDoorIM;
	Image BedIM;
	Image BarCounterIM;
	Image BarBack1IM;
	Image BarBack2IM;
	Image TableIM;
	Image RChairIM;
	Image LChairIM;
	Image HorizInHouseDoorIM;
	Image VertInHouseDoorIM;
	Image SwingingSwordIM;
	Image DeadGuyIM;
	Image BirminghamIM;

private:
	bool _initialized;

	// Textures
	TextureManager Character1TX, NPC1TX, Goblin1TX, WraithTX, TextBoxTX, TextBoxArrowTX, SouthfallFontTX[4];
	TextureManager ImpedeEffectTX;
	TextureManager PortalOpenTX;
	TextureManager PortalCloseTX;
	TextureManager SwordIconTX;
	TextureManager BlinkIconTX;
	TextureManager FireballIconTX;
	TextureManager MagicSightOnTX;
	TextureManager MagicSightOffTX;
	TextureManager ShadowballIconTX;
	TextureManager FireballSheetTX;
	TextureManager ShadowballSheetTX;
	TextureManager TreeTX;
	TextureManager HouseTX;
	TextureManager CWallTX;
	TextureManager VWallTX;
	TextureManager HWallTX;
	TextureManager MagicPortalTX;
	TextureManager RiverTX;
	TextureManager Boulder2TX;
	TextureManager WoodTileTX;
	TextureManager Boulder1TX;
	TextureManager WaterTX;
	TextureManager GrassTX;
	TextureManager VertInHouseDoorTX;
	TextureManager HorizInHouseDoorTX;
	TextureManager LChairTX;
	TextureManager RChairTX;
	TextureManager TableTX;
	TextureManager BarBack2TX;
	TextureManager BarBack1TX;
	TextureManager BarCounterTX;
	TextureManager BedTX;
	TextureManager HouseDoorTX;
	TextureManager HouseWallTX;
	TextureManager SwingingSwordTX;
	TextureManager DeadGuyTX;
	TextureManager BirminghamTX;
};

#endif