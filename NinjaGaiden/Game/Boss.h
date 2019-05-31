#pragma once
#include "Object.h"
#include "Sprite.h"
#include <map>
#include "Boom.h"
#define BOOM_NUMBERS 3
class Boss : public Object {
private:
	ENEMY_STATE state;
	map<ENEMY_STATE, Sprite*>* sprite;
	vector<Sprite*>* explosion;
	DIRECTION direction;
	Boom boom[BOOM_NUMBERS];
	int hp;
	bool isOnGround;
	bool throwBoom;
	float time;
	int count;
	float timeHurt;
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