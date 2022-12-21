#pragma once
#include <vector>
#include "sprite.h"
#include "player.h"
#include <iostream>

class spriteCtrl {
public:
	static std::vector<sprite*> sprites;
	player p;

	void load();
	void spritesDraw();
	void spritesUnload();
	void spritesUpdate();
};