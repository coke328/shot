#pragma once
#include "raylib.h"
#include <vector>
#include <iostream>

struct Vecbool
{
	Vector2 point;
	bool collsitu;
	bool iscollid;
};

class boundary
{
public:
	float a, b, c;//ax+by+c=0
	Vector2 Points[2];
	bool isStatic;
	float* bsaves;
	bool* ps;
	boundary();
	boundary(float x1, float y1, float x2, float y2, bool st);
	void boundaryInit(float x1, float y1, float x2, float y2, bool st);
	void removeMemory();
	void movePos(Vector2 mPos);
	Vecbool isCollid(boundary& bound, int j, int k);
};



//boundbool isCollid(boundary bound1, boundary bound2);
Vecbool isboundmeet(boundary bound1, boundary bound2);
