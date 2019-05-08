#pragma once
#include "Object.h"
#include "Sprite.h"
#include <map>
class SoldierSword :public Object {
private:
	RECT movingArea;
	vector<RECT> movingBox;
	map<ENEMY_STATE, Sprite*>* sprite;
	ENEMY_STATE state;
	DIRECTION direction;
	float time;
	void init();
public:
	SoldierSword();
	SoldierSword(RECT movingArea, RECT movingBox, int positionX, int positionY, DIRECTION direction);
	~SoldierSword();
	void Update(float t, vector<Object*>* objects);
	void Render();
	void HandleCollision(vector<Object*> *object);
	void ResetState();
	RECT GetMovingArea();
};