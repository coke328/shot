#include "effects.h"

void start(int cnt, float time, effects* e) {
	
	e->sp.setVisibla(false);
	e->setState(false);
}

effects::~effects()
{
	sp.unloadTexture();
	sp.spriteRemoveFromVector();
}

effects::effects()
{
}

effects::effects(Vector2 globalPos, float width, float height, int maxId, int id, float r, Vector2 origin, std::string file, int term)
{
	sp.init(globalPos, width, height, r, maxId, id, origin, file, globalPos.y, false);
	time = term;
	state = 0;
	setState(false);
}

void effects::init(Vector2 globalPos, float width, float height, int maxId, int id, float r,Vector2 origin, std::string file, int term)
{
	sp.init(globalPos, width, height, r, maxId, id, origin, file, globalPos.y, false);
	time = term;
	state = 0;
	setState(false);
}

void effects::startEffect(Vector2 gPos, float r)
{
	setGlobalPos(gPos);
	setRotation(r);
	sp.depth = gPos.y;
	setState(true);
	sp.setVisibla(true);
	lastTime = clock();
}

void effects::updateEffect()
{
	
	if (lastTime + time <= clock()) {
		state++;
		std::cout << state << std::endl;
		if (state >= sp.maxTextureId + 1) {
			setState(false);
			sp.setVisibla(false);
			state = 0;
		}
		else {
			sp.changeTexture(state);
			lastTime = clock();
		}
	}
}

void effects::setState(bool state)
{
	performing = state;
}

void effects::setGlobalPos(Vector2 gPos)
{
	sp.setglobalPos(gPos);
}

void effects::setRotation(float r)
{
	sp.setRotation(r);
}

bool effects::getState()
{
	return performing;
}

effectsCtrl::~effectsCtrl()
{
	
	delete[] effectsPool;
}

void effectsCtrl::init(Vector2 globalPos, float width, float height, int maxId, int id, float r, Vector2 origin, std::string file, int term, int mPool)
{
	maxPool = mPool;
	effectsPool = new effects[maxPool];
	effectsPool[0].init(globalPos, width, height, maxId, id, r, origin, file, term);
	effectsPool[0].sp.spritesToVector();
	for (int i = 1; i < maxPool; i++) {
		effectsPool[i] = effectsPool[0];
		//std::cout <<  << std::endl;
		effectsPool[i].sp.spritesToVector();
	}
}

void effectsCtrl::startEffect(Vector2 gPos,float r)
{
	for (int i = 0; i < maxPool; i++) {
		if (!effectsPool[i].getState()) {

			effectsPool[i].startEffect(gPos,r);
			
			break;
		}
	}
}

void effectsCtrl::updateEffects()
{
	for (int i = 0; i < maxPool; i++) {
		if (effectsPool[i].getState()) {

			effectsPool[i].updateEffect();
		}
	}
}
