#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Object.h"
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"
#include "Grid.h"
#include "Player.h"
#include "Constants.h"
#include "Grid.h"
#include "Map.h"
#include "Square.h"
class Scence {
protected:
	vector<Square*> *bricks;
	Map* map;
	string name;
	int score;
	int timer;
public:
	Scence();
	~Scence();
	virtual void LoadResource() = 0;
	virtual void Update(float deltaTime);
	virtual void Render();
};