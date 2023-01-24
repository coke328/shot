#pragma once
#include "player.h"


class spriteCtrl {
public:
	//static std::vector<sprite*> sprites;
	int* sequence;
	player* p;

	void load();
	void spritesDraw();
	void spritesUnload();
	void spritesUpdate();
};
