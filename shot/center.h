#pragma once
#include "raylib.h"
#include "weapon.h"
#include "item.h"
#include <vector>

class center
{
private:
	int items[10];//0~2 weapon 3~5 armor 6~ item
	std::vector<item*> itemHave;
	std::vector<weapon*> Weapon;
	int weaponHaveCnt;
	int itemHaveCnt;
	
	bool activeInven;
	int hand;

	sprite reloadBar[2];
	sprite inventoryUi;
	sprite numberOfBullet[7];
	sprite item[13];

	sprite aim;

	button tab;

	weaponManager wm;
public:
	center();
	int getItemIdx(int slot);//0~2
	void getitem(int itemIdx);
	void changeItem(int slot1, int slot2);
	void drawInventory();
	void changeBulletCnt();
	void update(Vector2 gPos, float rot, float distanceMouse);
};

