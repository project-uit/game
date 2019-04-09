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
#include "Scence.h"
#include "Scence1.h"
class World
{
private:
	static World * _instance;
	vector<Object*>* objects;
	Item* item;
	Scence* scence;
	Map* map;
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

