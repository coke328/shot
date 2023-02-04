#pragma once
#include "boundary.h"

class enemy;

class bodyBound;

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
	static std::vector<bodyBound*> bodyBoundarys;
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
	virtual bool update(Vector2& globalPos, Vector2& vel);
	void setboundaryPos(Vector2 gPos);
	void boundset();
};

class slipcollid : public boundarys {
public:
	bool update(Vector2& globalPos, Vector2& vel) override;
};

class bulletBound {
public:
	boundary b[2];
	float damage;
	
	void setDamage(float d);
	Vecbool collid();
};

class bodyBound : public boundarys{
private:
	enemy* e;
public:
	~bodyBound();
	void linkbody(enemy* enemy);
	bool update(Vector2& globalPos, Vector2& Vel) override;
	void getdamage(float d);
};