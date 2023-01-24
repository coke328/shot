#include "pillar.h"


pillar::pillar(Vector2 pos, int h, float scale, int tiletype) {
	height = h;
	parts = new sprite[2 * h + 1];
	parts[0].init({ pos.x,pos.y - 32 * h * scale }, 64 * scale, 32 * scale, 0, 2, tiletype, { 0,0 }, "resource/tile.png", pos.y + 16 * scale,true);
	for (int i = 0; i < 2 * h; i++) {
		if (i < h) {//rightwall
			parts[i + 1].init({ pos.x,pos.y - (32 * i + 16) * scale }, 32 * scale, 48 * scale, 0, 1, 1, { 0,0 }, "resource/wall.png", pos.y + 16 * scale,true);
		}
		else {//leftwall
			parts[i + 1].init({ pos.x + 32 * scale,pos.y - (32 * (i - h) + 16) * scale }, 32 * scale, 48 * scale, 0, 1, 0, { 0,0 }, "resource/wall.png", pos.y + 16 * scale,true);
		}
	}
	//set static boundary
	boundarys::staticbounds.emplace_back(pos.x, pos.y + 16 * scale, pos.x + 32 * scale, pos.y, true);
	boundarys::staticbounds.emplace_back(pos.x + 32 * scale, pos.y, pos.x + 64 * scale, pos.y + 16 * scale, true);
	boundarys::staticbounds.emplace_back(pos.x + 64 * scale, pos.y + 16 * scale, pos.x + 32 * scale, pos.y + 32 * scale, true);
	boundarys::staticbounds.emplace_back(pos.x + 32 * scale, pos.y + 32 * scale, pos.x, pos.y + 16 * scale, true);
	boundarys::holeidxstart += 4;
}

void pillar::partsToSprites()
{
	for (int i = 0; i < 2 * height + 1; i++) {
		//spriteCtrl::sprites.push_back(&parts[i]);
		parts[i].spritesToVector();
	}
}
