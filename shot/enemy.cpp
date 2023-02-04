#include "enemy.h"

enemy::enemy()
{
	hp = 100;
	globalPos = { 2000,0 };
	BodyBound->linkbody(this);
	Pos = cam::getscreenPos(globalPos);

	head.init({ Pos.x,Pos.y - 12 * 4 }, 32 * 4, 32 * 4, 0, 1, 0, { 16 * 4,6 * 4 }, "resource/playerhead.png", 0, true);
	body.init({ Pos.x,Pos.y }, 32 * 4, 32 * 4, 0, 1, 0, { (float)16.5 * 4 ,18 * 4 }, "resource/body.png", 0, true);
	leftleg.init({ Pos.x + 2 * 4 ,Pos.y + 5 * 4 }, 32 * 4, 32 * 4, 0, 1, 0, { (float)18.5 * 4, 23 * 4 }, "resource/rightleg.png", 0, true);
	rightleg.init({ Pos.x - 2 * 4 ,Pos.y + 5 * 4 }, 32 * 4, 32 * 4, 0, 1, 0, { (float)14.5 * 4, 23 * 4 }, "resource/leftleg.png", 0, true);
}

enemy::~enemy()
{
	delete BodyBound;
}

void enemy::getDamage(float damage)
{
	hp -= damage;
	std::cout << hp << std::endl;
}
