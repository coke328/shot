#pragma once
#include "raylib.h"
#include "weapon.h"
#include <vector>

enum {
	defaultHandgun = 1,
	defaultar,
	liteSniper,
	maxWeapons,
	healkit,

};

class inventory
{
private:
	int items[10];//0~2 weapon 3~5 armor 6~ item
	std::vector<weapon*> Weapon;
	
	bool activeInven;
	int hand;

	ui reloadBar[2];
	ui inventoryUi;

	button tab;

	weaponManager wm;
public:
	inventory();
	int getItemIdx(int slot);//0~2
	void getitem(int itemIdx);
	void changeItem(int slot1, int slot2);
	void drawInventory();
	void update(Vector2 gPos, float rot, float distanceMouse);
};

