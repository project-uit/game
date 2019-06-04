#pragma once
#include "../Framework/Texture.h"
#include "../Framework/Sprite.h"
#include "../Framework/Game.h"
#include "../Framework/Grid.h"
#include "../Object/Player/Player.h"
#include "../Framework/Constants.h"
#include "../Framework/Map.h"
#include "../Object/Square/Square.h"
#include "../Framework/Scence.h"
#include "../Object/Boss/Boss.h"
class Scence3 : public Scence {
private:
	Boss* boss;
	float remainTime;
public:
	Scence3();
	~Scence3();
	void LoadResource();
	void Update(float deltaTime);
	void Render();
};