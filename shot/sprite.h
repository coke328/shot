#pragma once
#include "raylib.h"
#include "cam.h"
#include <string>

class sprite {
public:
	Vector2 Pos;
	Vector2 globalPos;
	Vector2 Origin;
	float depth;
	float Width;
	float Height;
	float Rotation;
	Rectangle sourceRec;
	Texture2D texture;
	int maxTextureId;
	int textureId;
	sprite();
	sprite(Vector2 pos,float width, float height, float rotation,int maxId, int Id, Vector2 origin, std::string file, float d);
	void init(Vector2 pos, float width, float height, float rotation, int maxId, int Id, Vector2 origin, std::string file, float d);
	void changeTexture(int Id);
	void unloadTexture();
	void setPos(float x,float y);
	void setOrigin(float x, float y);
	void drawTexture();
	void update();
};