#include "boundarys.h"

std::vector<boundary> boundarys::staticbounds;

boundarys::boundarys()
{
	boundcnt = 0;
}

void boundarys::init(int cnt) {
	boundcnt = cnt;
	for (int i = 0; i < bounds.size(); i++) {
		int size = staticbounds.size() * 2;
		bounds[i].bsaves = new float[size];
		for (int j = 0; j < size; j++) {
			bounds[i].bsaves[j] = 0;
		}
	}
}

void boundarys::staticboundarysInit(int w, int h, float scale)
{
	staticbounds.emplace_back(0, 0, w * 32 * scale, h * -16 * scale, true);
	staticbounds.emplace_back(w * 32 * scale, h * -16 * scale, w * 64 * scale, 0, true);
	staticbounds.emplace_back(0, 0, w * 32 * scale, h * 16 * scale, true);
	staticbounds.emplace_back(w * 32 * scale, h * 16 * scale, w * 64 * scale, 0, true);

}

void boundarys::collid(Vector2 &globalPos, Vector2 &vel)
{
	for (int i = 0; i < bounds.size(); i++) {
		for (int j = 0; j < staticbounds.size(); j++) {
			boundary stb = staticbounds[j];
			vecbool tmp = bounds[i].isCollid(stb,j);
			if (tmp.iscollid){
				
				Vector2 p = tmp.point;
				//if (tmpvec.x != p.x && tmpvec.y != p.y) {

				globalPos.x = (stb.b * (stb.b * p.x - stb.a * p.y) - stb.a * stb.c) / (stb.a * stb.a + stb.b * stb.b)-p.x + globalPos.x;
				globalPos.y = (stb.a * (stb.a * p.y - stb.b * p.x) - stb.b * stb.c) / (stb.a * stb.a + stb.b * stb.b)-p.y + globalPos.y;
				//std::cout << globalPos.x << "," << globalPos.y << std::endl;
				bounds[0].boundaryInit(globalPos.x - 5 * 4, globalPos.y + 9.5 * 4, globalPos.x + 5 * 4, globalPos.y + 9.5 * 4, false);
				bounds[1].boundaryInit(globalPos.x + 5 * 4, globalPos.y + 9.5 * 4, globalPos.x + 5 * 4, globalPos.y + 13.5 * 4, false);
				bounds[2].boundaryInit(globalPos.x - 5 * 4, globalPos.y + 13.5 * 4, globalPos.x + 5 * 4, globalPos.y + 13.5 * 4, false);
				bounds[3].boundaryInit(globalPos.x - 5 * 4, globalPos.y + 9.5 * 4, globalPos.x - 5 * 4, globalPos.y + 13.5 * 4, false);
					
				//}
			}
		}
	}
}

void boundarys::setboundaryPos(Vector2* points)
{

}
