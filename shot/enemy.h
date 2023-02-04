#pragma once
#include "boundarys.h"
#include "sprite.h"
#include "cam.h"

class enemy
{
private:
	float hp;
	Vector2 globalPos;
	Vector2 Pos;

	bodyBound* BodyBound;

	sprite head;
	sprite body;
	sprite leftleg;
	sprite rightleg;

public:
	enemy();
	~enemy();
	void getDamage(float damage);
};

