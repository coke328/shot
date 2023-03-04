#include "item.h"


item::item()
{
}

void item::init(Vector2 globalPos)
{
	std::string fileName = "resource/" + getItemName(itemId) + ".png";
	Texture2D tmp = LoadTexture(fileName.c_str());
	globalPos = item::globalPos;
	if (tmp.width > 32) {
		itemUi.init({ globalPos.x,globalPos.y }, 32 * 4, 32 * 4, 0, 3, 0, { 16 * 4,16 * 4 }, fileName, 3, false, false);
	}
	else {
		itemUi.init({ globalPos.x,globalPos.y }, 32 * 4, 32 * 4, 0, 0, 0, { 16 * 4,16 * 4 }, fileName, 3, false, false);
	}
	UnloadTexture(tmp);
}

void item::update()
{
	if (onGround) {

	}
	else {

	}
}

Vector2 item::getGlobalPos()
{
	return globalPos;
}

void item::displayF()
{
	f.setVisible(true);
}

void item::eraseF()
{
	f.setVisible(false);
}

void itemCtrl::linkplayerGlobalPos(Vector2* gPos)
{
	playerGLobalPos = gPos;
}

void itemCtrl::getItem()
{

}

void itemCtrl::update()
{
	float dist = powf(items.begin()->getGlobalPos().x,2) + powf(items.begin()->getGlobalPos().y, 2);
	int itemIdx = 0;
	std::list<item>::iterator iter;
	std::list<item>::iterator tmp;
	for (iter = items.begin()++; iter != items.end(); iter++) {
		float tmpdist = powf(iter->getGlobalPos().x, 2) + powf(iter->getGlobalPos().y, 2);
		if (dist > tmpdist) {
			dist = tmpdist;
			tmp = iter;
		}
	}
	if (dist < 400) {
		tmp->displayF();
	}
	else {
		tmp->eraseF();
	}
}

std::string getItemName(int itemType)
{
	if (itemType == defaultHandgun)
		return std::string("guns/defaultHandGun");
	if (itemType == defaultar)
		return std::string("guns/defaultAr");
	if (itemType == litesniper)
		return std::string("guns/liteSniper");

	return std::string("???");
}
