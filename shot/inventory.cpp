#include "inventory.h"

weapon* returnWeapon(int idx) 
{
	if (idx == defaultHandgun) { return new defaultHandGun(); }
}

inventory::inventory()
{
	hand = 1;
	Weapon.push_back(new Hand());
	getitem(defaultHandgun);
}

int inventory::getItemIdx(int slot)
{
	return items[slot];
}

void inventory::getitem(int itemIdx)
{
	if (itemIdx < maxWeapons) {
		Weapon.push_back(returnWeapon(itemIdx));
		
		if(Weapon.size() == 2 && hand == 1){ wm.changeWeapon(Weapon[0]); wm.holdGun = true; }
		else if(Weapon.size() == 3 && hand == 2){ wm.changeWeapon(Weapon[1]); wm.holdGun = true; }
		else if(Weapon.size() == 4 && hand == 3){ wm.changeWeapon(Weapon[2]); wm.holdGun = true; }
	}
}

void inventory::changeItem(int slot1, int slot2)
{
}

void inventory::drawInventory()
{
	if (activeInven) {
		
	}
}

void inventory::update(Vector2 gPos,float rot)
{
	if (IsKeyPressed(KEY_TAB)) {
		activeInven = true;
	}
	else if (IsKeyReleased(KEY_TAB)) {
		activeInven = false;
	}
	if (activeInven) {
		
	}
	if (IsKeyDown(KEY_ONE) && hand != 1) {
		if (Weapon.size() >= 2) {
			wm.changeWeapon(Weapon[1]);
			wm.holdGun = true;
			std::cout << "weapon1" << std::endl;
		}
		else {
			wm.changeWeapon(Weapon[0]);
			wm.holdGun = false;
			std::cout << "hand" << std::endl;
		}
		hand = 1;
	}
	else if (IsKeyDown(KEY_TWO) && hand != 2) {
		if (Weapon.size() >= 3) {
			wm.changeWeapon(Weapon[2]);
			wm.holdGun = true;
			std::cout << "weapon2" << std::endl;
		}
		else {
			wm.changeWeapon(Weapon[0]);
			wm.holdGun = false;
			std::cout << "hand" << std::endl;
		}
		hand = 2;
	}
	else if (IsKeyDown(KEY_THREE) && hand != 3) {
		if (Weapon.size() >= 4) {
			wm.changeWeapon(Weapon[3]);
			wm.holdGun = true;
			std::cout << "weapon3" << std::endl;
		}
		else {
			wm.changeWeapon(Weapon[0]);
			wm.holdGun = false;
			std::cout << "hand" << std::endl;
		}
		hand = 3;
	}
	else if (IsKeyDown(KEY_FOUR)) {

	}
	wm.update(gPos,rot);
}
