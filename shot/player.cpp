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
	Xspeed = 0.4;//0.5
	Yspeed = 0.3;
	Xmaxspeed = 4;//5
	Ymaxspeed = 3;//4
	stopspeed = 1;
	scale = 4;
	localheadpos = { 0,-12 * scale };
	globalPos = { (float)x,(float)y };
	hp = 100;
	
	//parts pos set
	rightfootstep = { 400 - 2*scale,300 + 14 * scale};
	leftfootstep = { 400 + 2*scale,300 + 14 * scale};
	lastfootposL = { 400,300 + 10 * scale };
	lastfootposR = { 400,300 + 10 * scale };

	head.init({ Pos.x,Pos.y - 12 * scale }, 32 * scale, 32 * scale, 0, 1, 0, { 16 * scale,6 * scale }, "resource/playerhead.png",0,true);
	body.init({ Pos.x,Pos.y }, 32 * scale, 32 * scale, 0, 1, 0, { (float)16.5 * scale ,18 * scale }, "resource/body.png",0,true);
	leftleg.init({ Pos.x + 2 * scale ,Pos.y + 5 * scale }, 32 * scale, 32 * scale, 0, 1, 0, { (float)18.5 * scale, 23 * scale }, "resource/rightleg.png",0,true);
	rightleg.init({ Pos.x - 2 * scale ,Pos.y + 5 * scale }, 32 * scale, 32 * scale, 0, 1, 0, { (float)14.5 * scale, 23 * scale }, "resource/leftleg.png",0,true);
	head.spritesToVector();
	body.spritesToVector();
	leftleg.spritesToVector();
	rightleg.spritesToVector();

	//boundary set
	c.pushBounds({ (float)(globalPos.x - 5 * scale), (float)(globalPos.y + 9.5 * scale) }, { (float)(globalPos.x + 5 * scale), (float)(globalPos.y + 9.5 * scale) });
	c.pushBounds({ (float)(globalPos.x + 5 * scale), (float)(globalPos.y + 9.5 * scale) }, { (float)(globalPos.x + 5 * scale), (float)(globalPos.y + 13.5 * scale) });
	c.pushBounds({ (float)(globalPos.x - 5 * scale), (float)(globalPos.y + 13.5 * scale) }, { (float)(globalPos.x + 5 * scale), (float)(globalPos.y + 13.5 * scale) });
	c.pushBounds({ (float)(globalPos.x - 5 * scale), (float)(globalPos.y + 9.5 * scale) }, { (float)(globalPos.x - 5 * scale), (float)(globalPos.y + 13.5 * scale) });
	c.pushlocalBoundPos(-5 * scale, 9.5 * scale);
	c.pushlocalBoundPos(5 * scale, 9.5 * scale);
	c.pushlocalBoundPos(5 * scale, 13.5 * scale);
	c.pushlocalBoundPos(-5 * scale, 13.5 * scale);
	c.init(4,0);//(boundcnt,id)
	boundarys::dyboundcnt += 4;
	
	BodyBound.pushBounds({ globalPos.x - 5 * scale, globalPos.y + -16 * scale }, { globalPos.x + 5 * scale, globalPos.y + -16 * scale });
	BodyBound.pushBounds({ globalPos.x + 5 * scale, globalPos.y + -16 * scale }, { globalPos.x + 5 * scale, globalPos.y + 12 * scale });
	BodyBound.pushBounds({ globalPos.x - 5 * scale, globalPos.y + 12 * scale }, { globalPos.x + 5 * scale, globalPos.y + 12 * scale });
	BodyBound.pushBounds({ globalPos.x - 5 * scale, globalPos.y + -16 * scale }, { globalPos.x - 5 * scale, globalPos.y + 12 * scale });

	BodyBound.pushlocalBoundPos(-5 * scale, -16 * scale);
	BodyBound.pushlocalBoundPos(5 * scale, -16 * scale);
	BodyBound.pushlocalBoundPos(5 * scale, 12 * scale);
	BodyBound.pushlocalBoundPos(-5 * scale, 12 * scale);
	
	BodyBound.linkHp(&hp);
	BodyBound.pushBodyBounds();
}

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

void player::update()
{
	Vector2 mPos = GetMousePosition();
	rotation = atan2f(mPos.y - Pos.y, mPos.x - Pos.x);
	float distanceToMouse = sqrtf(pow(mPos.x - Pos.x, 2) + pow(mPos.y - Pos.y, 2));
	Thread = std::thread(&inventory::update,&inven,globalPos,rotation,distanceToMouse);
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
		if (Vel.x < -stopspeed) {
			Vel.x += Xspeed;
		}
		else if (Vel.x > stopspeed) {
			Vel.x -= Xspeed;
		}
		else
		{
			Vel.x = 0;
		}
	}
	if(!W && !S){
		if (Vel.y < -stopspeed) {
			Vel.y += Yspeed;
		}
		else if (Vel.y > stopspeed) {
			Vel.y -= Yspeed;
		}
		else {
			Vel.y = 0;
		}
	}
	if (!W && !S && !A && !D) {
		state = 0;
	}
	else { state = 1; }

	c.update(globalPos, Vel);


	globalPos.x += Vel.x;
	globalPos.y += Vel.y;
	Pos = cam::getscreenPos(globalPos);

	head.depth = globalPos.y + 16 * scale;
	body.depth = globalPos.y + 16 * scale;
	rightleg.depth = globalPos.y + localrlpos.y + 9 * scale;
	leftleg.depth = globalPos.y + localllpos.y + 9 * scale;

	Thread.join();
	//inven.update(globalPos,rotation);
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
