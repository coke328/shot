#include "weapon.h"

weaponManager::~weaponManager()
{
	if (w) delete w;
}

void weaponManager::fire()
{
	w->fire();
}

void weaponManager::update(Vector2 playerPos, float rot)
{
	w->firePos.x = playerPos.x + cosf(rot) * w->distanceToGun;
	w->firePos.y = playerPos.y + sinf(rot) * w->distanceToGun;
	w->rotation = rot;
	clock_t t = clock();
	if (w->canFire) {
		std::cout << "defaltFire" << std::endl;
		w->lastTimeFire = t;
	}
	else if (w->lastTimeFire + w->firerate <= t) {
		w->canFire = true;
	}
	w->update(playerPos,rot);
}

void weaponManager::changeWeapon(weapon* pw)
{
	if (w) delete w;
	w = pw;
}

defaltGun::defaltGun()
{
	firerate = 500;//밀리세크
	damage = 10;
}

void defaltGun::fire()
{
}

void defaltGun::update(Vector2 playerPos, float rot)
{
	
}
