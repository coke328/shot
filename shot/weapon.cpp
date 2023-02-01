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

void button::init(int id) {
	keyId = id;
	singlePress = false;
	lastPress = false;
}

bool button::keyPressed() {
	if (singlePress == false && IsKeyDown(keyId)) {
		singlePress = true;
	}
	else {
		singlePress = false;
	}
	if (IsKeyDown(keyId)) {
		if (lastPress && singlePress) {
			singlePress = false;
		}
		lastPress = true;
	}
	else {
		lastPress = false;
	}
	return singlePress;
}

bool button::mousePressed() {
	{
		if (singlePress == false && IsMouseButtonDown(keyId)) {
			singlePress = true;
		}
		else {
			singlePress = false;
		}
		if (IsMouseButtonDown(keyId)) {
			if (lastPress && singlePress) {
				singlePress = false;
			}
			lastPress = true;
		}
		else {
			lastPress = false;
		}
	}
	return singlePress;
}

void weaponManager::init() {
	aimPoint[0].init({ 0,0,8 * 4,8 * 4 }, 0, 0, { 3.5 * 4,4.5 * 4 }, "resource/Ui/aimPointLeft.png", 0, false);
	aimPoint[1].init({ 0,0,8 * 4,8 * 4 }, 0, 0, { 4.5 * 4,4.5 * 4 }, "resource/Ui/aimPointRight.png", 0, false);
	uiCtrl::push(&aimPoint[0]);
	uiCtrl::push(&aimPoint[1]);
	holdGun = false;
}

weaponManager::~weaponManager()
{
	if (w) delete w;
}

int weaponManager::getReloadingTime()
{
	if (w->reloading) {
		return w->reloadTime;
	}
	return 0;
}

float weaponManager::getRt()
{
	return w->Rt;
}

