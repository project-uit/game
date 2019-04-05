#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Object.h"
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"
#include "player.h"
#include "Camera.h"
#include "Item.h"
class World
{
private:
	static World * _instance;
	Sprite* testSpriteStand;
	vector<Object*>* objects;
	Item* item;

public:
	World();
	~World();

	void LoadResource();
	void Update(float deltaTime);
	void Render();

	static World* GetInstance() {
		if (_instance == NULL) _instance = new World();
		return _instance;
	}
};

