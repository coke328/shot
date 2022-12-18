#pragma once
#include "raylib.h"
#include "cam.h"
#include <iostream>

class tile
{
public:
	Vector2 globalPos;
	Vector2 localPos;
	float height;
	int tiletype;
	//static Texture2D texture;
	static void textureLoad();
	tile();
	tile(int type, Vector2 globalpos,float h);
	void drawtile(float scale);
	void update();
	void init(int type, Vector2 globalpos, float h);
};