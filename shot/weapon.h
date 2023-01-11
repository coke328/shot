#pragma once
#include "sprite.h"
#include "raylib.h"
#include <time.h>
#include <math.h>
#include <iostream>

class weapon
{
public:
	float firerate;
	float damage;
	float rotation;
	float distanceToGun;
	Vector2 firePos;
	clock_t lastTimeFire;
	bool canFire;
	sprite* sp;
	virtual void fire() = 0;
	virtual void update(Vector2 playerPos, float rot) = 0;
};

class defaltGun : public weapon{
public:
	defaltGun();
	void fire() override;
	void update(Vector2 playerPos, float rot) override;
};

class weaponManager {
public:
	weaponManager() : w(0) {}
	~weaponManager();

	void fire();
	void update(Vector2 playerPos, float rot);
	void changeWeapon(weapon* pw);

private:
	weapon* w;
};