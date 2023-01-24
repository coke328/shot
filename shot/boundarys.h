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

	Vector2 globalPos;

	int id;
	int boundcnt;
	boundarys();
	~boundarys();
	void init(int cnt, int idx);
	static void staticboundarysInit();
	static void suburbbound(int w, int h, float scale);
	virtual bool collid(Vector2& globalPos, Vector2& vel) = 0;
	void setboundaryPos(Vector2 gPos);
	void boundset();

};

class slipcollid : public boundarys {
public:
	bool collid(Vector2& globalPos, Vector2& vel) override;
};

class bulletBound {
public:
	boundary b[2];
	Vecbool collid();
};