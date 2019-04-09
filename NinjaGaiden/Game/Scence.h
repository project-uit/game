﻿#pragma once
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
class Scence {
protected:
	vector<Object*> *objects;
	vector<RECT> *bricks;
public:
	Scence();
	~Scence();

	void InitHorizontalBrick(RECT rect);

	// Dùng để cắt theo hàng dọc
	void InitVerticalBrick(RECT rect);

	virtual void LoadResource() = 0;
	virtual void Update(float deltaTime);
	virtual void Render();
};