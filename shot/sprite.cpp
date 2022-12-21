#include "sprite.h"


sprite::sprite()
{
	Pos = { 0,0 };
	depth = 0;
	Width = 0;
	Height = 0;
	depth = 0;
	Rotation = 0;
	maxTextureId = 0;
	textureId = 0;
	Origin = { 0,0 };
	sourceRec = { 0, 0, 0, 0 };
}

sprite::sprite(Vector2 pos, float width, float height, float rotation, int maxId, int Id, Vector2 origin, std::string file, float d)
{
	globalPos = pos;
	Pos = { globalPos.x - cam::camPos.x,globalPos.y - cam::camPos.y };
	Width = width;
	Height = height;
	depth = d;
	Rotation = rotation;
	maxTextureId = maxId;
	textureId = Id;
	Origin = origin;
	texture = LoadTexture(file.c_str());
	int w = texture.width / (maxTextureId + 1);
	int h = texture.height;
	sourceRec = { (float)w * textureId, 0, (float)w, (float)h };
}

void sprite::init(Vector2 pos, float width, float height, float rotation, int maxId, int Id, Vector2 origin, std::string file , float d)
{
	globalPos = pos;
	Pos = { globalPos.x - cam::camPos.x,globalPos.y - cam::camPos.y };
	Width = width;
	Height = height;
	depth = d;
	Rotation = rotation;
	maxTextureId = maxId;
	textureId = Id;
	Origin = origin;
	texture = LoadTexture(file.c_str());
	int w = texture.width / (maxTextureId + 1);
	int h = texture.height;
	sourceRec = { (float)w * textureId, 0, (float)w, (float)h };
	
}

void sprite::changeTexture(int Id) // 0~
{
	int w = texture.width / (maxTextureId + 1);
	int h = texture.height;
	sourceRec = { (float)w * Id, 0, (float)w, (float)h };
}

void sprite::unloadTexture()
{
	UnloadTexture(texture);
}


void sprite::setPos(float x, float y)
{
	Pos.x = x;
	Pos.y = y;
}

void sprite::setOrigin(float x, float y)
{
	Origin = { x,y };
}

void sprite::drawTexture()
{

	DrawTexturePro(texture, sourceRec, {Pos.x,Pos.y,Width,Height}, Origin, Rotation, WHITE);
}

void sprite::update()
{
	Pos = cam::getscreenPos(globalPos);
}
