#pragma once
#include "Object.h"
#include "Sprite.h"
#include <map>
#include "Boom.h"
class Boss : public Object {
private:
	ENEMY_STATE state;
	map<ENEMY_STATE, Sprite*>* sprite;
	DIRECTION direction;
	Boom boom[3];
	int hp;
	bool isOnGround;
	bool throwBoom;
	float time;
	int count;
	float timeHurt;
	float deltaXAxis;
	int left;
	int right;
public:
	Boss();
	~Boss();
	void Update(float t, vector<Object*>* objects);
	void Render();
	void HandleCollision(vector<Object*> *object);
	void ResetState();
	int GetHp();
};