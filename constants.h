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
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  1200;               // width of game in pixels
const UINT GAME_HEIGHT = 680;               // height of game in pixels

// Game
const double PI = 3.14159265;
const double TPI = 2*PI;
const double HPI = 0.5*PI;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations

// Image Files

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
const char FX[]   = "fx";


#endif
