#pragma once
#include "Object.h"
#include "Sprite.h"
#include <map>
class Boom : public Object {
private:
	map<ENEMY_STATE, Sprite*>* sprite;
	ENEMY_STATE state;
	bool isFly;
public:
	Boom();
	~Boom();
	void Update(float t, vector<Object*>* objects);
	void Render();
	void HandleCollision(vector<Object*> *object);
	void ResetState();
	bool IsOutCamera();
	bool IsFly();
	void SetFly(bool fly);
};