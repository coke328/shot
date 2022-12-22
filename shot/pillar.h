#pragma once
#include "sprite.h"
#include "spriteCtrl.h"

class pillar
{
public:
	int height;
	sprite* parts;
	pillar(Vector2 pos, int h, float scale, int tiletype);
	void partsToSprites();
};

