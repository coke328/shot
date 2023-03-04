#include "center.h"

void ReloadBarmove(int reloadTime, float Rt, bool isReloading, sprite* reloadBar) {
	if (Rt > 0 && isReloading) {
		reloadBar[0].setVisible(true);
		reloadBar[1].setVisible(true);

		reloadBar[1].setPos( (15- 30*Rt/reloadTime)*4 ,-25 * 4);

	}
	else {
		reloadBar[0].setVisible(false);
		reloadBar[1].setVisible(false);
	}
}

weapon* returnWeapon(int idx) 
{
	switch (idx) {
	case defaultHandgun:
		return new defaultHandGun();
	case defaultar:
		return new defaultAr();
	}
}

center::center()
{
	hand = 1;
	Weapon.push_back(new Hand());
	getitem(defaultHandgun);
	getitem(defaultar);

	reloadBar[0].init({ 0,-25 * 4 },32 * 4, 32 * 4, 0, 0, 0, { 16 * 4,16.5 * 4 }, "resource/Ui/reloadingBar1.png", 3000, false, false);
	reloadBar[1].init({ 0,-25 * 4 }, 8 * 4, 8 * 4, 0, 0, 0, { 4.5 * 4,4.5 * 4 }, "resource/Ui/reloadingBar2.png", 3001, false, false);
	reloadBar[0].spritesToVector();
	reloadBar[1].spritesToVector();

	inventoryUi.init({ 0,0 }, 400 * 4, 225 * 4, 0, 0, 0, { 200 * 4,125 * 4 }, "resource/Ui/inventory.png", 3002, false, false);
	inventoryUi.spritesToVector();

	numberOfBullet[0].init({ 102 * 4,88 * 4 }, 16 * 4, 16 * 4, 0, 10, 0, { 0,0 }, "resource/Ui/number.png", 3001, true, false);
	numberOfBullet[1].init({ 114 * 4,88 * 4 }, 16 * 4, 16 * 4, 0, 10, 0, { 0,0 }, "resource/Ui/number.png", 3001, true, false);
	numberOfBullet[2].init({ 126 * 4,88 * 4 }, 16 * 4, 16 * 4, 0, 10, 0, { 0,0 }, "resource/Ui/number.png", 3001, true, false);
	numberOfBullet[3].init({ 138 * 4,88 * 4 }, 16 * 4, 16 * 4, 0, 2, 0, { 0,0 }, "resource/Ui/symbol.png", 3001, true, false);
	numberOfBullet[4].init({ 150 * 4,88 * 4 }, 16 * 4, 16 * 4, 0, 10, 0, { 0,0 }, "resource/Ui/number.png", 3001, true, false);
	numberOfBullet[5].init({ 162 * 4,88 * 4 }, 16 * 4, 16 * 4, 0, 10, 0, { 0,0 }, "resource/Ui/number.png", 3001, true, false);
	numberOfBullet[6].init({ 174 * 4,88 * 4 }, 16 * 4, 16 * 4, 0, 10, 0, { 0,0 }, "resource/Ui/number.png", 3001, true, false);
	numberOfBullet[0].spritesToVector();
	numberOfBullet[1].spritesToVector();
	numberOfBullet[2].spritesToVector();
	numberOfBullet[3].spritesToVector();
	numberOfBullet[4].spritesToVector();
	numberOfBullet[5].spritesToVector();
	numberOfBullet[6].spritesToVector();

	aim.init({ 0,0 }, 8 * 4, 8 * 4, 0, 0, 0, { 4.5 * 4,4.5 * 4 }, "resource/Ui/mouseCursor.png", 3000, true, false);
	aim.spritesToVector();

	wm.init();

	tab.init(KEY_TAB);
}

int center::getItemIdx(int slot)
{
	return items[slot];
}

void center::getitem(int itemIdx)
{
	if (itemHaveCnt + weaponHaveCnt <= 13) {
		if (itemIdx < maxWeapons) {
			Weapon.push_back(returnWeapon(itemIdx));

			if (Weapon.size() == 2 && hand == 1) { wm.changeWeapon(Weapon[0]); wm.holdGun = true; }
			else if (Weapon.size() == 3 && hand == 2) { wm.changeWeapon(Weapon[1]); wm.holdGun = true; }
			else if (Weapon.size() == 4 && hand == 3) { wm.changeWeapon(Weapon[2]); wm.holdGun = true; }
		}
		else if (itemIdx > maxWeapons) {

		}
	}
}

void center::changeItem(int slot1, int slot2)
{
}

void center::drawInventory()
{
	if (activeInven) {
		
	}
}

void center::changeBulletCnt()
{
	int mb = wm.getMaxBullet();
	int bc = wm.getBulletCnt();
	int place[3];
	for (int i = 2; i >= 0; i--) {
		place[i] = bc / (int)powf(10, i);
		bc -= place[i] * (int)powf(10, i);
	}
	numberOfBullet[0].setspId(place[2]);
	numberOfBullet[1].setspId(place[1]);
	numberOfBullet[2].setspId(place[0]);
	for (int i = 2; i >= 0; i--) {
		place[i] = mb / (int)powf(10, i);
		mb -= place[i] * (int)powf(10, i);
	}
	numberOfBullet[4].setspId(place[2]);
	numberOfBullet[5].setspId(place[1]);
	numberOfBullet[6].setspId(place[0]);
}

void center::update(Vector2 gPos, float rot, float distanceMouse)
{
	aim.setPos(GetMousePosition().x,GetMousePosition().y);

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
	for (int i = 0; i < 3; i++) {
		Weapon[i]->muzzleFlame.updateEffects();
		Weapon[i]->bc.updateBullet();
	}
	
	changeBulletCnt();
}
