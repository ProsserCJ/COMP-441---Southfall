#include "Waypoint.h"

Waypoint::~Waypoint()
{
	safeDelete<Waypoint*>(next);
}