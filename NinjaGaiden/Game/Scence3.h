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
class Scence3 : public Scence {
public:
	Scence3();
	~Scence3();
	void LoadResource();
	void Update(float deltaTime);
	void Render();
};