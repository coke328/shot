#include "inventory.h"

void ReloadBarmove(int reloadTime, float Rt, bool isReloading, ui* reloadBar) {
	//std::cout << Rt << std::endl;
	//std::cout << reloadTime << std::endl;
	if (Rt > 0 && isReloading) {
		reloadBar[0].setVisible(true);
		reloadBar[1].setVisible(true);

		reloadBar[1].setPos({ (15- 30*Rt/reloadTime)*4 ,-25 * 4});

	}
	else {
		reloadBar[0].setVisible(false);
		reloadBar[1].setVisible(false);
	}
}

weapon* returnWeapon(int idx) 
{
	if (idx == defaultHandgun) { return new defaultHandGun(); }
	if (idx == defaultar) { return new defaultAr(); }
}

inventory::inventory()
{
	hand = 1;
	Weapon.push_back(new Hand());
	getitem(defaultHandgun);
	getitem(defaultar);

	reloadBar[0].init({ 0,-25 * 4,32 * 4,32 * 4 }, 0, 0, { 16 * 4,16.5 * 4 }, "resource/Ui/reloadingBar1.png", 0, false);
	reloadBar[1].init({ 0,-25 * 4,8 * 4,8 * 4 }, 0, 0, { 4.5 * 4,4.5 * 4 }, "resource/Ui/reloadingBar2.png", 1, false);
	uiCtrl::push(&reloadBar[0]);
	uiCtrl::push(&reloadBar[1]);

	inventoryUi.init({ 0,0,400 * 4,225 * 4 }, 0, 0, { 200*4,125*4 }, "resource/Ui/inventory.png", 2, false);
	uiCtrl::push(&inventoryUi);
	wm.init();

	tab.init(KEY_TAB);
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
	else if(itemIdx > maxWeapons) {

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

void inventory::update(Vector2 gPos, float rot, float distanceMouse)
{
	if (tab.keyPressed()) {
		if (activeInven) {
			activeInven = false;
			inventoryUi.setVisible(false);
		}
		else {
			activeInven = true;
			inventoryUi.setVisible(true);
		}
	}
	if (activeInven) {

	}
	else {
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
		wm.update(gPos, rot, distanceMouse);

		ReloadBarmove(wm.getReloadingTime(), wm.getRt(), wm.getisReloading(), reloadBar);
	}
}
