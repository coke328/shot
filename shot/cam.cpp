#include "cam.h"

int cam::camWidth = 800;
int cam::camHeight = 600;
Vector2 cam::camPos = { 0,0 };

Vector2 cam::getscreenPos(Vector2 globalPos)
{
	Vector2 result;
	result.x = globalPos.x - camPos.x;
	result.y = globalPos.y - camPos.y;
	return result;
}

void cam::setcamPos(Vector2 Pos)
{
	cam::camPos.x = Pos.x - cam::camWidth / 2;
	cam::camPos.y = Pos.y - cam::camHeight / 2;
}
