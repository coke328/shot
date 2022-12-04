#pragma once
#include "sprite.h"
#include "raylib.h"

class player
{
public:
	Vector2 Pos;
	Vector2 Vel;
	Vector2 Acc;
	int state = 0;//0:stop 1:walk
	float Xspeed;
	float Yspeed;
	float Xmaxspeed;
	float Ymaxspeed;
	float rotation;
	float scale;
	Vector2 localheadpos;
	Vector2 localllpos;
	Vector2 localrlpos;
	Vector2 leftfootstep;
	Vector2 rightfootstep;
	
	sprite head;
	sprite body;
	sprite leftleg;
	sprite rightleg;
	player();
	void playerInit();
	void drawParts();
	void partsMovement();
	void movement();
	void unloadTextures();
	void legmove();
};

