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
			int idx = s.find(",");
			int t;
			int h;
			sscanf_s(s.substr(0,idx).c_str(), "%d", &t);
			sscanf_s(s.substr(idx + 1).c_str(), "%d", &h);

			Vector2 tmp = { 32 * scale * (i + j), 16 * scale * (i - j - 1) };
			Tile[j][i].init(t, tmp, h);
		}
	}

	myfile.close();

	boundarys::staticboundarysInit(width, height, scale);
}

void tilemap::unloadT()
{
	tile::unloadtexture();
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

void tilemap::load()
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (y == 0) {
				loadlongwall(Tile[x][y].globalPos, 0);//leftwall
			}

			if (x == width - 1) {
				loadlongwall(Tile[x][y].globalPos, 1);//rightwall
			}
			if (Tile[x][y].height != 0) {
				pillar p(Tile[x][y].globalPos, Tile[x][y].height, 4, Tile[x][y].tiletype);
				pillars.push_back(p);
			}
		
		}
	}
	for (int i = 0; i < walls.size(); i++) {//wallsprite to sprites vectors
		spriteCtrl::sprites.push_back(&walls[i]);
	}
	for (int i = 0; i < pillars.size(); i++) {
		pillars[i].partsToSprites();
	}
}

void tilemap::loadlongwall(Vector2 wallPos, bool state)
{
	sprite tmp;
	if (state) {
		tmp.init({ wallPos.x + 32 * scale,wallPos.y - 240 * scale}, 32 * scale, 256 * scale, 0, 1, 1, { 0,0 }, "resource/longwall.png", wallPos.y);
	}
	else {
		tmp.init({ wallPos.x,wallPos.y - 240 * scale }, 32 * scale, 256 * scale, 0, 1, 0, { 0,0 }, "resource/longwall.png", wallPos.y);
	}
	walls.push_back(tmp);
}

