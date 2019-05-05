#pragma once
#include "Object.h"
#include "Sprite.h"
#include <map>
class Panther : Object{
private:
	RECT movingArea;
	map<ENEMY_STATE, Sprite*>* sprite;
	ENEMY_STATE state;
	DIRECTION direction;
public:
	Panther();
	~Panther();
	void Update(float t, vector<Object*>* objects);
	void Render();
	void HandleCollision(vector<Object*> *object);
};