#include "game.h"

player p;
tilemap tmap;
int FPS = 60;

void init() {
	p.playerInit(0, 0);
	tmap.loadmap("resource/tilemap/test.txt");
	
}

void draw() {
	tmap.drawtilemap();
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
		cam::setcamPos(p.globalPos);
		lastTime = t;
	}
}
