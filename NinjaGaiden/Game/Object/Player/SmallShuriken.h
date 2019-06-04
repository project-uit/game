#pragma once
#include "Weapon.h"
class SmallShuriken : public Weapon {
public:
	SmallShuriken();
	~SmallShuriken();
	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *object);

};