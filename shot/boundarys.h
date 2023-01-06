#pragma once
#include <vector>
#include "boundary.h"

class vec2 {
public:
	float x;
	float y;
	vec2(float x, float y);
};

class boundarys
{
public:
	static std::vector<boundary> staticbounds;
	std::vector<boundary> bounds;
	std::vector<vec2> blocalPos;
	int boundcnt;
	boundarys();
	void init(int cnt);
	static void staticboundarysInit(int h, int w, float scale);
	virtual void collid(Vector2 &globalPos, Vector2 &vel) = 0;
	void setboundaryPos(Vector2 globalPos);

};

class slipcollid : public boundarys {
public:
	virtual void collid(Vector2& globalPos, Vector2& vel);
};