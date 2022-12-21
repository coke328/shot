#include "game.h"

player p;
tilemap tmap;
spriteCtrl spc;
int FPS = 60;

void init() {
	tmap.loadmap("resource/tilemap/test.txt");
	tmap.loadwall();
	spc.load();
}

void draw() {
	tmap.drawtilemap();
	spc.spritesDraw();
}

void unload() {
	tmap.unloadT();
	spc.spritesUnload();
}

clock_t lastTime;
void update()
{
	
	clock_t t = clock();
	if ((t - lastTime) >= 1000 / FPS) {
		
		cam::setcamPos(spc.p.globalPos);
		spc.spritesUpdate();
		spc.p.movement();
		spc.p.partsMovement();

		lastTime = t;
	}
}
