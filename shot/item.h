#pragma once
#include "weapon.h"
#include <list>
#include <math.h>

enum ItemType{
	defaultHandgun = 1,
	defaultar,
	litesniper,
	maxWeapons,
	healkit,

};

std::string getItemName(int itemType);

class item
{
private:
	
	int itemId;
	int maxTidx;
	bool isWeapon;
	bool onGround;
	Vector2 globalPos;
	Vector2 Pos;
	weapon* w;
	sprite itemUi;
	sprite f;

public:
	

	item();
	void init(Vector2 globalPos);
	void update();
	Vector2 getGlobalPos();
	void displayF();
	void eraseF();
};

class itemCtrl {
	std::list<item*> inventoryitem;
	Vector2* playerGLobalPos;
	std::list<item> items;

	void linkplayerGlobalPos(Vector2* gPos);
	void getItem();
	void update();
};