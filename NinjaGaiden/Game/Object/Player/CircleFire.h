#pragma once
#include "Weapon.h"
class CircleFire : public Weapon {
public:
	CircleFire();
	~CircleFire();
	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Update(float deltaTime, int index, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *object);
	void ResetState();
};