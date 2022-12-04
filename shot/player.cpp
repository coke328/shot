#include "player.h"
#include <iostream>
#include <time.h>
#include <math.h>

#define PI 3.141592

player::player()
{
}

void player::playerInit()
{
	Pos = { 400,300 };
	Vel = { 0,0 };
	Acc = { 0,0 };
	Xspeed = 0.5;
	Yspeed = 0.5;
	Xmaxspeed = 5;
	Ymaxspeed = 4;
	scale = 4;
	localheadpos = { 0,-12 * scale };
	
	rightfootstep = { 400 - 2*scale,300 + 14 * scale};
	leftfootstep = { 400 + 2*scale,300 + 14 * scale};

	head.init(Vector2{ Pos.x,Pos.y - 12 * scale }, 32 * scale, 32 * scale, 0, 1, 0, { 16 * scale,6 * scale }, "resource/playerhead.png");
	body.init(Vector2{ Pos.x,Pos.y }, 32 * scale, 32 * scale, 0, 1, 0, { (float)16.5 * scale ,18 * scale }, "resource/body.png");
	leftleg.init(Vector2{ Pos.x + 2 * scale ,Pos.y + 5 * scale }, 32 * scale, 32 * scale, 0, 1, 0, { (float)18.5 * scale, 23 * scale }, "resource/rightleg.png");
	rightleg.init(Vector2{ Pos.x - 2 * scale ,Pos.y + 5 * scale }, 32 * scale, 32 * scale, 0, 1, 0, { (float)14.5 * scale, 23 * scale }, "resource/leftleg.png");

}

void player::drawParts()
{
	
	head.drawTexture();
	
	if (localrlpos.y - 5 * scale < 0) {
		rightleg.drawTexture();
		leftleg.drawTexture();
	}
	else {
		leftleg.drawTexture();
		rightleg.drawTexture();
	}
	body.drawTexture();
	
}
int t = 6;
bool rightlegturn = true;
Vector2 lastfootpos = { 400,356};
Vector2 predictstep = { 0,0 };

void player::partsMovement()
{
	double tmp = rotation + (PI / 2);
	float cos = 2 * scale * cosf(tmp);
	float sin = scale * sinf(tmp);
	if (cos > 0) {
		body.Width = 32 / 5 * (cos + 3 * scale);
	}
	else {
		body.Width = 32 / 5 * (-cos + 3 * scale);
	}
	body.Origin.x = body.Width / 2;

	localrlpos = { cos,sin + 5 * scale };
	localllpos = { -cos,-sin + 5 * scale };

	head.setPos(Pos.x,Pos.y + localheadpos.y);
	body.setPos(Pos.x - 0.4 * scale, Pos.y);
	rightleg.setPos(Pos.x + localrlpos.x, Pos.y + localrlpos.y);
	leftleg.setPos(Pos.x + localllpos.x, Pos.y + localllpos.y);

	int tm = 15;
	
	if (state == 1) {
		
		if (t > 0) {
			float h = (9 + t * (t - tm) / (tm/2)) * scale;
			cout << h << endl;
			if (rightlegturn) {
				rightleg.Height = h*32/9;
				rightleg.Origin.y = 23 * h / 9;
				
			}
			else {
				leftleg.Height = h*32/9;
				leftleg.Origin.y = 23 * h / 9;
				cout << leftleg.Origin.y << endl;
			}
			t--;
		}
		else {
			t = tm;
			rightlegturn = !rightlegturn;
		}
		
		
		//legmove();
	}
	else {
	}
}

void player::movement()
{
	rotation = atan2f(GetMousePosition().y - Pos.y, GetMousePosition().x - Pos.x);
	//cout << rotation * 180 / 3.141592 << endl;
	bool W = IsKeyDown(KEY_W);
	bool S = IsKeyDown(KEY_S);
	bool A = IsKeyDown(KEY_A);
	bool D = IsKeyDown(KEY_D);
	if (W) {
		Vel.y -= Yspeed;
	}
	if (S) {
		Vel.y += Yspeed;
	}
	if (A) {
		Vel.x -= Xspeed;
	}
	if (D) {
		Vel.x += Xspeed;
	}
	if (Vel.x > Xmaxspeed) {
		Vel.x = Xmaxspeed;
	}
	else if (Vel.x < -Xmaxspeed) {
		Vel.x = -Xmaxspeed;
	}
	if (Vel.y > Ymaxspeed) {
		Vel.y = Ymaxspeed;
	}
	else if (Vel.y < -Ymaxspeed) {
		Vel.y = -Ymaxspeed;
	}
	if (!A && !D) {
		if (Vel.x < 0) {
			Vel.x += Xspeed;
		}
		else if (Vel.x > 0) {
			Vel.x -= Xspeed;
		}
	}
	if(!W && !S){
		if (Vel.y < 0) {
			Vel.y += Yspeed;
		}
		else if (Vel.y > 0) {
			Vel.y -= Yspeed;
		}
	}
	if (!W && !S && !A && !D) {
		state = 0;
	}
	else { state = 1; }
	Pos.x += Vel.x;
	Pos.y += Vel.y;
}

void player::unloadTextures()
{
	head.unloadTexture();
	
	body.unloadTexture();
	
	leftleg.unloadTexture();
	rightleg.unloadTexture();
	
}

void player::legmove()
{
	float x = rightfootstep.x - (Pos.x + localrlpos.x);
	float y = rightfootstep.y - (Pos.y + localrlpos.y);
	float distance = sqrtf(x*x + y*y);
	rightleg.Height = distance / 9 * 32;

	rightleg.Origin.y = distance / 9 * 23;

	float rot = 180 / PI * atan2f(y, x) + 270;
	rightleg.Rotation = rot;

	x = leftfootstep.x - (Pos.x + localllpos.x);
	y = leftfootstep.y - (Pos.y + localllpos.y);
	distance = sqrtf(x * x + y * y);
	leftleg.Height = distance / 9 * 32;

	leftleg.Origin.y = distance / 9 * 23;
	
	rot = 180 / PI * atan2f(y, x) + 270;
	leftleg.Rotation = rot;
}

