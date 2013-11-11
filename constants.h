// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 constants.h v1.1

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

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
const float DEFAULT_SCALE = TILE_SIZE/32;	// Default scale of images
const UINT HTILE_SIZE = 0.5*TILE_SIZE;
const UINT HSCREEN_WIDTH = 0.5*SCREEN_WIDTH;
const UINT HSCREEN_HEIGHT = 0.5*SCREEN_HEIGHT;

// Image Files
// Characters
const char CHARACTER1_SHEET[] = "Images\\Character1Sheet.png";
const char CHARACTER2_SHEET[] = "Images\\Character2Sheet.png";
// Tiles
const char GRASS1[] = "Images\\Grass1.png";
const char TREE1[] = "Images\\Tree1.png";
const char BOULDER1[] = "Images\\Boulder1.png";
const char BOULDER2[] = "Images\\Boulder2.png";
const char MAGICPORTAL1[] = "Images\\MagicPortal.png";
const char HOUSE1[] = "Images\\House1.png";
const char RIVER1[] = "Images\\River1.png";
const char WOODTILE1[] = "Images\\WoodFloor1.png";
const char HOUSEWALL1[] = "Images\\HouseWall1.png";
const char HOUSEDOOR1[] = "Images\\HouseDoor1.png";
const char HORIZINHOUSEDOOR1[] = "Images\\InHouseHorizDoor1.png";
const char VERTINHOUSEDOOR1[] = "Images\\InHouseVertDoor1.png";
const char BARCOUNTER[] = "Images\\Counter1.png";
const char HWALL[] = "Images\\HorizontalWallPiece.png";
const char VWALL[] = "Images\\VerticalWallPiece.png";
const char CWALL[] = "Images\\CornerWallPiece.png";
// NPC Interaction
const char TEXTBOX[] = "Images\\textBox.png";
const char TEXTBOX_ARROW[] = "Images\\textBoxArrow.png";

// Sound Files

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

// ADD FILE names for AUDIO here
const char WAVE_BANK[]  = "audio\\Win\\Wave Bank.xwb";
const char SOUND_BANK[] = "audio\\Win\\Sound Bank.xsb";

// ADD CUE name here
const char COLLIDE[] = "Collision";
const char SELECT[] = "Blip_Select";
const char BACKGROUND[] = "Background";
const char BATTLE[] = "Battle";
const char BATTLE_INTRO[] = "Battle Intro";
const char HOUSE[] = "Background2";


#endif