bool weaponManager::getisReloading()
{
	return w->reloading;
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

void weaponManager::update(Vector2 playerPos, float rot, float distanceMouse)
{
	if (holdGun) {
		float cos = cosf(rot);
		float sin = sinf(rot);
		w->firePos.x = playerPos.x + cos * w->distanceToMuzzle;
		w->firePos.y = playerPos.y + sin * w->distanceToMuzzle / 1;
		w->gunPos.x = playerPos.x + cos * w->distanceToGun;
		w->gunPos.y = playerPos.y + sin * w->distanceToGun / 1;
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
		if (distanceMouse > w->distanceToMuzzle) {
			
			float rightAngle = rot + (w->angle * PI / 1800);// 
			//aimPoint[0].setGlobalPos({ cosf(rightAngle) * fPosmPos + w->firePos.x, sinf(rightAngle) * fPosmPos + w->firePos.y });
			aimPoint[0].setGlobalPos({ cosf(rightAngle) * distanceMouse + playerPos.x, sinf(rightAngle) * distanceMouse + playerPos.y });
			aimPoint[0].setRotation(rot * 180 / PI + 90);

			float leftAngle = rot - (w->angle * PI / 1800);// 
			//aimPoint[1].setGlobalPos({ cosf(leftAngle) * fPosmPos + w->firePos.x, sinf(leftAngle) * fPosmPos + w->firePos.y });
			aimPoint[1].setGlobalPos({ cosf(leftAngle) * distanceMouse + playerPos.x, sinf(leftAngle) * distanceMouse + playerPos.y });
			aimPoint[1].setRotation(rot * 180 / PI + 90);

			aimPoint[0].setVisible(true);
			aimPoint[1].setVisible(true);
		}
		else {
			aimPoint[0].setVisible(false);
			aimPoint[1].setVisible(false);
		}
		
		w->update(playerPos, rot, distanceMouse);
	}
	else {
		aimPoint[0].setVisible(false);
		aimPoint[1].setVisible(false);
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

weapon::weapon() {
	
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
	lastTimeReload = 0;
	accuracy = 5;
	increaseAccuracy = 1;
	increaseOverlap = 0;
	decreaseOverlap = 0.1;
	sp.init({ -100,-100 }, 32 * 4, 32 * 4, 0, 3, 0, {16 * 4, 16 * 4},"resource/guns/defaltHandgun.png",0,false);
	sp.spritesToVector();
	bs = new bullet[maxBulletPool];
	bs[0].init({0,0}, 32 * 4, 32 * 4, 0, 0, 0, {16 * 4,16 * 4}, "resource/bullets/bullet.png", 0, bspeed, damage, 2*4);
	for (int i = 1; i < maxBulletPool; i++) {
		bs[i].sp.setVisibla(false);
		bs[i].sp.setspId(-1);
	}

	gunSound = LoadSound("resource/sounds/handgunSound.mp3");

	leftClick.init(MOUSE_BUTTON_LEFT);
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
			
			srand(clock());
			float rAngle = (rand() % (int)round(angle * 2 + 1)) - angle;
			int id = bs[i].sp.Id;
			bs[i] = bs[0];
			bs[i].sp.setspId(id);
			bs[i].sp.setglobalPos(firePos);
			bs[i].sp.setVisibla(true);
			bs[i].rotation = rotation + rAngle * PI / 1800;
			bs[i].fire();
			executeOnce = false;
		}
	}
}

void defaultHandGun::update(Vector2 playerPos, float rot, float distanceMouse)
{

	clock_t t = clock();
	if (lastTimeFire + firerate <= t && !canFire) {
		canFire = true;
	}
	angle = 10 * (accuracy + increaseAccuracy * increaseOverlap);
	
	if (leftClick.mousePressed() && !reloading && canFire) {
		canFire = false;
		//singleShot = false;
		if (numberOfBullet) {
			sp.changeTexture(1);
			invokeChangeTexture(&sp, 0, 100);
			fire();
			PlaySoundMulti(gunSound);
			numberOfBullet--;
			
			increaseOverlap += increaseAccuracy;
			
		}
		lastTimeFire = t;
	}
	if (increaseOverlap >= decreaseOverlap) {
		increaseOverlap -= decreaseOverlap;
	}
	else {
		increaseOverlap = 0;
	}
	if (numberOfBullet != maxBullet && IsKeyDown(KEY_R) && !reloading) {
		sp.changeTexture(2);
		invokeChangeTexture(&sp, 0, reloadTime);
		lastTimeReload = t;
		reloading = true;
	}
	Rt = lastTimeReload + reloadTime - t;
	if (Rt <= 0 && reloading) {
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
	lastTimeReload = clock();
}

Hand::Hand()
{
}

void Hand::fire()
{
}

void Hand::update(Vector2 playerPos, float rot, float distanceMouse)
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
	lastTimeReload = 0;
	accuracy = 5;
	increaseAccuracy = 1;
	increaseOverlap = 0;
	decreaseOverlap = 0.1;
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
			
			srand(clock());
			float rAngle = (rand() % (int)round(angle * 2 + 1)) - angle;
			int id = bs[i].sp.Id;
			bs[i] = bs[0];
			bs[i].sp.setspId(id);
			bs[i].sp.setglobalPos(firePos);
			bs[i].sp.setVisibla(true);
			bs[i].rotation = rotation + rAngle * PI / 1800;
			bs[i].fire();
			executeOnce = false;
		}
	}
}

void defaultAr::update(Vector2 playerPos, float rot, float distanceMouse)
{

	clock_t t = clock();
	if (lastTimeFire + firerate <= t && !canFire) {
		canFire = true;
	}
	angle = 10 * (accuracy + increaseAccuracy * increaseOverlap);
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !reloading && canFire) {
		canFire = false;
		if (numberOfBullet) {
			sp.changeTexture(1);
			invokeChangeTexture(&sp, 0, 20);
			fire();
			PlaySoundMulti(gunSound);
			numberOfBullet--;

			increaseOverlap += increaseAccuracy;
			
		}
		lastTimeFire = t;
	}
	if (increaseOverlap >= decreaseOverlap) {
		increaseOverlap -= decreaseOverlap;
	}
	else {
		increaseOverlap = 0;
	}
	if (numberOfBullet != maxBullet && IsKeyDown(KEY_R) && !reloading) {
		sp.changeTexture(2);
		invokeChangeTexture(&sp, 0, reloadTime);
		lastTimeReload = t;
		reloading = true;
		/*
		for (int i = 1; i < maxBulletPool; i++) {
			std::cout << "staw:" << bs[i].sp.isSprites << std::endl;
		}*/
	}
	Rt = lastTimeReload + reloadTime - t;
	if (Rt <= 0 && reloading) {
		numberOfBullet = maxBullet;
		reloading = false;
		increaseOverlap = 0;
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
	lastTimeReload = clock();
}
