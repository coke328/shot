#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "sprite.h"
#include "tile.h"

class tilemap {
public:
	tile** Tile;
	int tilecount;
	int width;
	int height;
	float scale;
	
	tilemap();
	void loadmap(string file);
	void drawtilemap();
};

/*
namespace tilemap {
	tile** Tile;
	int tilecount;
	int width;
	int height;
	float scale;

	void loadmap(string file);
	void drawtilemap();
}
*/