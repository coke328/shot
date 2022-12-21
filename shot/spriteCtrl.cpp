#include "spriteCtrl.h"

std::vector<sprite*>spriteCtrl::sprites;

void spriteCtrl::load() {
	p.playerInit(0, 0);
	spriteCtrl::sprites.push_back(&p.head);
	spriteCtrl::sprites.push_back(&p.body);
	spriteCtrl::sprites.push_back(&p.leftleg);
	spriteCtrl::sprites.push_back(&p.rightleg);
}

void spriteCtrl::spritesDraw()
{
	for (int i = 0; i < spriteCtrl::sprites.size(); i++) {
		spriteCtrl::sprites[i]->drawTexture();
	}
}

void spriteCtrl::spritesUnload()
{
	for (int i = 0; i < spriteCtrl::sprites.size(); i++) {
		spriteCtrl::sprites[i]->unloadTexture();
	}
}

void spriteCtrl::spritesUpdate()
{
	for (int i = 0; i < spriteCtrl::sprites.size(); i++) {
		spriteCtrl::sprites[i]->update();
	}
}
