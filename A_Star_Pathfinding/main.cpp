// This is a program to test the logic and basic principal of A* pathfinding
// Written by James McAdam
// Sources:
// http://www.policyalmanac.org/games/aStarTutorial.htm
//

// Key includes
#include<iostream>
#include<vector>
#include<cmath> // using the abs
#include "classes.h"

// all this code is within the namespace std
using namespace std;

// All the required data for testing
// Represents a possible map.
const int ROWSIZE = 10;
const int COLUMNSIZE = 10;

char map[ROWSIZE][COLUMNSIZE] =	{ { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
								  { 'X', 'X', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ' },
								  { ' ', ' ', ' ', 'X', 'X', 'X', ' ', ' ', ' ', ' ' },
								  { ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ' },
								  { ' ', 'X', 'X', 'X', ' ', 'X', 'X', 'X', 'X', 'X' },
								  { ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ' },
								  { 'X', 'X', ' ', 'X', 'X', 'X', 'X', 'X', ' ', ' ' },
								  { ' ', ' ', ' ', 'X', ' ', ' ', ' ', 'X', ' ', ' ' },
								  { ' ', 'X', 'X', 'X', ' ', 'X', ' ', 'X', ' ', ' ' },
								  { ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ' } };

// start and goal definition
location start(0, 0);
location goal(9, 9);

// Lists for the algorithm
vector<location> openList;
vector<location> closedList;

#include "functions.h"

// Main Definintion ***********************************************************************************************************
void main()
{
	drawmap(); // draw the blank map

	cout << endl << endl << "The pathfinding A* is running." << endl << endl;

	pathfind(start, goal); // find the path

	updateMap(); // update with the path shown

	drawmap(); // draw the blank map

	char q;
	cin >> q;
}




