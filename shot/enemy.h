#pragma once
#include "boundarys.h"
#include "sprite.h"
#include "cam.h"
#include <time.h>

class enemy
{
private:
	float hp;
	float lastHp;
	float rotation;
	Vector2 globalPos;
	Vector2 Vel;
	Vector2 Pos;

	float lastTimeHit;
	float overlapDamage;

	bodyBound BodyBound;

	int state;

	int t = 15;
	int i = 1;
	bool sorted = false;
	bool rightlegturn = true;
	Vector2 predictstep = { 0,0 };
	Vector2 tmpL = { 0,0 };
	Vector2 tmpR = { 0,0 };

	Vector2 localheadpos;
	Vector2 localllpos;
	Vector2 localrlpos;
	Vector2 leftfootstep;
	Vector2 rightfootstep;
	Vector2 lastfootposR;
	Vector2 lastfootposL;

	sprite head;
	sprite body;
	sprite leftleg;
	sprite rightleg;

public:
	enemy();
	~enemy();
	void update();
	void partsMovement();
	void legmove();
	void getDamage(float d);
};

