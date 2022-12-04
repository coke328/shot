#pragma once
#include "raylib.h"
#include <string>

using namespace std;

class sprite {
public:
	Vector2 Pos;
	Vector2 Origin;
	float Width;
	float Height;
	float Rotation;
	Rectangle sourceRec;
	Texture2D texture;
	int maxTextureId;
	int textureId;
	sprite();
	sprite(Vector2 pos,float width, float height, float rotation,int maxId, int Id, Vector2 origin, string file);
	void init(Vector2 pos, float width, float height, float rotation, int maxId, int Id, Vector2 origin, string file);
	void changeTexture(int Id);
	void unloadTexture();
	void setPos(float x,float y);
	void setOrigin(float x, float y);
	void setscaleY(float y);
	void drawTexture();
};