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
		if(!friendly) {
			
		}
	}
}

void bullet::destructor()
{
	sp.spriteRemoveFromVector();
}

