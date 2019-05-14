#pragma once
#include "Object.h"
#include "Sprite.h"
#include <map>
class Food :public Object {
private:
	map<FOOD_STATE, Sprite*>* sprite;
	FOOD_STATE state;
	bool isOnGround;
public:
	Food(SCENCE scene, int type, int posX, int posY);
	~Food();
	void Update(float t, vector<Object*>* objects);
	void Render();
	void HandleCollision(vector<Object*> *object);

	bool GetIsOnGround();
	void SetIsOnGround(bool flag);
};