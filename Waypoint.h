#ifndef _WAYPOINT_H
#define _WAYPOINT_H

#include "graphics.h"

struct Waypoint
{
	Waypoint(VECTOR2 position) : position(position), next(0), radius(1) {};
	Waypoint(float x, float y) : position(VECTOR2(x,y)), next(0), radius(1) {};
	Waypoint(VECTOR2 position, Waypoint* next) : position(position), next(next), radius(1) {};
	Waypoint(float x, float y, Waypoint* next) : position(VECTOR2(x,y)), next(next), radius(1) {};
	~Waypoint();

	VECTOR2 position;
	Waypoint* next;
	float radius;	// How close you have to be before youre "at" the waypoint
};

#endif