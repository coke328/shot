#pragma once
#include "raylib.h"

class cam {
public:
	static Vector2 camPos;
	static int camWidth;
	static int camHeight;
	static Vector2 getscreenPos(Vector2 globalPos);
	static void setcamPos(Vector2 Pos);
};
