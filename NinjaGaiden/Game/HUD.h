#pragma once
#include "Sprite.h"
#include "Constants.h"
class HUD {
private:
	static HUD* _instance;
	Sprite* healthPlayer;
	Sprite*  healthBoss;
	Sprite*	box;
	Sprite* item;
	Sprite* lifePoint;
public:
	HUD();
	~HUD();
	static HUD* GetInstance() {
		if (_instance == NULL) {
			_instance = new HUD();
		}
		return _instance;
	}
	void Update(float t);
	void Render(int hpBoss = 16);
};