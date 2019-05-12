#pragma once
#include "Sprite.h"
#include "Constants.h"
class HUD {
private:
	Sprite* healthPlayer;
	Sprite*  healthBoss;
	Sprite*	box;
	Sprite* item;
	Sprite* lifePoint;
public:
	HUD();
	~HUD();
	void Update(float t);
	void Render();
};