#pragma once
#include "raylib.h"
#include <vector>
#include <iostream>

struct vecbool
{
	Vector2 point;
	bool iscollid;
};

class boundary
{
public:
	float a, b, c;//ax+by+c=0
	Vector2 Points[2];
	bool isStatic;
	bool p;
	float* bsaves;
	boundary();
	boundary(float x1, float y1, float x2, float y2, bool st);
	void boundaryInit(float x1, float y1, float x2, float y2, bool st);
	vecbool isCollid(boundary bound, int j);
};



//boundbool isCollid(boundary bound1, boundary bound2);
Vector2 boundmeet(boundary bound1, boundary bound2);
