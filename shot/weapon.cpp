#include "weapon.h"

void delayExecute(sprite* sp, int Tid, int time) {
	clock_t start = clock();
	clock_t currentT = start;
	while (start + time > currentT) {
		currentT = clock();
	}
	sp->changeTexture(Tid);
}

void invokeChangeTexture(sprite* sp,int Tid,int time) {
	std::thread t(delayExecute,sp,Tid,time);
	t.detach();
}

weaponManager::~weaponManager()
{
	if (w) delete w;
}

void weaponManager::fire()
{
	w->fire();
}

void weaponManager::changeToAnotherWeapon()
{
	w->changeToAnotherWeapon();
}

void weaponManager::changeThisWeapon() {
	w->changeThisWeapon();
}

void weaponManager::update(Vector2 playerPos, float rot)
{
	if (holdGun) {
		float cos = cosf(rot);
		float sin = sinf(rot);
		w->firePos.x = playerPos.x + cos * w->distanceToMuzzle;
		w->firePos.y = playerPos.y + sin * w->distanceToMuzzle / 1.5;
		w->gunPos.x = playerPos.x + cos * w->distanceToGun;
		w->gunPos.y = playerPos.y + sin * w->distanceToGun / 1.5;
		w->rotation = rot;
		w->sp.setRotation(rot);
		w->sp.setglobalPos(w->gunPos);
		if (w->rotation > -PI / 2 && w->rotation < PI / 2) {
			if (w->isGunFlip == true) {
				w->sp.flipY();
			}
			w->isGunFlip = false;
		}
		else {
			if (w->isGunFlip == false) {
				w->sp.flipY();
			}
			w->isGunFlip = true;
		}
		w->sp.depth = w->gunPos.y + 50;

		w->update(playerPos, rot);
	}
}

void weaponManager::changeWeapon(weapon* pw)
{
	if (w) {
		w->sp.Visible = false;
		changeToAnotherWeapon();
	}
	w = pw;
	changeThisWeapon();
	w->sp.Visible = true;
}

defaultHandGun::defaultHandGun()
{
	itemId = 1;
	firerate = 200;//剐府技农
	damage = 10;
	bspeed = 20;
	numberOfBullet = 12;
	maxBullet = 12;
	reloadTime = 2000;
	reloading = false;
	canFire = true;
	distanceToGun = 60;
	distanceToMuzzle = 96;
	sp.init({ -100,-100 }, 32 * 4, 32 * 4, 0, 3, 0, {16 * 4, 16 * 4},"resource/guns/defaltHandgun.png",0,false);
	sp.spritesToVector();
	bs = new bullet[maxBulletPool];
	bs[0].init({0,0}, 32 * 4, 32 * 4, 0, 0, 0, {16 * 4,16 * 4}, "resource/bullets/bullet.png", 0, bspeed, damage, 2*4);
	for (int i = 1; i < maxBulletPool; i++) {
		bs[i].sp.setVisibla(false);
		bs[i].sp.setspId(-1);
	}

	gunSound = LoadSound("resource/sounds/handgunSound.mp3");
}

defaultHandGun::~defaultHandGun()
{
	UnloadSound(gunSound);
	delete[] bs;
}

void defaultHandGun::fire()
{
	bool executeOnce = true;
	for (int i = 1; i < maxBulletPool; i++) {
		if (!bs[i].sp.Visible && executeOnce) {
			bool tmp = bs[i].sp.isSprites;
			int id = bs[i].sp.Id;
			bs[i] = bs[0];
			//bs[i].sp.setIsSprites(tmp);
			bs[i].sp.setspId(id);
			bs[i].sp.setglobalPos(firePos);
			bs[i].sp.setVisibla(true);
			bs[i].rotation = rotation;
			bs[i].fire();
			executeOnce = false;
		}
	}
}

void defaultHandGun::update(Vector2 playerPos, float rot)
{

	clock_t t = clock();
	if (lastTimeFire + firerate <= t && !canFire) {
		canFire = true;
	}
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !reloading && canFire && singleShot) {
		canFire = false;
		singleShot = false;
		lastTimeFire = t;
		if (numberOfBullet) {
			std::cout << "fire" << std::endl;
			sp.changeTexture(1);
			invokeChangeTexture(&sp, 0, 100);
			fire();
			PlaySoundMulti(gunSound);
			numberOfBullet--;
		}
	}
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		singleShot = true;
	}
	if (numberOfBullet != maxBullet && IsKeyDown(KEY_R) && !reloading) {
		std::cout << "reloading" << std::endl;
		sp.changeTexture(2);
		invokeChangeTexture(&sp, 0, reloadTime);
		lastTimeReload = t;
		reloading = true;
	}
	if (lastTimeReload + reloadTime <= t && reloading) {
		std::cout << "reloading end" << std::endl;
		numberOfBullet = maxBullet;
		reloading = false;
	}
	for (int i = 1; i < maxBulletPool; i++) {
		if (bs[i].sp.Visible) {
			bs[i].update();
		}
	}
}

