#include "MazeSolver.h"

#include "World.h"

DIR MazeSolver::solve(World* W, VECTOR2 target, VECTOR2 start)
{
	// Initialize search array
	for(int x=-SIGHTRANGE; x<=SIGHTRANGE; x++)
		for(int y=-SIGHTRANGE; y<=SIGHTRANGE; y++)
		{// Center SearchArray around target
			if(0 < target.x+x && target.x+x < W->getWidth() && 0 < target.y+y && target.y+y < W->getHeight()
				&& W->getTile((int)(target.x)+x,(int)(target.y)+y)->isTraversable())
				SearchArray[x+SIGHTRANGE+1][y+SIGHTRANGE+1] = INT_MAX;
			else SearchArray[x+SIGHTRANGE+1][y+SIGHTRANGE+1] = -1;
		}
	// Set borders
	for(int i=0; i<ARRAYWIDTH+2; i++)
	{
		SearchArray[i][0] = INT_MAX;
		SearchArray[i][ARRAYWIDTH+1] = INT_MAX;
		SearchArray[0][i] = INT_MAX;
		SearchArray[ARRAYWIDTH+1][i] = INT_MAX;
	}
	SearchArray[SIGHTRANGE+1][SIGHTRANGE+1] = 0; // Target square is 0
	// Find paths
	bool revising = true;
	int counts = 0;
	while(revising)
	{
		revising = false;
		for(int x=1; x<ARRAYWIDTH; x++)
			for(int y=1; y<ARRAYWIDTH; y++)
			{
				int num = number(x,y);
				int& entry = SearchArray[x][y];
				if(entry != -1 && num < entry)
				{
					entry = num;
					revising = true;
				}
			}
		counts++;
	}
	// Pick best square to go on
	int CX = (int)start.x - (int)target.x + (SIGHTRANGE) + 1;
	int CY = (int)start.y - (int)target.y + (SIGHTRANGE) + 1;
	int n = SearchArray[CX][CY];

	if(n == INT_MAX) return DIR::NONE;
	else if(0 <= SearchArray[CX-1][CY-1] && SearchArray[CX-1][CY-1] < n) return DIR::UP_LEFT;
	else if(0 <= SearchArray[CX][CY-1] && SearchArray[CX][CY-1] < n) return DIR::UP;
	else if(0 <= SearchArray[CX+1][CY-1] && SearchArray[CX+1][CY-1] < n) return DIR::UP_RIGHT;
	else if(0 <= SearchArray[CX-1][CY] && SearchArray[CX-1][CY] < n) return DIR::LEFT;
	else if(0 <= SearchArray[CX+1][CY] && SearchArray[CX+1][CY] < n) return DIR::RIGHT;
	else if(0 <= SearchArray[CX-1][CY+1] && SearchArray[CX-1][CY+1] < n) return DIR::DOWN_LEFT;
	else if(0 <= SearchArray[CX][CY+1] && SearchArray[CX][CY+1] < n) return DIR::DOWN;
	else if(0 <= SearchArray[CX+1][CY+1] && SearchArray[CX+1][CY+1] < n) return DIR::DOWN_RIGHT;
	else return DIR::NONE;
}

int MazeSolver::number(int x, int y)
{
	int min = INT_MAX;
	for(int i=0; i<3; i++)
	{
		if(SearchArray[x-1+i][y-1] >= 0) min = min(min, SearchArray[x-1+i][y-1]);
		if(SearchArray[x-1+i][y+1] >= 0) min = min(min, SearchArray[x-1+i][y+1]);
		if(SearchArray[x-1][y-1+i] >= 0) min = min(min, SearchArray[x-1][y-1+i]);
		if(SearchArray[x+1][y-1+i] >= 0) min = min(min, SearchArray[x+1][y-1+i]);
	}
	if(min == INT_MAX) return INT_MAX;
	return min+1;
}