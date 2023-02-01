#include "game.h"
#define FPS 120

tilemap *tmap = new tilemap;
spriteCtrl* spc = new spriteCtrl;
uiCtrl* uc = new uiCtrl;
ui aim;

void initlast() {
	boundarys::staticboundarysInit();
}

void init() {
	tmap->loadmap("resource/tilemap/test.txt");
	tmap->load();
	spc->load();
	initlast();
	HideCursor();
	aim.init({ 0,0,8 * 4,8 * 4 }, 0, 0, { 4.5 * 4,4.5 * 4 }, "resource/Ui/mouseCursor.png", 3, true);
	uiCtrl::push(&aim);
}

void draw() {
	aim.setPos({ GetMousePosition().x - GetScreenWidth() / 2,GetMousePosition().y - GetScreenHeight() / 2 });
	tmap->drawtilemap();
	spc->spritesDraw();
	uc->drawUi();
	DrawCircle(spc->p->Pos.x - 5 * 4, spc->p->Pos.y + 9.5 * 4, 5, BLACK);
	DrawCircle(spc->p->Pos.x + 5 * 4, spc->p->Pos.y + 9.5 * 4, 5, BLACK);
	DrawCircle(spc->p->Pos.x - 5 * 4, spc->p->Pos.y + 13.5 * 4, 5, BLACK);
	DrawCircle(spc->p->Pos.x + 5 * 4, spc->p->Pos.y + 13.5 * 4, 5, BLACK);
}

void unload() {
	tmap->unloadT();
	spc->spritesUnload();
	uc->unloadTexture();
	delete tmap, spc, uc;
}

std::thread t1;
clock_t lastTime;
void update()
{
	
	clock_t t = clock();
	clock_t tDelta = t - lastTime;
	if (tDelta >= 1000 / FPS) {
		//std::cout << tDelta << std::endl;
		cam::setcamPos(spc->p->globalPos);
		spc->spritesUpdate();
		t1 = thread(&player::partsMovement,&spc->p[0]);
		//spc->p->partsMovement();
		spc->p->update();
		t1.join();
		lastTime = t;
	}
}
