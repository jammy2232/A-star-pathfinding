// This is a program to test the logic and basic principal of A* pathfinding
// Written by James McAdam
// Sources:
// http://www.policyalmanac.org/games/aStarTutorial.htm
//

// Key includes
#include<iostream>
#include<vector>
#include<cmath> // using the abs
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "classes.h"

// all this code is within the namespace std
using namespace std;

// All the required data for testing
// Represents a possible map.
const int ROWSIZE = 10;
const int COLUMNSIZE = 10;

char levelMap[ROWSIZE][COLUMNSIZE] =	{ { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
										  { 'X', ' ', 'X', 'X', 'X', ' ', ' ', ' ', ' ', ' ' },
										  { ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
										  { 'X', ' ', 'X', ' ', ' ', 'X', 'X', 'X', 'X', 'X' },
										  { ' ', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
										  { 'X', ' ', 'X', 'X', 'X', 'X', ' ', ' ', ' ', ' ' },
										  { ' ', 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
										  { 'X', ' ', 'X', ' ', 'X', ' ', 'X', 'X', 'X', 'X' },
										  { ' ', 'X', 'X', ' ', 'X', ' ', ' ', ' ', ' ', ' ' },
										  { ' ', ' ', ' ', 'X', 'X', ' ', ' ', ' ', ' ', ' ' } };

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
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "A* Algorithm Test"); // Create a window 
	sf::RenderWindow* pwindow = &window;

	pathfind(start, goal); // find the path
	updateMap();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		drawmap(pwindow); // draw the blank map

		window.display();
	}
}



