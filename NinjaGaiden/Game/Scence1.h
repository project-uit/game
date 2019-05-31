#pragma once
#include "Scence.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Object.h"
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"
#include "Grid.h"
#include "Player.h"
#include "Constants.h"
#include "Map.h"
#include "Square.h"
class Scence1 : public Scence {
private:
	float waitingTime;
public:
	Scence1();
	~Scence1();
	void LoadResource();
	void Update(float deltaTime);
	void Render();
};
