#include "game.h"
#include "player.h"
#include <time.h>


player p;
int FPS = 60;

void init() {
	p.playerInit();
}

void draw() {
	p.drawParts();
}

void unload() {
	p.unloadTextures();
}

clock_t lastTime;
void update()
{
	clock_t t = clock();
	if ((t - lastTime) >= 1000 / FPS) {

		p.movement();
		p.partsMovement();
		lastTime = t;
	}
}
