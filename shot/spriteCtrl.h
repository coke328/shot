#pragma once
#include "player.h"

class spriteCtrl {
public:
	static std::vector<sprite*> sprites;
	int* sequence;
	static int activecnt;
	player* p;

	void load();
	void spritesDraw();
	void spritesUnload();
	void spritesUpdate();
};
