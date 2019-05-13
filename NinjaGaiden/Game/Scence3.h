#pragma once
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"
#include "Grid.h"
#include "Player.h"
#include "Constants.h"
#include "Map.h"
#include "Square.h"
#include "Scence.h"
#include "Boss.h"
class Scence3 : public Scence {
private:
	Boss* boss;
public:
	Scence3();
	~Scence3();
	void LoadResource();
	void Update(float deltaTime);
	void Render();
};