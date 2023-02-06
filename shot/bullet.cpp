#include "bullet.h"

void bullet::init(Vector2 gPos,int w, int h, float r, int maxId, int id, Vector2 origin, std::string file, float d, float bspeed, float damage, int radius)
{
	Damage = damage;
	bb.setDamage(damage);
	bulletspeed = bspeed;
	sp.init(gPos,w,h,r,maxId,id,origin,file,d,true);
	Radius = radius;
}

void bullet::fire()
{
	Vector2 tmp = { cosf(rotation + PI / 2) * Radius,sinf(rotation + PI / 2) * Radius };
	Vector2 tmp2 = { cosf(rotation) * -bulletspeed,sinf(rotation) * -bulletspeed };
	bb.b[0].boundaryInit(sp.globalPos.x + tmp.x, sp.globalPos.y + tmp.y, sp.globalPos.x + tmp.x + tmp2.x, sp.globalPos.y + tmp.y + tmp2.y, false);
	bb.b[1].boundaryInit(sp.globalPos.x + -tmp.x, sp.globalPos.y + -tmp.y, sp.globalPos.x + -tmp.x + tmp2.x, sp.globalPos.y + -tmp.y + tmp2.y, false);
}

void bullet::update()
{
	Vector2 tmp = { cosf(rotation) * bulletspeed , sinf(rotation) * bulletspeed };
	sp.globalPos.x += tmp.x;
	sp.globalPos.y += tmp.y;
	sp.setRotation(rotation);
	sp.depth = sp.globalPos.y;
	bb.b[0].movePos({ tmp.x,tmp.y });
	bb.b[1].movePos({ tmp.x,tmp.y });
	Vecbool result = bb.collid();
	if (result.iscollid) {
		sp.setVisibla(false);
	}
}

void bullet::destructor()
{
	sp.spriteRemoveFromVector();
}



void bulletCtrl::destructor()
{
	for (int i = 1; i < maxPool; i++) {
		bulletPool[i].destructor();
	}
}

void bulletCtrl::init(Vector2 gPos, int w, int h, float r, int maxId, int id, Vector2 origin, std::string file, float d, float bSpeed, float damage, int radius, int mPool)
{
	bulletPool = new bullet[mPool];
	maxPool = mPool;
	bulletPool[0].init(gPos, w, h, r, maxId, id, origin, file, d, bSpeed, damage, radius);
	for (int i = 1; i < mPool; i++) {
		bulletPool[i].sp.setVisibla(false);
		bulletPool[i].sp.setspId(-1);
	}
}

void bulletCtrl::fireBullet(Vector2 firePos,float rotation,float angle)
{
	for (int i = 1; i < maxPool; i++) {
		if (!bulletPool[i].sp.Visible) {

			srand(clock());
			float rAngle = (rand() % (int)round(angle * 2 + 1)) - angle;
			int id = bulletPool[i].sp.Id;
			bulletPool[i] = bulletPool[0];
			bulletPool[i].sp.setspId(id);
			bulletPool[i].sp.setglobalPos(firePos);
			bulletPool[i].sp.setVisibla(true);
			bulletPool[i].rotation = rotation + rAngle * PI / 1800;
			bulletPool[i].fire();
			break;
		}
	}
}

void bulletCtrl::updateBullet()
{
	for (int i = 1; i < maxPool; i++) {
		if (bulletPool[i].sp.Visible) {
			bulletPool[i].update();
		}
	}
}

void bulletCtrl::holdThis()
{
	for (int i = 1; i < maxPool; i++) {
		bulletPool[i].sp.setVisibla(false);
		bulletPool[i].sp.setspId(-1);
		bulletPool[i].sp.setIsSprites(true);
		bulletPool[i].sp.spritesToVector();
	}
}
