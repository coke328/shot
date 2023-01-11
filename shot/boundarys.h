#pragma once
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
	static int holeidxstart;
	static int dyboundcnt;

	std::vector<boundary> bounds;
	std::vector<vec2> blocalPos;

	int id;
	int boundcnt;
	boundarys();
	~boundarys();
	void init(int cnt, int idx);
	static void staticboundarysInit();
	static void suburbbound(int w, int h, float scale);
	virtual void collid(Vector2& globalPos, Vector2& vel) = 0;
	void setboundaryPos(Vector2 globalPos);

};

class slipcollid : public boundarys {
public:
	virtual void collid(Vector2& globalPos, Vector2& vel);
};

class bulletcollid : public boundarys {
public:
	virtual void collid();
};