#pragma once
#include "Object.h"
#include "Sprite.h"
#include <map>
class Boom : public Object {
private:
	map<ENEMY_STATE, Sprite*>* sprite;
	ENEMY_STATE state;
	float time;
public:
	Boom();
	~Boom();
	void Update(float t, vector<Object*>* objects);
	void Update(float t, float runTime, vector<Object*>* objects);
	void Render();
	void HandleCollision(vector<Object*> *object);
	void ResetState();
	bool IsOutCamera();
	void Dead();
	ENEMY_STATE GetState();
};