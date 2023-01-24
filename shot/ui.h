#pragma once
#include "raylib.h"

class ui
{
private:
	Vector2 screenPos;
	int textureId;
	int maxTextureId;

	Texture2D texture;
	Rectangle destRec;
	Rectangle sourceRec;
public:
	ui();
};

