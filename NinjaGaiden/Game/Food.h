#pragma once
#include "Object.h"
#include "Sprite.h"
#include <map>

#define TIME_DISAPPEAR 5
class Food :public Object {
private:
	D3DXVECTOR3 initialPosition;
	map<FOOD_STATE, Sprite*>* sprite;
	FOOD_STATE state;
	FOOD_TYPE type;
	bool isOnGround;
	int score;
	float timer;
public:
	Food(SCENCE scene, int type, int posX, int posY);
	~Food();
	void Update(float t, vector<Object*>* objects);
	void Render();
	void HandleCollision(vector<Object*> *object);
	void Reset();
	void ResetState();
	FOOD_TYPE GetType();
	bool GetIsOnGround();
	void SetIsOnGround(bool flag);
	int GetScore();
	FOOD_STATE GetState();
};