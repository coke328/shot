#pragma once
#include <vector>
#include "boundary.h"

class boundarys
{
public:
	static std::vector<boundary> staticbounds;
	std::vector<boundary> bounds;
	int boundcnt;
	boundarys();
	void init(int cnt);
	static void staticboundarysInit(int h, int w, float scale);
	void collid(Vector2 &globalPos, Vector2 &vel);
	void setboundaryPos(Vector2* points);

};

