#pragma once
#include "../Framework/Sprite.h"
#include "../Framework/Constants.h"
class HUD {
private:
	static HUD* _instance;
	Sprite* healthPlayer;
	Sprite*  healthBoss;
	Sprite*	box;
	Sprite* item;
	Sprite* lifePoint;
	Sprite* skill;
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
	void SetSkill(Sprite* skill);
};