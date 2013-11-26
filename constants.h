/***************************************************************
Constants header file

Last Modified 11/14/2013

***************************************************************/

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <string>
using std::string;

//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
    if (ptr)
    { 
        ptr->Release(); 
        ptr = NULL;
    }
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
    if (ptr)
    { 
        delete ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
    if (ptr)
    { 
        delete[] ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
    if (ptr)
        ptr->onLostDevice(); 
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
    if (ptr)
        ptr->onResetDevice(); 
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility

//=============================================================================
//                  Constants
//=============================================================================

// Window
const char CLASS_NAME[] = "Southfall";
const char GAME_TITLE[] = "Southfall";
const bool FULLSCREEN = false;              // Windowed or fullscreen
const UINT SCREEN_WIDTH =  1200;            // Width of screen in pixels
const UINT SCREEN_HEIGHT = 680;				// Height of screen in pixels

// Game
const double PI = 3.14159265;
const double TPI = 2*PI;
const double HPI = 0.5*PI;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations

const float DIAG_MULT = 1/sqrt(2.0f);		//	1/sqrt(2)
const UINT TILE_SIZE = 64;					// Width of a tile in pixels
const float INVTILE_SIZE = 1.0/TILE_SIZE;	// Inverse of tile size
const float DEFAULT_SCALE = TILE_SIZE/32;	// Default scale of Images
const UINT HTILE_SIZE = 0.5*TILE_SIZE;
const UINT HSCREEN_WIDTH = 0.5*SCREEN_WIDTH;
const UINT HSCREEN_HEIGHT = 0.5*SCREEN_HEIGHT;

// Image Files

// Characters
const char CHARACTER1_SHEET[] = "..\\source\\Images\\Entities\\Character1Sheet.png";
const char CHARACTER2_SHEET[] = "..\\source\\Images\\Entities\\Character2Sheet.png";
const char GOBLIN1_SHEET[] = "..\\source\\Images\\Entities\\Goblin1Sheet.png";
const char WRAITH1_SHEET[] = "..\\source\\Images\\Entities\\Wraith1Sheet.png";
const char DEADGUY[] = "..\\source\\Images\\Entities\\DEADGUY.png";
 // Terrain
const char GRASS1[] = "..\\source\\Images\\Terrain\\Grass1.png";
const char SAND1[] = "..\\source\\Images\\Terrain\\Sand1.png";
const char ROCKSURFACE[] = "..\\source\\Images\\Terrain\\Rockfloor1.png";
const char CAVEWALL[] = "..\\source\\Images\\CaveWall.png";
const char TREE1[] = "..\\source\\Images\\Terrain\\Tree1.png";
const char CACTUS1[] = "..\\source\\Images\\Terrain\\Cactus1.png";
const char BOULDER1[] = "..\\source\\Images\\Terrain\\Boulder1.png";
const char BOULDER2[] = "..\\source\\Images\\Terrain\\Boulder2.png";
const char RIVER1[] = "..\\source\\Images\\Terrain\\River1.png";
// Structures
const char WOODTILE1[] = "..\\source\\Images\\Structures\\WoodFloor1.png";
const char HOUSEWALL1[] = "..\\source\\Images\\Structures\\HouseWall1.png";
const char HOUSEDOOR1[] = "..\\source\\Images\\Structures\\HouseDoor1.png";
const char HORIZINHOUSEDOOR1[] = "..\\source\\Images\\Structures\\\\InHouseHorizDoor1.png";
const char VERTINHOUSEDOOR1[] = "..\\source\\Images\\Structures\\\\InHouseVertDoor1.png";
const char BARCOUNTER[] = "..\\source\\Images\\Structures\\Counter1.png";
const char LOWERBARBACK[] = "..\\source\\Images\\Structures\\LowerBarBackdrop.png";
const char BARBACKDROP[] = "..\\source\\Images\\Structures\\BarBackdrop.png";
const char TABLE[] = "..\\source\\Images\\Structures\\Table1.png";
const char RIGHTCHAIR[] = "..\\source\\Images\\Structures\\RightChair.png";
const char LEFTCHAIR[] = "..\\source\\Images\\Structures\\LeftChair.png";
const char BED1[] = "..\\source\\Images\\Structures\\Bed1.png";
const char HWALL[] = "..\\source\\Images\\Structures\\HorizontalWallPiece.png";
const char VWALL[] = "..\\source\\Images\\Structures\\VerticalWallPiece.png";
const char CWALL[] = "..\\source\\Images\\Structures\\CornerWallPiece.png";
// Structure Exteriors
const char HOUSE1[] = "..\\source\\Images\\StructureExteriors\\House1.png";
//Objects
const char MAGICPORTAL1[] = "..\\source\\Images\\Objects\\MagicPortal.png";
const char FIREBALLSHEET[] = "..\\source\\Images\\Objects\\FireballSheet.png";
const char SHADOWBALLSHEET[] = "..\\source\\Images\\Objects\\ShadowballSheet.png";
const char SWINGINGSWORD[] = "..\\source\\Images\\Objects\\SwingingSwordSheet.png";
// Icons
const char IMPEDEEFFECTICON[] = "..\\source\\Images\\Icons\\ImpedeEffectIcon.png";
const char PORTALOPEN[] = "..\\source\\Images\\Icons\\PortalOpen.png";
const char PORTALCLOSE[] = "..\\source\\Images\\Icons\\PortalClose.png";
const char SWORDICON[] = "..\\source\\Images\\Icons\\SwordIcon1.png";
const char BLINKICON[] = "..\\source\\Images\\Icons\\BlinkIcon1.png";
const char FIREBALLICON[] = "..\\source\\Images\\Icons\\FireballIcon.png";
const char MAGICSIGHTONICON[] = "..\\source\\Images\\Icons\\MagicSightOnIcon.png";
const char MAGICSIGHTOFFICON[] = "..\\source\\Images\\Icons\\MagicSightOffIcon.png";
const char SHADOWBALLICON[] = "..\\source\\Images\\Icons\\ShadowballIcon.png";
// Other
const char GAMEMENUBACK[] = "..\\source\\Images\\Other\\GameMenuBackground.png";
const char BIRMINGHAM[] = "..\\source\\Images\\Other\\Birmingham.png";
const char END_IMAGE[] = "..\\source\\Images\\Other\\EndScreen1.png";
const char TEXTBOX[] = "..\\source\\Images\\Other\\textBox.png";
const char TEXTBOX_ARROW[] = "..\\source\\Images\\Other\\textBoxArrow.png";
const char SOUTHFALLFONT[] = "..\\source\\Images\\Other\\SouthfallFont.png";
const char ESBURGFONT[] = "..\\source\\Images\\Other\\EsburgFont.png";
const char WESELLYNFONT[] = "..\\source\\Images\\Other\\WesellynFont.png";
const char NORSTAFFFONT[] = "..\\source\\Images\\Other\\NorstaffFont.png";

// Worlds
const string BAR1STRUCTURE = "..\\source\\Worlds\\Bar1.txt";
const string BAR2STRUCTURE = "..\\source\\Worlds\\Bar2.txt";
const string HOUSE1STRUCTURE = "..\\source\\Worlds\\House1.txt";
const string HOUSE2STRUCTURE = "..\\source\\Worlds\\House2.txt";
const string HOUSE3STRUCTURE = "..\\source\\Worlds\\House3.txt";
const string HOUSE4STRUCTURE = "..\\source\\Worlds\\House4.txt";
const string SOUTHFALLMAP = "..\\source\\Worlds\\TTotalMap.txt";
// Texts
const char INTRO_TEXT[] = "..\\source\\Worlds\\intro.txt";

// Sound Files
const char COLLIDE[] = "Collision";
const char SELECT[] = "Blip_Select";
const char SOUTHFALL_THEME[] = "Background";
const char BATTLE[] = "Battle";
const char BATTLE_INTRO[] = "Battle Intro";
const char MAIN_THEME[] = "Background2";
const char HOOH[] = "Hooh";
const char DAMAGE[] = "Damage";
const char ALERT[] = "Intro_alert";
const char FIREBALL_SOUND[] = "Fireball";
const char LIGHTNING[] = "Lightning";
const char BIRMINGHAM_SOUND[] = "Birmingham";
const char WIN[] = "Win";

// Audio
const char WAVE_BANK[]  = "..\\source\\Audio\\Win\\Wave Bank.xwb";
const char SOUND_BANK[] = "..\\source\\Audio\\Win\\Sound Bank.xsb";

// key mappings
const UCHAR CONSOLE_KEY		= VK_OEM_3;		// ~ key
const UCHAR ESC_KEY			= VK_ESCAPE;    // Escape key
const UCHAR ALT_KEY			= VK_MENU;      // Alt key
const UCHAR ENTER_KEY		= VK_RETURN;	// Enter key
const UCHAR R_SHIFT_KEY		= VK_SHIFT;		// Shift key
const UCHAR SPACE_KEY		= VK_SPACE;		// Space key
const UCHAR WKEY			= 0x57;			// 'w'
const UCHAR AKEY			= 0x41;			// 'a'
const UCHAR SKEY			= 0x53;			// 's'
const UCHAR DKEY			= 0x44;			// 'd'
const UCHAR ZOOM_IN			= 0x49;			// The 'i' key
const UCHAR ZOOM_OUT		= 0x4f;			// The 'o' key
const UCHAR M_KEY			= 0x4D;			// The 'm' key
const UCHAR F_KEY			= 0x46;			// The 'f' key
const UCHAR T_KEY			= 0x54;			// The 't' key
const UCHAR P_KEY			= 0x50;			// The 'P' key
const UCHAR O_KEY			= 0x4F;			// The 'O' key

#endif
