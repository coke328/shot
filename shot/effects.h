#pragma once
#include "raylib.h"
#include "cam.h"
#include "sprite.h"
#include <string>
#include <thread>
#include <time.h>

class effects
{
private:
	
	float time;
	bool performing;
	int state;
	float lastTime;

public:
	sprite sp;
	

	~effects();
	effects();
	effects(Vector2 globalPos, float width, float height, int maxTId, int Tid, float r, Vector2 origin, std::string file, int term);
	void init(Vector2 globalPos, float width, float height,int maxTId,int Tid,float r,Vector2 origin,std::string file,int term);
	void startEffect(Vector2 gPos, float r);
	virtual void updateEffect();
	void setState(bool state);
	void setGlobalPos(Vector2 gPos);
	void setRotation(float r);
	bool getState();
};

class effectsCtrl {
public:
	effects* effectsPool;
	int maxPool;


	~effectsCtrl();
	void init(Vector2 globalPos, float width, float height, int maxId, int id, float r, Vector2 origin, std::string file, int term, int maxPool);
	void startEffect(Vector2 gPos, float r);
	void updateEffects();
};