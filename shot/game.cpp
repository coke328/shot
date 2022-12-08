#include "game.h"
#include "player.h"
#include <time.h>


player p;
int FPS = 60;
Vector2 camPos;
int camWidth;
int camHeight;

void init() {
	p.playerInit(400,300);
	camPos = p.camPos;
	camWidth = p.camWidth;
	camHeight = p.camHeight;
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
		camPos = p.camPos;
		p.movement();
		p.partsMovement();
		p.cammove();
		lastTime = t;
	}
}
