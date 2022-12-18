#include "tile.h"

Texture2D texture;

void tile::drawtile(float scale)
{
	Rectangle tmp = { 0,0,0,0 };
	if (tiletype > 0) {
		tmp = { (float)64 * (tiletype - 1),0,(float)64 * tiletype,32 };
	}
	Rectangle dest = { localPos.x,localPos.y,128 * scale,64 * scale };
	DrawTexturePro(texture, tmp, dest, { 0,0 }, 0, WHITE);
}

void tile::update()
{
	localPos.x = globalPos.x - cam::camPos.x;
	localPos.y = globalPos.y - cam::camPos.y;
}

void tile::init(int type, Vector2 globalpos, float h)
{
	globalPos = globalpos;
	height = h;
	tiletype = type;
	localPos = { globalPos.x - cam::camPos.x,globalPos.y - cam::camPos.y };
}

void tile::textureLoad()
{
	
	texture = LoadTexture("resource/tile.png");
}

tile::tile()
{
	globalPos = { 0,0 };
	height = 0;
	tiletype = 0;
	localPos = { 0,0 };
}

tile::tile(int type, Vector2 globalpos, float h) {
	globalPos = globalpos;
	height = h;
	tiletype = type;
	localPos = { globalPos.x - cam::camPos.x,globalPos.y - cam::camPos.y };
}
