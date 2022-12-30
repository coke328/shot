#include "game.h"

tilemap tmap;
spriteCtrl spc;
int FPS = 60;

void init() {
	tmap.loadmap("resource/tilemap/test.txt");
	tmap.load();
	spc.load();
}

void draw() {
	tmap.drawtilemap();
	spc.spritesDraw();
	DrawCircle(spc.p.Pos.x - 5 * 4, spc.p.Pos.y + 9.5 * 4, 5, BLACK);
	DrawCircle(spc.p.Pos.x + 5 * 4, spc.p.Pos.y + 9.5 * 4, 5, BLACK);
	DrawCircle(spc.p.Pos.x - 5 * 4, spc.p.Pos.y + 13.5 * 4, 5, BLACK);
	DrawCircle(spc.p.Pos.x + 5 * 4, spc.p.Pos.y + 13.5 * 4, 5, BLACK);
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
		spc.p.update();
		spc.p.partsMovement();

		lastTime = t;
	}
}
