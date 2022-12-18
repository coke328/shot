#include "tilemap.h"

tilemap::tilemap()
{
	scale = 4;
	width = 0; 
	height = 0;
	tilecount = 0;
}

void tilemap::loadmap(string file)
{
	tile::textureLoad();

	ifstream myfile(file);
	string s;
	myfile >> s;

	sscanf_s(s.c_str(), "%d", &width);
	myfile >> s;

	sscanf_s(s.c_str(), "%d", &height);

	tilecount = width * height;

	Tile = new tile*[width];
	for (int i = 0; i < height; i++) {
		Tile[i] = new tile[height];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			myfile >> s;
			int t;
			sscanf_s(s.c_str(), "%d", &t);

			Vector2 tmp = { 32 * scale * (i + j), 16 * scale * (i - j - 1) };
			Tile[j][i].init(t, tmp, 0);
		}
	}

	myfile.close();
}

void tilemap::drawtilemap()
{
	for (int i = 0; i < height; i++) {
		for (int j = width - 1; j >= 0; j--) {
			Tile[j][i].update();
			Tile[j][i].drawtile(scale);
		}
	}
}
