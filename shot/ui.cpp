#include "ui.h"

ui::ui(Rectangle dRec, int maxId, int id, Vector2 origin, std::string file, int depth, bool visible)
{
	destRec = dRec;
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
