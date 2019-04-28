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
	Scence* scence;
	SCENCE scenceType;
public:
	World();
	~World();
	//Khởi tạo texture, object, map, player
	void LoadResource();
	void Update(float deltaTime);
	void Render();
	void ReplaceScence(SCENCE scenceType);
	void SetScence(Scence* s);
	static World* GetInstance() {
		if (_instance == NULL) _instance = new World();
		return _instance;
	}
};

