#include "ImageLibrary.h"

void ImageLibrary::initialize(Graphics* graphics)
{
	if(_initialized) return;
	
	_initializeEntities(graphics);
	_initializeIcons(graphics);
	_initializeObjects(graphics);
	_initializeOther(graphics);
	_initializeStructures(graphics);
	_initializeStructureExteriors(graphics);
	_initializeTerrain(graphics);
	
	_initialized = true;
}

void ImageLibrary::_initializeEntities(Graphics* graphics)
{
	// Character 1
	if(!Character1TX.initialize(graphics, CHARACTER2_SHEET))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Character 1 texture"));
	if(!Character1IM.initialize(graphics, 32, 32, 8, &Character1TX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Character 1 image"));
	// Dead guy
	if(!DeadGuyTX.initialize(graphics, DEADGUY))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Dead Guy texture"));
	if(!DeadGuyIM.initialize(graphics, 32, 32, 1, &DeadGuyTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Dead Guy image"));
	// Goblin 1
	if(!Goblin1TX.initialize(graphics, GOBLIN1_SHEET))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Goblin 1 texture"));
	if(!Goblin1IM.initialize(graphics, 32, 32, 8, &Goblin1TX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Goblin 1 image"));
	// Wraith 
	if(!WraithTX.initialize(graphics, WRAITH1_SHEET))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Wraith texture"));
	if(!WraithIM.initialize(graphics, 32, 96, 8, &WraithTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Wraith image"));
}

void ImageLibrary::_initializeIcons(Graphics* graphics)
{
	// Impede effect
	if(!ImpedeEffectTX.initialize(graphics, IMPEDEEFFECTICON))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Impede effect texture"));
	if(!ImpedeEffectIM.initialize(graphics, 0, 0, 0, &ImpedeEffectTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Impede effect image"));
	// Portal Opening
	if(!PortalOpenTX.initialize(graphics, PORTALOPEN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Portal open texture"));
	if(!PortalOpenIM.initialize(graphics, 0, 0, 0, &PortalOpenTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Portal open image"));
	// Portal Exit
	if(!PortalCloseTX.initialize(graphics, PORTALCLOSE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Portal close texture"));
	if(!PortalCloseIM.initialize(graphics, 0, 0, 0, &PortalCloseTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Portal close image"));
	// Sword Icon
	if(!SwordIconTX.initialize(graphics, SWORDICON))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing SwordIcon texture"));
	if(!SwordIconIM.initialize(graphics, 0, 0, 0, &SwordIconTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing SwordIcon image"));
	// Blink Icon
	if(!BlinkIconTX.initialize(graphics, BLINKICON))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing BlinkIcon texture"));
	if(!BlinkIconIM.initialize(graphics, 0, 0, 0, &BlinkIconTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing BlinkIcon image"));
	// Fireball Icon
	if(!FireballIconTX.initialize(graphics, FIREBALLICON))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing FireballIcon texture"));
	if(!FireballIconIM.initialize(graphics, 0, 0, 0, &FireballIconTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing FireballIcon image"));
	// Magic Sight On Icon
	if(!MagicSightOnTX.initialize(graphics, MAGICSIGHTONICON))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing MagicSightOn texture"));
	if(!MagicSightOnIM.initialize(graphics, 0, 0, 0, &MagicSightOnTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing MagicSightOn image"));
	// Magic Sight Off Icon
	if(!MagicSightOffTX.initialize(graphics, MAGICSIGHTOFFICON))
	  throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing MagicSightOff texture"));
	if(!MagicSightOffIM.initialize(graphics, 0, 0, 0, &MagicSightOffTX))
	  throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing MagicSightOff image"));
	// Shadowball Icon
	if(!ShadowballIconTX.initialize(graphics, SHADOWBALLICON))
	  throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Shadowball texture"));
	if(!ShadowballIconIM.initialize(graphics, 0, 0, 0, &ShadowballIconTX))
	  throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Shadowball image"));
}

void ImageLibrary::_initializeObjects(Graphics* graphics)
{
	// Swinging sword
	if(!SwingingSwordTX.initialize(graphics, SWINGINGSWORD))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing SwingingSword texture"));
	if(!SwingingSwordIM.initialize(graphics, 64, 32, 8, &SwingingSwordTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing SwingingSword image"));	
	// Fireball projectile
	if(!FireballSheetTX.initialize(graphics, FIREBALLSHEET))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Fireball sheet texture"));
	if(!FireballSheetIM.initialize(graphics, 16, 16, 4, &FireballSheetTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Fireball sheet image"));
	// Shadowball projectile
	if(!ShadowballSheetTX.initialize(graphics, SHADOWBALLSHEET))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Shadowball sheet texture"));
	if(!ShadowballSheetIM.initialize(graphics, 16, 16, 4, &ShadowballSheetTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Shadowball sheet image"));
	// Magic Portal
	if(!MagicPortalTX.initialize(graphics, MAGICPORTAL1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Magic portal texture"));
	if(!MagicPortalIM.initialize(graphics, 32, 32, 4, &MagicPortalTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Magic portal image"));
}

void ImageLibrary::_initializeOther(Graphics* graphics)
{
	//Set up region fonts
	if(!SouthfallFontTX[0].initialize(graphics, SOUTHFALLFONT))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing southfallFont texture"));
	if(!SouthfallFontTX[1].initialize(graphics, ESBURGFONT))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing esburgFont texture"));
	if(!SouthfallFontTX[2].initialize(graphics, WESELLYNFONT))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wesellynFont texture"));
	if(!SouthfallFontTX[3].initialize(graphics, NORSTAFFFONT))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing norstaffFont texture"));
	for(int i = 0; i < 4; ++i)
	{
		if(!SouthfallFontIM[i].initialize(graphics, 0, 0, 0, &SouthfallFontTX[i]))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing southfallFont image: " + i));
		SouthfallFontIM[i].setX(SCREEN_WIDTH/2-SouthfallFontIM[0].getWidth()/2);
		SouthfallFontIM[i].setY(SCREEN_HEIGHT/4-SouthfallFontIM[0].getHeight()/2);
	}
	// Textbox
	if(!TextBoxTX.initialize(graphics, TEXTBOX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Textbox texture"));
	if(!TextBoxIM.initialize(graphics, 1000, 200, 1, &TextBoxTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Textbox image"));
	// Textbox arrow
	if(!TextBoxArrowTX.initialize(graphics, TEXTBOX_ARROW))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Textbox arrow texture"));
	if(!TextBoxArrowIM.initialize(graphics, 35, 20, 4, &TextBoxArrowTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Textbox arrow image"));
	// Birmingham
	if(!BirminghamTX.initialize(graphics, BIRMINGHAM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Birmingham texture"));
	if(!BirminghamIM.initialize(graphics, 0, 0, 0, &BirminghamTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Birmingham image"));	
	// End Screen
	if(!EndTX.initialize(graphics, END_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing End Screen texture"));
	if(!EndIM.initialize(graphics, SCREEN_WIDTH, SCREEN_HEIGHT, 0, &EndTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing End Screen image"));	
}

void ImageLibrary::_initializeStructures(Graphics* graphics)
{
	// Wood Floor 1
	if(!WoodTileTX.initialize(graphics, WOODTILE1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Wood Tile texture"));
	if(!WoodTileIM.initialize(graphics, 0, 0, 0, &WoodTileTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Wood Tile image"));
	// House Wall 1
	if(!HouseWallTX.initialize(graphics, HOUSEWALL1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing House Wall texture"));
	if(!HouseWallIM.initialize(graphics, 0, 0, 0, &HouseWallTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing House Wall image"));
	// House Door 1
	if(!HouseDoorTX.initialize(graphics, HOUSEDOOR1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing House Door texture"));
	if(!HouseDoorIM.initialize(graphics, 0, 0, 0, &HouseDoorTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing House Door image"));
	// Horizontal in-house Door 1
	if(!HorizInHouseDoorTX.initialize(graphics, HORIZINHOUSEDOOR1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Horizontal in House Door texture"));
	if(!HorizInHouseDoorIM.initialize(graphics, 32, 32, 2, &HorizInHouseDoorTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing House Door image"));
	// Vertical in-house Door 1
	if(!VertInHouseDoorTX.initialize(graphics, VERTINHOUSEDOOR1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Vertical in House Door texture"));
	if(!VertInHouseDoorIM.initialize(graphics, 32, 32, 2, &VertInHouseDoorTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Vertical in House Door image"));
	// Bed
	if(!BedTX.initialize(graphics, BED1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Bed texture"));
	if(!BedIM.initialize(graphics, 0, 0, 0, &BedTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Bed image"));
	// Bar Counter
	if(!BarCounterTX.initialize(graphics, BARCOUNTER))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Bar Counter texture"));
	if(!BarCounterIM.initialize(graphics, 0, 0, 0, &BarCounterTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Bar Counter image"));	
	// Bar Backdrop
	if(!BarBack1TX.initialize(graphics, BARBACKDROP))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Bar Backdrop 1 texture"));
	if(!BarBack1IM.initialize(graphics, 32, 32, 8, &BarBack1TX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Bar Backdrop 1 image"));	
	// Lower Bar Backdrop
	if(!BarBack2TX.initialize(graphics, LOWERBARBACK))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Lower Bar Backdrop texture"));
	if(!BarBack2IM.initialize(graphics, 0, 0, 0, &BarBack2TX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Lower Bar Backdrop image"));	
	// Table
	if(!TableTX.initialize(graphics, TABLE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing table texture"));
	if(!TableIM.initialize(graphics, 0, 0, 0, &TableTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing table image"));	
	// Right facing chair
	if(!RChairTX.initialize(graphics, RIGHTCHAIR))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing RChair texture"));
	if(!RChairIM.initialize(graphics, 0, 0, 0, &RChairTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing RChair image"));	
	// Right facing chair
	if(!LChairTX.initialize(graphics, LEFTCHAIR))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing LChair texture"));
	if(!LChairIM.initialize(graphics, 0, 0, 0, &LChairTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing LChair image"));	
	// Wood Tile
	if(!WoodTileTX.initialize(graphics, WOODTILE1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Wood Tile texture"));
	if(!WoodTileIM.initialize(graphics, 0, 0, 0, &WoodTileTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Wood Tile image"));
	// Horizontal Wall
	if(!HWallTX.initialize(graphics, HWALL))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing HWall texture"));
	if(!HWallIM.initialize(graphics, 0, 0, 0, &HWallTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing HWall image"));
	// Vertical Wall
	if(!VWallTX.initialize(graphics, VWALL))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing VWall texture"));
	if(!VWallIM.initialize(graphics, 0, 0, 0, &VWallTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing VWall image"));
	// Wall Corner
	if(!CWallTX.initialize(graphics, CWALL))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing CWall texture"));
	if(!CWallIM.initialize(graphics, 0, 0, 0, &CWallTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing CWall image"));
}

void ImageLibrary::_initializeStructureExteriors(Graphics* graphics)
{
	// House
	if(!HouseTX.initialize(graphics, HOUSE1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing House texture"));
	if(!HouseIM.initialize(graphics, 0, 0, 0, &HouseTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing House image"));
}

void ImageLibrary::_initializeTerrain(Graphics* graphics)
{
	// River
	if(!RiverTX.initialize(graphics, RIVER1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing River texture"));
	if(!RiverIM.initialize(graphics, 0, 0, 0, &RiverTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing River image"));
	// Grass
	if(!GrassTX.initialize(graphics, GRASS1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Grass texture"));
	if(!GrassIM.initialize(graphics, 0, 0, 0, &GrassTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Grass image"));
	// Sand
	if(!SandTX.initialize(graphics, SAND1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Sand texture"));
	if(!SandIM.initialize(graphics, 0, 0, 0, &SandTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Sand image"));
	// Cave floor
	if(!CavefloorTX.initialize(graphics, ROCKSURFACE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cave floor texture"));
	if(!CavefloorIM.initialize(graphics, 0, 0, 0, &CavefloorTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cave floor image"));
	// Tree
	if(!TreeTX.initialize(graphics, TREE1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Tree texture"));
	if(!TreeIM.initialize(graphics, 0, 0, 0, &TreeTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Tree image"));
	// Cactus
	if(!CactusTX.initialize(graphics, CACTUS1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cactus texture"));
	if(!CactusIM.initialize(graphics, 0, 0, 0, &CactusTX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cactus image"));
	// Boulder 1
	if(!Boulder1TX.initialize(graphics, BOULDER1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boulder texture"));
	if(!Boulder1IM.initialize(graphics, 0, 0, 0, &Boulder1TX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boulder image"));
	// Boulder 2
	if(!Boulder2TX.initialize(graphics, BOULDER2))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boulder2 texture"));
	if(!Boulder2IM.initialize(graphics, 0, 0, 0, &Boulder2TX))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boulder2 image"));
}