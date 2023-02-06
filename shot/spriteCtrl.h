#pragma once
#include "player.h"
#include "enemy.h"

class spriteCtrl {
public:
	//static std::vector<sprite*> sprites;
	int* sequence;
	player* p;
	enemy* e;

	void load();
	void spritesDraw();
	void spritesUnload();
	void spritesUpdate();
};
