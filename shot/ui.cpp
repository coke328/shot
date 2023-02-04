#include "ui.h"

std::vector<ui*> uiCtrl::Uis;

void uiCtrlInsertion_sort() {
	int i, j;
	ui* key;
	for (i = 1; i < uiCtrl::Uis.size(); i++) {
		key = uiCtrl::Uis[i];
		for (j = i - 1; j >= 0 && uiCtrl::Uis[j]->getDepth() > key->getDepth(); j--) {
			uiCtrl::Uis[j + 1] = uiCtrl::Uis[j];
		}
		uiCtrl::Uis[j + 1] = key;
	}
}

ui::ui() {

}

ui::ui(Rectangle dRec, int maxId, int id, Vector2 origin, std::string file, int depth, bool visible)
{
	destRec.x = GetScreenWidth() / 2 + dRec.x;
	destRec.y = GetScreenHeight() / 2 + dRec.y;
	destRec.width = dRec.width;
	destRec.height = dRec.height;
	maxTextureId = maxId;
	textureId = id;
	Origin = origin;
	texture = LoadTexture(file.c_str());
	Depth = depth;
	Visible = visible;

	int h = texture.height;
	int w = texture.width / (maxId + 1);
	sourceRec.x = w * id;
	sourceRec.y = 0;
	sourceRec.width = w;
	sourceRec.height = h;
}

void ui::init(Rectangle dRec, int maxId, int id, Vector2 origin, std::string file, int depth, bool visible)
{
	destRec.x = GetScreenWidth() / 2 + dRec.x;
	destRec.y = GetScreenHeight() / 2 + dRec.y;
	destRec.width = dRec.width;
	destRec.height = dRec.height;
	maxTextureId = maxId;
	textureId = id;
	Origin = origin;
	texture = LoadTexture(file.c_str());
	Depth = depth;
	Visible = visible;

	int h = texture.height;
	int w = texture.width / (maxId + 1);
	sourceRec.x = w * id;
	sourceRec.y = 0;
	sourceRec.width = w;
	sourceRec.height = h;

	uiCtrl::push(this);
}

void ui::setVisible(bool v)
{
	Visible = v;
}

void ui::setTextureId(int id)
{
	textureId = id;
	int h = texture.height;
	int w = texture.width / (maxTextureId + 1);
	sourceRec.x = w * id;
	sourceRec.y = 0;
	sourceRec.width = w;
	sourceRec.height = h;
}

void ui::setPos(Vector2 p)
{
	destRec.x = GetScreenWidth() / 2 + p.x;
	destRec.y = GetScreenHeight() / 2 + p.y;
	//std::cout << destRec.x << std::endl;
}

void ui::setRotation(float angle) 
{
	rot = angle;
}

void ui::setGlobalPos(Vector2 gPos) {
	destRec.x = cam::getscreenPos(gPos).x;
	destRec.y = cam::getscreenPos(gPos).y;
}

int ui::getDepth()
{
	return Depth;
}

void ui::drawUi()
{
	if (Visible) {
		DrawTexturePro(texture, sourceRec, destRec, Origin, rot, WHITE);
	}
}

void ui::unloadTexture()
{
	UnloadTexture(texture);
}

void uiCtrl::drawUi()
{
	for (int i = 0; i < Uis.size(); i++) {
		Uis[i]->drawUi();
	}
}

void uiCtrl::unloadTexture()
{
	for (int i = 0; i < Uis.size(); i++) {
		Uis[i]->unloadTexture();
	}
}

void uiCtrl::push(ui* u) 
{
	uiCtrl::Uis.push_back(u);
	uiCtrlInsertion_sort();
}
