
#pragma once

// ******************************************************************************************************************************************************************
// FUNCTION DEFININTIONS
// ******************************************************************************************************************************************************************

// Pathfininding Constants
const int VHMOVE = 10; // vertical/Horizontal move cost
const int DMOVE = 14; // diagonal move cost



					  // returns the heuristic value required for the alogrithm - estimated shortest distance to goal ************************************************
int heuristic(location current) // using mannhatten method
{
	int horizontal_dist = abs(current.xpos - goal.xpos);
	int vertical_dist = abs(current.ypos - goal.ypos);
	int diagonal_dist = 0;

	// the smaller of the 2 represents the max possible diagonals 
	if (horizontal_dist > vertical_dist)
	{
		diagonal_dist = vertical_dist;
	}
	else if (horizontal_dist < vertical_dist)
	{
		diagonal_dist = horizontal_dist;
	}
	else if (horizontal_dist == vertical_dist)
	{ 
		diagonal_dist = horizontal_dist;
	}

	// the difference represents the remaing horizontal/vertical
	int horvert_dist = abs(horizontal_dist - vertical_dist);

	// return the combined cost
	return (horvert_dist*VHMOVE + diagonal_dist*DMOVE);
}
// **********************************************************************************




// Find the square in the open list with the smallest f cost value ***************************************************
location findLowestFcost()
{
	location lowest = openList[0]; // start with the first entry in the Open List

	for (unsigned int i = 1; i < openList.size(); i++) // find the lowest f value on the openlist
	{
		if (openList[i].value.fCost < lowest.value.fCost)
		{
			lowest = openList[i];
		}
	}
	return lowest; // return the lowest value
}
// **********************************************************************************



// check that the locatioin is in the array ***************************************************
bool boundscheck(int row, int column)
{
	if (row > -1 && column > -1 && row < (ROWSIZE) && column < (COLUMNSIZE))
	{
		return true;
	}
	else
	{
		return false;
	}
}
// **********************************************************************************



// Check if target is on closed list **********************************************************************************
bool checkClosedList(location target)
{
	for (unsigned int i = 0; i < closedList.size(); i++)
	{
		if (closedList[i] == target) // == overloaded for location class
		{
			return true;
		}
	}
	return false;
}
// **********************************************************************************


// Check if target is on open list **********************************************************************************
bool checkOpenList(location target)
{
	for (unsigned int i = 0; i < openList.size(); i++)
	{
		if (openList[i] == target) // == overloaded for location class
		{
			return true;
		}
	}
	return false;
}
// **********************************************************************************




// saves the new values of test in the vector **********************************************************************************
void save(location newvalues)
{
	for (unsigned int i = 0; i < openList.size(); i++)
	{
		if (openList[i] == newvalues) // == overloaded for location class
		{
			openList[i] = newvalues;
		}
	}
}
// **********************************************************************************




// find it's a diagonal or horizontal/verical move and return the cost **********************************************************************************
int gCostCalc(location test, location current)
{
	if (test.xpos != current.xpos && test.ypos != current.ypos) // If both row and columns differ must be diagonal
	{
		return DMOVE;
	}
	else
	{
		return VHMOVE;
	}
}
// **********************************************************************************



// Update the interal cost values **********************************************************************************
void updateCostValue(location& test, location current)
{
	test.value.parentx = current.xpos; // make the current the parent of this square being tested
	test.value.parenty = current.ypos;  // make the current the parent of this square being tested
	test.value.hCost = heuristic(test);
	test.value.gCost = gCostCalc(test, current);
	test.value.fCost = test.value.hCost + test.value.gCost;
}
// **********************************************************************************



// to detail ***************************************************
void checksurrounding(location current)
{
	// variables declarations
	location test(0, 0);

	for (int ROW = -1; ROW < 2; ++ROW) // 2 for loops to check all 8 squares around the current locaiton
	{
		for (int COLUMN = -1; COLUMN < 2; ++COLUMN)
		{
			if ((ROW != 0 && COLUMN != 0))
				//{
					// Calculate the position of the square of interest
				test.ypos = current.ypos + ROW;
			test.xpos = current.xpos + COLUMN;

			// check that square actually exists and is walkble and isn't on the closed list, and isn't the middle square
			if (boundscheck(test.xpos, test.ypos) && map[test.xpos][test.ypos] != 'X' && !checkClosedList(test)) // This seems to mess it up
			{
				// If it's not on the openList add it
				if (checkOpenList(test) == false)
				{
					updateCostValue(test, current); // calculate all the costs
					openList.push_back(test); // add it to the list
				}
				else // it's already on the list
				{
					if (test.value.gCost > gCostCalc(test, current)) // check if it's a better route
					{
						updateCostValue(test, current); // if not recalcuate the better route
						save(test); // save it to the open list
					}
				}

			}
		}
	}
}
// **********************************************************************************



// Delete from the openlist **********************************************************************************
void deletefromopen(location target) // remove the current square from the open list
{
	for (unsigned int i = 0; i < openList.size(); i++)
	{
		if (openList[i] == target) // == overloaded for location class
		{
			openList.erase(openList.begin() + i);
		}
	}
}
// **********************************************************************************




// Function to draw the map to the screen ************************************************
void drawmap()
{

	map[start.xpos][start.ypos] = 'S'; // mark the start and finish
	map[goal.xpos][goal.ypos] = 'G';

	cout << "________________________" << endl << endl; // cosmetic

	for (unsigned int i = 0; i < 10; i++)
	{

		cout << "| "; // cosmetic

		for (unsigned int j = 0; j < 10; j++)
		{
			cout << map[i][j] << " "; // Draw the map with a space between each array entry
		}

		cout << " |" << endl; // Add a new line after each row 

	}

	cout << "________________________"; // cosmetic

}
// **********************************************************************************





void updateMap()
{
	location pathNode = closedList[closedList.size() - 1]; // start with the last entry on the closed list. i.e. goal.

	while (pathNode != start)
	{
		map[pathNode.xpos][pathNode.ypos] = 'O'; // mark the path
		for (unsigned int i = closedList.size() - 1; i < -1; i--) // check the list
		{
			if (closedList[i].xpos == pathNode.value.parentx && closedList[i].ypos == pathNode.value.parenty) // find the parent
			{
				pathNode = closedList[i]; // set the patNode the the parent, i.e. the next part of the path.
				break; // break out of the for loop
			}
		}
	}

	map[start.xpos][start.ypos] = 'S'; // mark the start and finish
	map[goal.xpos][goal.ypos] = 'G';

}



// The main Pathfinding algorithm **********************************************************************************
void pathfind(location start, location goal)
{

	// Add the starting square to the open list
	openList.push_back(start);

	// Variables
	location currentSquare = start;

	while (!checkClosedList(goal) && openList.size() > 0) // Main Algorithm loop
	{
		currentSquare = findLowestFcost(); // find the lowest f cost on the list
		checksurrounding(currentSquare); // check and calculate the cost of all the surroundings
		closedList.push_back(currentSquare); // add the current square to the closed list
		deletefromopen(currentSquare); // remove the current square from the open list
		// updateMap();
			// drawmap();
	}
}
// **********************************************************************************






