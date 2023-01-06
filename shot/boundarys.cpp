#include "boundarys.h"

std::vector<boundary> boundarys::staticbounds;

boundarys::boundarys()
{
	boundcnt = 0;
}

void boundarys::init(int cnt) {
	boundcnt = cnt;
	for (int i = 0; i < bounds.size(); i++) {
		int size = staticbounds.size();
		boundary& b = bounds[i];
		b.bsaves = new float[size*2];
		b.ps = new bool[size];
		for (int j = 0; j < size*2; j++) {
			b.bsaves[j] = 0;
		}
		for (int j = 0; j < size; j++) {
			b.ps[j] = 0;
		}
	}
}

void boundarys::setboundaryPos(Vector2 globalPos)
{
	for (int i = 0; i < boundcnt - 1; i++) {
		bounds[i].boundaryInit(globalPos.x + blocalPos[i].x, globalPos.y + blocalPos[i].y, globalPos.x + blocalPos[i + 1].x, globalPos.y + blocalPos[i + 1].y, 0);
	}
	bounds[boundcnt - 1].boundaryInit(globalPos.x + blocalPos[boundcnt - 1].x, globalPos.y + blocalPos[boundcnt - 1].y, globalPos.x + blocalPos[0].x, globalPos.y + blocalPos[0].y, 0);
}


void boundarys::staticboundarysInit(int w, int h, float scale)
{
	staticbounds.emplace_back(0, 0, w * 32 * scale, h * -16 * scale, true);
	staticbounds.emplace_back(w * 32 * scale, h * -16 * scale, w * 64 * scale, 0, true);
	staticbounds.emplace_back(0, 0, w * 32 * scale, h * 16 * scale, true);
	staticbounds.emplace_back(w * 32 * scale, h * 16 * scale, w * 64 * scale, 0, true);

}
/*
void boundarys::collid(Vector2 &globalPos, Vector2 &vel)
{

	setboundaryPos(globalPos);

	for (int i = 0; i < bounds.size(); i++) {
		for (int j = 0; j < staticbounds.size(); j++) {
			boundary stb = staticbounds[j];
			vecbool tmp = bounds[i].isCollid(stb,j);
			if (tmp.iscollid && tmp.point.x != 0 && tmp.point.y != 0) {
				
				Vector2 p = tmp.point;

				globalPos.x = (stb.b * (stb.b * p.x - stb.a * p.y) - stb.a * stb.c) / (stb.a * stb.a + stb.b * stb.b)-p.x + globalPos.x;
				globalPos.y = (stb.a * (stb.a * p.y - stb.b * p.x) - stb.b * stb.c) / (stb.a * stb.a + stb.b * stb.b)-p.y + globalPos.y;

				setboundaryPos(globalPos);
				
				float t = (stb.a * vel.x + stb.b * vel.y) / (stb.a * stb.a + stb.b * stb.b);
				vel.x -= t * stb.a;
				vel.y -= t * stb.b;
				
			}
		}
	}
}
*/
vec2::vec2(float inx, float iny)
{
	x = inx;
	y = iny;
}

void slipcollid::collid(Vector2& globalPos, Vector2& vel)
{
	setboundaryPos(globalPos);

	for (int i = 0; i < bounds.size(); i++) {
		for (int j = 0; j < staticbounds.size(); j++) {
			boundary stb = staticbounds[j];
			vecbool tmp = bounds[i].isCollid(stb, j);
			if (tmp.iscollid && tmp.point.x != 0 && tmp.point.y != 0) {

				Vector2 p = tmp.point;

				globalPos.x = (stb.b * (stb.b * p.x - stb.a * p.y) - stb.a * stb.c) / (stb.a * stb.a + stb.b * stb.b) - p.x + globalPos.x;
				globalPos.y = (stb.a * (stb.a * p.y - stb.b * p.x) - stb.b * stb.c) / (stb.a * stb.a + stb.b * stb.b) - p.y + globalPos.y;

				setboundaryPos(globalPos);

				float t = (stb.a * vel.x + stb.b * vel.y) / (stb.a * stb.a + stb.b * stb.b);
				vel.x -= t * stb.a;
				vel.y -= t * stb.b;

			}
		}
	}
}
