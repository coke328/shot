#include "boundarys.h"

std::vector<boundary> boundarys::staticbounds;
int boundarys::dyboundcnt;
int boundarys::holeidxstart;

boundarys::boundarys()
{
	boundcnt = 0;
}

boundarys::~boundarys()
{
	for (int i = 0; i < bounds.size(); i++) {
		bounds[i].removeMemory();
	}
}

void boundarys::init(int cnt, int idx) {
	boundcnt = cnt;
	id = idx;
	int size = boundarys::staticbounds.size();
	for (int i = 0; i < bounds.size(); i++) {
		boundary& b = bounds[i];
		b.bsaves = new float[size*2]();
		b.ps = new bool[size]();
	}
}

void boundarys::setboundaryPos(Vector2 gPos)
{
	globalPos = gPos;
	for (int i = 0; i < boundcnt - 1; i++) {
		bounds[i].boundaryInit(globalPos.x + blocalPos[i].x, globalPos.y + blocalPos[i].y, globalPos.x + blocalPos[i + 1].x, globalPos.y + blocalPos[i + 1].y, 0);
	}
	bounds[boundcnt - 1].boundaryInit(globalPos.x + blocalPos[boundcnt - 1].x, globalPos.y + blocalPos[boundcnt - 1].y, globalPos.x + blocalPos[0].x, globalPos.y + blocalPos[0].y, 0);
}

void boundarys::boundset()
{
	int size = blocalPos.size();
	for (int i = 0; i < size-1; i++) {
		bounds.emplace_back(globalPos.x + blocalPos[i].x, globalPos.y + blocalPos[i].y, globalPos.x + blocalPos[i + 1].x, globalPos.y + blocalPos[i + 1].y, false);
	}
	bounds.emplace_back(globalPos.x + blocalPos[size - 1].x, globalPos.y + blocalPos[size - 1].y, globalPos.x + blocalPos[0].x, globalPos.x + blocalPos[0].y, false);
}


void boundarys::staticboundarysInit()
{
	
	for (int i = 0; i < boundarys::staticbounds.size(); i++) {
		boundary& b = boundarys::staticbounds[i];
		b.bsaves = new float[dyboundcnt * 2]();
		b.ps = new bool[dyboundcnt*2]();
	}
}

void boundarys::suburbbound(int w, int h, float scale)
{
	boundarys::staticbounds.emplace_back(0, 0, w * 32 * scale, h * -16 * scale, true);
	boundarys::staticbounds.emplace_back(w * 32 * scale, h * -16 * scale, w * 64 * scale, 0, true);
	boundarys::staticbounds.emplace_back(0, 0, w * 32 * scale, h * 16 * scale, true);
	boundarys::staticbounds.emplace_back(w * 32 * scale, h * 16 * scale, w * 64 * scale, 0, true);
	boundarys::holeidxstart += 4;
}

vec2::vec2(float inx, float iny)
{
	x = inx;
	y = iny;
}

bool slipcollid::collid(Vector2& globalPos, Vector2& vel)
{
	setboundaryPos(globalPos);
	
	for (int i = 0; i < bounds.size(); i++) {
		for (int j = 0; j < boundarys::staticbounds.size(); j++) {
			Vecbool tmp = bounds[i].isCollid(boundarys::staticbounds[j], j, i);
			
			if (tmp.iscollid && !(tmp.point.x == 0 && tmp.point.y == 0)) {
				Vector2 p = tmp.point;
				boundary b;
				//std::cout << tmp.collsitu << " : " << p.x << " , " << p.y << std::endl;
				//Vector2 tmppos = { globalPos.x - vel.x,globalPos.y - vel.y };
				bool t = false;
				setboundaryPos(globalPos);
				if (tmp.collsitu) {
					
					b = boundarys::staticbounds[j];
					globalPos.x += (b.b * (b.b * p.x - b.a * p.y) - b.a * b.c) / (b.a * b.a + b.b * b.b) - p.x;
					globalPos.y += (b.a * (b.a * p.y - b.b * p.x) - b.b * b.c) / (b.a * b.a + b.b * b.b) - p.y;
					t = true;
					
				}
				else{
					
					b = bounds[i];
					globalPos.x -= (b.b * (b.b * p.x - b.a * p.y) - b.a * b.c) / (b.a * b.a + b.b * b.b) - p.x;
					globalPos.y -= (b.a * (b.a * p.y - b.b * p.x) - b.b * b.c) / (b.a * b.a + b.b * b.b) - p.y;
					t = true;
					
				}
				
				if(t){
					

					float t = (b.a * vel.y - b.b * vel.x) / (b.a * b.a + b.b * b.b);
					vel.x = -t * b.b;
					vel.y = t * b.a;
					//vel = { globalPos.x - tmppos.x,globalPos.y - tmppos.y };
					//std::cout << vel.x << " , " << vel.y << std::endl;
				}
				
				
			}
			
		}
		
	}
	return false;
}

Vecbool bulletBound::collid()
{
	Vecbool result;
	result.iscollid = false;
	result.point = { 0,0 };

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < boundarys::staticbounds.size(); j++) {
			Vecbool tmp = isboundmeet(b[i], boundarys::staticbounds[j]);
			if (tmp.iscollid) {
				result.iscollid = true;
				result.point = tmp.point;
			}
		}
	}

	return result;
}
