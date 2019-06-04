#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Object.h"
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"
#include "../Object/Player/Player.h"
#include "Camera.h"
#include "Scence.h"
class World
{
private:
	static World * _instance;
	Scence* scence;
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

