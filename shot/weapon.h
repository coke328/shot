#pragma once
#include "sprite.h"
#include "raylib.h"
#include "bullet.h"
#include <time.h>
#include <math.h>
#include <iostream>
#include <thread>

#define PI 3.14

class weapon
{
public:
	int itemId;

	float firerate;
	float damage;
	float rotation;
	float distanceToMuzzle;
	float distanceToGun;
	Vector2 firePos;
	Vector2 gunPos;
	bool isGunFlip;

	sprite sp;

	virtual void fire() = 0;
	virtual void update(Vector2 playerPos, float rot) = 0;
	virtual void changeToAnotherWeapon() = 0;
};

class weaponManager {
public:
	bool holdGun;

	weaponManager() : w(0) {}
	~weaponManager();

	void fire();
	void changeToAnotherWeapon();
	void update(Vector2 playerPos, float rot);
	void changeWeapon(weapon* pw);

private:
	weapon* w;
};

class Hand : public weapon {
public:
	Hand();
	void fire() override;
	void update(Vector2 playerPos, float rot) override;
	void changeToAnotherWeapon() override;
};

class defaultHandGun : public weapon {
public:
	clock_t lastTimeFire;
	clock_t lastTimeReload;
	bool canFire;
	int numberOfBullet;
	int maxBullet;
	float reloadTime;
	bool reloading;
	const int maxBulletPool = 50;
	float bspeed;

	bullet* bs;

	defaultHandGun();
	~defaultHandGun();
	void fire() override;
	void update(Vector2 playerPos, float rot) override;
	void changeToAnotherWeapon() override;
};