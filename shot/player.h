#pragma once
#include "sprite.h"
#include "boundarys.h"
#include "inventory.h"
#include <thread>

class player
{
public:
	Vector2 Pos;
	Vector2 Vel;
	Vector2 Acc;
	Vector2 globalPos;

	int state = 0;//0:stop 1:walk
	float Xspeed;
	float Yspeed;
	float Xmaxspeed;
	float Ymaxspeed;
	float stopspeed;
	float rotation;
	float scale;
	float hp;

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

	bodyBound bodyBound;
	slipcollid c;
	inventory inven;
	boundarys bounds;
	std::thread Thread;

	player();
	void playerInit(int x, int y);
	void drawParts();
	void partsMovement();
	void update();
	void unloadTextures();
	void legmove();
};

