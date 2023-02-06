#pragma once
#include "raylib.h"
#include "sprite.h"
#include "cam.h"
#include "boundarys.h"
#include "sprite.h"
#include <cmath>

class bullet
{
public:
	float Damage;
	float bulletspeed;
	float rotation;
	int Radius;

	bulletBound bb;

	sprite sp;

	void init(Vector2 gPos, int w, int h, float r, int maxId, int id, Vector2 origin, std::string file, float d, float bSpeed, float damage, int radius);
	void fire();
	virtual void update();
	void destructor();
};

class bulletCtrl {
public:
	bullet* bulletPool;
	int maxPool;

	void destructor();
	void init(Vector2 gPos, int w, int h, float r, int maxId, int id, Vector2 origin, std::string file, float d, float bSpeed, float damage, int radius, int mPool);
	void fireBullet(Vector2 firePos, float rotation, float angle);
	void updateBullet();
	void holdThis();
};
