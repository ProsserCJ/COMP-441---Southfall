#ifndef _MAZE_SOLVER_H
#define _MAZE_SOLVER_H

#include "entity.h"
using entityNS::DIR;

const int SIGHTRANGE = 8;
const int ARRAYWIDTH = 2*SIGHTRANGE+1;
const float SOLVEDELAY = 0.3f;

class MazeSolver
{
public:
	DIR solve(World* W, VECTOR2 target, VECTOR2 start);
	void update(float frameTime);

private:
	inline int number(int x, int y);

	int SearchArray[ARRAYWIDTH+2][ARRAYWIDTH+2];

	DIR last;

	float time;

};

#endif