#pragma once
#include "raylib.h"
#include "cam.h"
#include <string>
#include <vector>
#include <iostream>

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
	int Id;
	bool Yfliped;
	bool Visible;
	bool isSprites;

	static std::vector<sprite*> sprites;
	static int cnt;

	sprite();
	sprite(Vector2 pos,float width, float height, float rotation,int maxId, int Id, Vector2 origin, std::string file, float d, bool visible);
	void init(Vector2 pos, float width, float height, float rotation, int maxId, int Id, Vector2 origin, std::string file, float d, bool visible);
	void changeTexture(int Id);
	void unloadTexture();
	void setPos(float Px, float Py);
	void setglobalPos(Vector2 gPos);
	void setOrigin(float x, float y);
	void setRotation(float radian);
	void spritesToVector();
	void spriteRemoveFromVector();
	void flipY();
	void setVisibla(bool visible);
	void setspId(int id);
	void setIsSprites(bool in);
	void drawTexture();
	void update();
};