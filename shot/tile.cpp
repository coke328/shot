#include "tile.h"

Texture2D texture;

void tile::drawtile(float scale)
{
	Rectangle tmp = { 0,0,0,0 };
	if (height == 0) {
		tmp = { (float)64 * tiletype,0,64,32 };
	}
	Rectangle dest = { localPos.x,localPos.y,64 * scale,32 * scale };
	DrawTexturePro(texture, tmp, dest, { 0,0 }, 0, WHITE);
}

void tile::update()
{
	localPos.x = globalPos.x - cam::camPos.x;
	localPos.y = globalPos.y - cam::camPos.y;
}

void tile::init(int type, Vector2 globalpos, int h)
{
	globalPos = globalpos;
	height = h;
	tiletype = type;
	localPos = { globalPos.x - cam::camPos.x,globalPos.y - cam::camPos.y };
	if (height > 0) {

	}
}

void tile::textureLoad()
{
	
	texture = LoadTexture("resource/tile.png");
}

void tile::unloadtexture() {
	UnloadTexture(texture);
}

tile::tile()
{
	globalPos = { 0,0 };
	height = 0;
	tiletype = 0;
	localPos = { 0,0 };
}

tile::tile(int type, Vector2 globalpos, int h) {
	globalPos = globalpos;
	height = h;
	tiletype = type;
	localPos = { globalPos.x - cam::camPos.x,globalPos.y - cam::camPos.y };
}
