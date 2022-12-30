#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "sprite.h"
#include "tile.h"
#include "sprite.h"
#include "spriteCtrl.h"
#include "pillar.h"
#include <vector>

using namespace std;

class tilemap {
public:
	tile** Tile;
	int tilecount;
	int width;
	int height;
	float scale;

	std::vector<sprite> walls;
	std::vector<pillar> pillars;
	
	tilemap();
	void loadmap(std::string file);
	static void unloadT();
	void drawtilemap();
	void load();
	void loadlongwall(Vector2 wallPos, bool state);
};