void defaultHandGun::changeToAnotherWeapon()
{
	//std::cout << "before:" << sprite::sprites.size() << std::endl;
	for (int i = 1; i < maxBulletPool; i++) {
		//std::cout << "staw:" << bs[i].sp.isSprites << std::endl;
		
		//std::cout << i << std::endl;
		bs[i].destructor();
		
	}
	//std::cout << "after:" << sprite::sprites.size() << std::endl;
}

void defaultHandGun::changeThisWeapon() 
{
	for (int i = 1; i < maxBulletPool; i++) {
		bs[i].sp.setVisibla(false);
		bs[i].sp.setspId(-1);
		bs[i].sp.setIsSprites(true);
		bs[i].sp.spritesToVector();
	}
}

Hand::Hand()
{
}

void Hand::fire()
{
}

void Hand::update(Vector2 playerPos, float rot)
{
}

void Hand::changeToAnotherWeapon()
{
}

void Hand::changeThisWeapon() {

}

defaultAr::defaultAr()
{
	itemId = 1;
	firerate = 50;//剐府技农
	damage = 10;
	bspeed = 20;
	numberOfBullet = 30;
	maxBullet = 30;
	reloadTime = 2000;
	reloading = false;
	canFire = true;
	distanceToGun = 60;
	distanceToMuzzle = 96;
	sp.init({ -100,-100 }, 32 * 4, 32 * 4, 0, 2, 0, { 16 * 4, 16 * 4 }, "resource/guns/defaultAr.png", 0, false);
	sp.spritesToVector();
	bs = new bullet[maxBulletPool];
	bs[0].init({ 0,0 }, 32 * 3, 32 * 3, 0, 0, 0, { 16 * 3,16 * 3 }, "resource/bullets/bullet.png", 0, bspeed, damage, 2 * 4);
	for (int i = 1; i < maxBulletPool; i++) {
		bs[i].sp.setVisibla(false);
		bs[i].sp.setspId(-1);
	}

	gunSound = LoadSound("resource/sounds/handgunSound.mp3");
}

defaultAr::~defaultAr()
{
	UnloadSound(gunSound);
	delete[] bs;
}

void defaultAr::fire()
{
	bool executeOnce = true;
	for (int i = 1; i < maxBulletPool; i++) {
		if (!bs[i].sp.Visible && executeOnce) {
			bool tmp = bs[i].sp.isSprites;
			int id = bs[i].sp.Id;
			bs[i] = bs[0];
			//bs[i].sp.setIsSprites(tmp);
			bs[i].sp.setspId(id);
			bs[i].sp.setglobalPos(firePos);
			bs[i].sp.setVisibla(true);
			bs[i].rotation = rotation;
			bs[i].fire();
			executeOnce = false;
		}
	}
}

void defaultAr::update(Vector2 playerPos, float rot)
{

	clock_t t = clock();
	if (lastTimeFire + firerate <= t && !canFire) {
		canFire = true;
	}
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !reloading && canFire) {
		canFire = false;
		lastTimeFire = t;
		if (numberOfBullet) {
			std::cout << "fire" << std::endl;
			sp.changeTexture(1);
			invokeChangeTexture(&sp, 0, 20);
			fire();
			PlaySoundMulti(gunSound);
			numberOfBullet--;
		}
	}
	if (numberOfBullet != maxBullet && IsKeyDown(KEY_R) && !reloading) {
		std::cout << "reloading" << std::endl;
		sp.changeTexture(2);
		invokeChangeTexture(&sp, 0, reloadTime);
		lastTimeReload = t;
		reloading = true;
		/*
		for (int i = 1; i < maxBulletPool; i++) {
			std::cout << "staw:" << bs[i].sp.isSprites << std::endl;
		}*/
	}
	if (lastTimeReload + reloadTime <= t && reloading) {
		std::cout << "reloading end" << std::endl;
		numberOfBullet = maxBullet;
		reloading = false;
	}
	for (int i = 1; i < maxBulletPool; i++) {
		if (bs[i].sp.Visible) {
			bs[i].update();
		}
	}
}

void defaultAr::changeToAnotherWeapon()
{
	//std::cout << "before:" << sprite::sprites.size() << std::endl;
	for (int i = 1; i < maxBulletPool; i++) {
		//std::cout << "staw:" << bs[i].sp.isSprites << std::endl;

		//std::cout << i << std::endl;
		bs[i].destructor();
	}
	//std::cout << "after:" << sprite::sprites.size() << std::endl;
}

void defaultAr::changeThisWeapon() 
{
	for (int i = 1; i < maxBulletPool; i++) {
		bs[i].sp.setVisibla(false);
		bs[i].sp.setspId(-1);
		bs[i].sp.setIsSprites(true);
		bs[i].sp.spritesToVector();
	}
}