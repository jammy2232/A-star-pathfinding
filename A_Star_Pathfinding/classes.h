#pragma once

class location;

// Class definition for coordinates system **************************************************
class cost
{
public:
	cost(int g = 0, int h = 0, int f = 0);
	int hCost;
	int gCost;
	int fCost;
	int parentx; // workaround for issues with using location name
	int parenty;
};

cost::cost(int g, int h, int f)
{
	hCost = 0;
	gCost = 0;
	fCost = 0;
}

//************************************************************************

// Class definition for coordinates system **************************************************
class location
{
public:
	location(int x = 0, int y = 0);
	friend bool operator== (const location &l1, const location &l2);
	friend bool operator!= (const location &l1, const location &l2);
	int xpos;
	int ypos;
	cost value;
};

location::location(int x, int y)
{
	xpos = x;
	ypos = y;
}

bool operator== (const location &l1, const location &l2)
{
	return (l1.xpos == l2.xpos && l1.ypos == l2.ypos);
}

bool operator!= (const location &l1, const location &l2)
{
	return (l1.xpos != l2.xpos || l1.ypos != l2.ypos);
}

//************************************************************************