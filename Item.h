#ifndef _ITEM_H
#define _ITEM_H

#include "image.h"

namespace itemNS
{
	enum ITEMTYPE{MONEY, WEAPON, SPELL};
}; 
using namespace itemNS;

class Item 
{
public:
	Item() {};
	~Item() {};

	ITEMTYPE getItemType()	{return type;}
	int getValue()			{return value;}

private:
	Image* icon;		// The icon to display the item as
	
	int value;			// Monetary value
	
	bool claimable;		// Can the item be picked up
	VECTOR2 position;	// If the item is on the map

	ITEMTYPE type;
};

#endif