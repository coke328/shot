#include "sprite.h"
std::vector<sprite*> sprite::sprites;
int sprite::cnt;

sprite::sprite()
{
	Pos = { 0,0 };
	depth = 0;
	Width = 0;
	Height = 0;
	depth = 0;
	Rotation = 0;
	maxTextureId = 0;
	textureId = 0;
	Origin = { 0,0 };
	sourceRec = { 0, 0, 0, 0 };
	Yfliped = false;
	isSprites = false;
}

sprite::sprite(Vector2 pos, float width, float height, float rotation, int maxId, int Id, Vector2 origin, std::string file, float d, bool visible)
{
	globalPos = pos;
	Pos = { globalPos.x - cam::camPos.x,globalPos.y - cam::camPos.y };
	Width = width;
	Height = height;
	depth = d;
	Rotation = rotation;
	maxTextureId = maxId;
	textureId = Id;
	Origin = origin;
	texture = LoadTexture(file.c_str());
	int w = texture.width / (maxTextureId + 1);
	int h = texture.height;
	sourceRec = { (float)w * textureId, 0, (float)w, (float)h };
	Visible = visible;
	Yfliped = false;
	isSprites = false;
}

void sprite::init(Vector2 pos, float width, float height, float rotation, int maxId, int Id, Vector2 origin, std::string file , float d, bool visible)
{
	globalPos = pos;
	Pos = { globalPos.x - cam::camPos.x,globalPos.y - cam::camPos.y };
	Width = width;
	Height = height;
	depth = d;
	Rotation = rotation;
	maxTextureId = maxId;
	textureId = Id;
	Origin = origin;
	texture = LoadTexture(file.c_str());
	int w = texture.width / (maxTextureId + 1);
	int h = texture.height;
	sourceRec = { (float)w * textureId, 0, (float)w, (float)h };
	Visible = visible;
	Yfliped = false;
	isSprites = false;
}

void sprite::changeTexture(int Id) // 0~
{
	textureId = Id;
	int w = texture.width / (maxTextureId + 1);
	int h = texture.height;
	if (Yfliped) {
		sourceRec = { (float)w * textureId, (float)h, (float)w, -(float)h };
	}
	else {
		sourceRec = { (float)w * textureId, 0, (float)w, (float)h };
	}
}

void sprite::unloadTexture()
{
	UnloadTexture(texture);
}


void sprite::setPos(float Px, float Py)
{
	Pos.x = Px;
	Pos.y = Py;
}

void sprite::setOrigin(float x, float y)
{
	Origin = { x,y };
}

void sprite::setRotation(float radian)
{
	Rotation = radian * 180 / PI;
}

void sprite::spritesToVector()
{
	setspId(sprite::sprites.size());
	sprite::sprites.push_back(this);
	setIsSprites(true);
}

void sprite::spriteRemoveFromVector()
{
	//std::cout << "spriteR:" << Id << std::endl;
	if (isSprites) {
		sprite::sprites.erase(sprite::sprites.begin() + Id);
		setIsSprites(false);
		for (int i = Id; i < sprite::sprites.size(); i++) {
			sprite::sprites[i]->setspId(i);
		}
	}
}

void sprite::flipY()
{
	int w = texture.width / (maxTextureId + 1);
	int h = texture.height;
	if (Yfliped) {
		sourceRec = { (float)w * textureId, 0, (float)w, (float)h };
		Yfliped = false;
	}else{
		sourceRec = { (float)w * textureId, (float)h, (float)w, -(float)h };
		Yfliped = true;
	}
}

void sprite::setVisibla(bool visible)
{
	Visible = visible;
}

void sprite::setspId(int id)
{
	Id = id;
	//std::cout << "change" << std::endl;
}

void sprite::setIsSprites(bool in)
{
	isSprites = in;
}

void sprite::drawTexture()
{
	if (Visible) {
		DrawTexturePro(texture, sourceRec, { Pos.x,Pos.y,Width,Height }, Origin, Rotation, WHITE);
	}
}

void sprite::setglobalPos(Vector2 gPos) {
	globalPos = gPos;
}

void sprite::update()
{
	Pos = cam::getscreenPos(globalPos);
}


