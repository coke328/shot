#pragma once
#include "raylib.h"
#include "cam.h"
#include <string>
#include <vector>
#include <iostream>

class ui
{
private:
	int textureId;
	int maxTextureId;
	Vector2 Origin;
	bool Visible;
	int Depth;
	float rot;

	Texture2D texture;
	Rectangle destRec;
	Rectangle sourceRec;
public:
	ui();
	ui(Rectangle dRec, int maxId, int id, Vector2 origin, std::string file, int depth, bool visible);
	void init(Rectangle dRec, int maxId, int id, Vector2 origin, std::string file, int depth, bool visible);
	void setVisible(bool v);
	void setTextureId(int id);
	void setPos(Vector2 p);
	void setRotation(float angle);
	void setGlobalPos(Vector2 gPos);
	int getDepth();
	void drawUi();
	void unloadTexture();
};

class uiCtrl {
public:
	static std::vector<ui*> Uis;

	static void push(ui* u);
	void drawUi();
	void unloadTexture();
};