#pragma once
#include "Object.h"
#include "Sprite.h"
#include <map>
class SoldierSword :public Object {
private:
	int leftMoving;
	int rightMoving;
	vector<int> movingLimit;
	vector<int> activeArea;
	map<ENEMY_STATE, Sprite*>* sprite;
	ENEMY_STATE state;
	DIRECTION direction;
	float time;
	float resetTime;
	void init();
public:
	SoldierSword();
	SoldierSword(vector<int> movingLimit, vector<int> activeArea, int positionX, int positionY);
	~SoldierSword();
	void Update(float t, vector<Object*>* objects);
	void Render();
	void HandleCollision(vector<Object*> *object);
	void ResetState();
	void UpdateActiveArea(float t);
	void SetState(ENEMY_STATE state);
};