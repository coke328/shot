#include "player.h"
#include <iostream>
#include <time.h>
#include <math.h>

#define PI 3.141592

player::player()
{
}

void player::playerInit(int x, int y)
{
	Pos = { (float)x,(float)y };
	Vel = { 0,0 };
	Acc = { 0,0 };
	Xspeed = 0.5;
	Yspeed = 0.5;
	Xmaxspeed = 5;
	Ymaxspeed = 4;
	scale = 4;
	localheadpos = { 0,-12 * scale };
	globalPos = { (float)x,(float)y };
	
	rightfootstep = { 400 - 2*scale,300 + 14 * scale};
	leftfootstep = { 400 + 2*scale,300 + 14 * scale};
	lastfootposL = { 400,300 + 10 * scale };
	lastfootposR = { 400,300 + 10 * scale };

	head.init({ Pos.x,Pos.y - 12 * scale }, 32 * scale, 32 * scale, 0, 1, 0, { 16 * scale,6 * scale }, "resource/playerhead.png",0);
	body.init({ Pos.x,Pos.y }, 32 * scale, 32 * scale, 0, 1, 0, { (float)16.5 * scale ,18 * scale }, "resource/body.png",0);
	leftleg.init({ Pos.x + 2 * scale ,Pos.y + 5 * scale }, 32 * scale, 32 * scale, 0, 1, 0, { (float)18.5 * scale, 23 * scale }, "resource/rightleg.png",0);
	rightleg.init({ Pos.x - 2 * scale ,Pos.y + 5 * scale }, 32 * scale, 32 * scale, 0, 1, 0, { (float)14.5 * scale, 23 * scale }, "resource/leftleg.png",0);

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
int t = 15;
int i = 1;
bool sorted = false;
bool rightlegturn = true;
Vector2 predictstep = { 0,0 };
Vector2 tmpL = { 0,0 };
Vector2 tmpR = { 0,0 };

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

	int tm = 8;
	
	if (state == 1) {
		sorted = false;

		if (t > 0) {
			
			if (t == tm) {
				tmpL = localllpos;
				tmpR = localrlpos;
			}
			predictstep.x = globalPos.x + (Vel.x * (t+4));
			predictstep.y = globalPos.y + (Vel.y * (t+4));
			
			if (rightlegturn) {
				
				rightfootstep.x = (predictstep.x - lastfootposR.x) * (tm + 1 - t) / tm + lastfootposR.x + tmpR.x;
				rightfootstep.y = ((predictstep.y + 5 * scale) - lastfootposR.y) * (tm + 1 - t) / tm + lastfootposR.y + tmpR.y;
				
				if (t == 1) {
					lastfootposR = rightfootstep;
				}
			}
			else {

				leftfootstep.x = (predictstep.x - lastfootposL.x) * (tm+1-t) / tm + lastfootposL.x + tmpL.x;
				leftfootstep.y = (predictstep.y + 5 * scale - lastfootposL.y) * (tm + 1 - t) / tm  + lastfootposL.y + tmpL.y;
				if (t == 1) {
					lastfootposL = leftfootstep;
				}
			}
			t--;
		}
		else {
			t = tm;
			rightlegturn = !rightlegturn;
		}
		
		
		legmove();
	}
	else {
		if (!sorted) {
			lastfootposR = rightfootstep;
			lastfootposL = leftfootstep;
			i = 1;
			sorted = true;
		}
		int im = 10;
		if (i <= im) {
			rightfootstep.x = (globalPos.x + localrlpos.x - lastfootposR.x) * i / im + lastfootposR.x;
			rightfootstep.y = (globalPos.y + 8 * scale + localrlpos.y - lastfootposR.y) * i / im + lastfootposR.y;
			leftfootstep.x = (globalPos.x + localllpos.x - lastfootposL.x) * i / im + lastfootposL.x;
			leftfootstep.y = (globalPos.y + 8 * scale + localllpos.y - lastfootposL.y) * i / im + lastfootposL.y;
			legmove();
			i++;
		}
	}
}

void player::movement()
{
	
	rotation = atan2f(GetMousePosition().y - Pos.y, GetMousePosition().x - Pos.x);
	
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
	globalPos.x += Vel.x;
	globalPos.y += Vel.y;
	Pos = cam::getscreenPos(globalPos);
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
	int maxleglength = 30;
	float x = rightfootstep.x - (globalPos.x + localrlpos.x);
	float y = rightfootstep.y - (globalPos.y + localrlpos.y);
	float distance = sqrtf(x*x + y*y);
	if (distance > maxleglength) {
		distance = maxleglength;
	}
	rightleg.Height = distance / 9 * 32;

	rightleg.Origin.y = distance / 9 * 23;

	float rot = 180 / PI * atan2f(y, x) + 270;
	rightleg.Rotation = rot;

	x = leftfootstep.x - (globalPos.x + localllpos.x);
	y = leftfootstep.y - (globalPos.y + localllpos.y);
	distance = sqrtf(x * x + y * y);
	if (distance > maxleglength) {
		distance = maxleglength;
	}
	leftleg.Height = distance / 9 * 32;

	leftleg.Origin.y = distance / 9 * 23;
	
	rot = 180 / PI * atan2f(y, x) + 270;
	leftleg.Rotation = rot;
}
