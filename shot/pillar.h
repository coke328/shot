#pragma once
#include "sprite.h"
#include "spriteCtrl.h"
#include "boundarys.h"

class pillar
{
public:
	int height;
	sprite* parts;
	pillar(Vector2 pos, int h, float scale, int tiletype);
	void partsToSprites();
};

