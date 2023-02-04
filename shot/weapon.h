#pragma once
#include "sprite.h"
#include "raylib.h"
#include "bullet.h"
#include "ui.h"
#include "effects.h"
#include <time.h>
#include <math.h>
#include <iostream>
#include <thread>

#define PI 3.14

class button {
private:
	bool singlePress;
	bool lastPress;
	int keyId;

public:
	void init(int id);
	bool keyPressed();
	bool mousePressed();
};

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
	float reloadTime;
	bool reloading;
	float Rt;
	float accuracy;
	float increaseOverlap;
	float Overlap;
	float decreaseOverlap;
	float angle;
	int maxEffectsPool;

	effectsCtrl muzzleFlame;
	sprite sp;

	weapon();
	virtual void fire() = 0;
	virtual void update(Vector2 playerPos, float rot, float distanceMouse) = 0;
	virtual void changeToAnotherWeapon() = 0;
	virtual void changeThisWeapon() = 0;
};

class weaponManager {
public:
	bool holdGun;
	ui aimPoint[2];

	weaponManager() : w(0) {}
	~weaponManager();

	void init();
	int getReloadingTime();
	float getRt();
	bool getisReloading();
	void fire();
	void changeToAnotherWeapon();
	void changeThisWeapon();
	void update(Vector2 playerPos, float rot, float distanceMouse);
	void changeWeapon(weapon* pw);

private:
	weapon* w;
};

class Hand : public weapon {
public:
	Hand();
	void fire() override;
	void update(Vector2 playerPos, float rot, float distanceMouse) override;
	void changeToAnotherWeapon() override;
	void changeThisWeapon() override;
};

class defaultHandGun : public weapon {
public:
	clock_t lastTimeFire;
	clock_t lastTimeReload;
	bool canFire;
	int numberOfBullet;
	int maxBullet;
	const int maxBulletPool = 50;
	float bspeed;
	bool singleFire;
	bool lastPressed;

	bullet* bs;
	Sound gunSound;
	button leftClick;

	defaultHandGun();
	~defaultHandGun();
	void fire() override;
	void update(Vector2 playerPos, float rot, float distanceMouse) override;
	void changeToAnotherWeapon() override;
	void changeThisWeapon() override;
};

class defaultAr : public weapon {
public:
	clock_t lastTimeFire;
	clock_t lastTimeReload;
	bool canFire;
	int numberOfBullet;
	int maxBullet;
	const int maxBulletPool = 50;
	float bspeed;



	bullet* bs;
	Sound gunSound;

	defaultAr();
	~defaultAr();
	void fire() override;
	void update(Vector2 playerPos, float rot, float distanceMouse) override;
	void changeToAnotherWeapon() override;
	void changeThisWeapon() override;
};