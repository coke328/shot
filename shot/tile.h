#pragma once
#include "raylib.h"
#include "cam.h"
#include <iostream>

class tile
{
public:
	Vector2 globalPos;
	Vector2 localPos;
	int height;
	int tiletype;
	static void textureLoad();
	static void unloadtexture();
	tile();
	tile(int type, Vector2 globalpos,int h);
	void drawtile(float scale);
	void update();
	void init(int type, Vector2 globalpos, int h);
};