#pragma once
#include "Object.h"
#include "Sprite.h"
#include <map>
class SoldierSword :public Object {
private:
	RECT movingArea;
	map<ENEMY_STATE, Sprite*>* sprite;
	ENEMY_STATE state;
	DIRECTION direction;
public:
	SoldierSword();
	~SoldierSword();
	void Update(float t, vector<Object*>* objects);
	void Render();
	void HandleCollision(vector<Object*> *object);
};