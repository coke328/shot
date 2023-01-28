#pragma once
#include "raylib.h"
#include <string>

class ui
{
private:
	Vector2 screenPos;
	int textureId;
	int maxTextureId;
	Vector2 Origin;
	bool Visible;
	int Depth;

	Texture2D texture;
	Rectangle destRec;
	Rectangle sourceRec;
public:
	ui(Rectangle sRec, int maxId, int id, Vector2 origin, std::string file, int depth, bool visible);
	void setVisible(bool v);
	void setTextureId(int id);
};

