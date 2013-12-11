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
	Image BirmSpriteIM;
	Image Character1IM;
	Image NPC1IM;
	Image TextBoxIM;
	Image Goblin1IM, WraithIM;
	Image TextBoxArrowIM;
	Image SouthfallFontIM[4];
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
	Image SandIM;
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
	Image CactusIM;
	Image CavewallIM;
	Image CavefloorIM;
	Image HouseWallIM;
	Image HouseDoorIM;
	Image BedIM;
	Image BarCounterIM;
	Image BarBack1IM;
	Image BarBack2IM;
	Image SalsIM;
	Image TableIM;
	Image RChairIM;
	Image LChairIM;
	Image HorizInHouseDoorIM;
	Image VertInHouseDoorIM;
	Image SwingingSwordIM;
	Image DeadGuyIM;
	Image BirminghamIM;
	Image EndIM;
private:
	bool _initialized;

	// Textures
	TextureManager BirmSpriteTX;
	TextureManager Character1TX;
	TextureManager NPC1TX;
	TextureManager Goblin1TX;
	TextureManager WraithTX;
	TextureManager TextBoxTX;
	TextureManager TextBoxArrowTX;
	TextureManager SouthfallFontTX[4];
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
	TextureManager CactusTX;
	TextureManager CavewallTX;
	TextureManager CavefloorTX;
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
	TextureManager SandTX;
	TextureManager VertInHouseDoorTX;
	TextureManager HorizInHouseDoorTX;
	TextureManager LChairTX;
	TextureManager RChairTX;
	TextureManager TableTX;
	TextureManager BarBack2TX;
	TextureManager BarBack1TX;
	TextureManager BarCounterTX;
	TextureManager SalsTX;
	TextureManager BedTX;
	TextureManager HouseDoorTX;
	TextureManager HouseWallTX;
	TextureManager SwingingSwordTX;
	TextureManager DeadGuyTX;
	TextureManager BirminghamTX;
	TextureManager EndTX;

	void _initializeEntities(Graphics* graphics);
	void _initializeIcons(Graphics* graphics);
	void _initializeObjects(Graphics* graphics);
	void _initializeOther(Graphics* graphics);
	void _initializeStructures(Graphics* graphics);
	void _initializeStructureExteriors(Graphics* graphics);
	void _initializeTerrain(Graphics* graphics);
	
};

#endif