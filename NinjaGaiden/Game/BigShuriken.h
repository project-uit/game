#pragma once
#include "Weapon.h"
class BigShuriken : public Weapon {
private:
	bool orbitMoving;
	float left, right;
public:
	BigShuriken();
	~BigShuriken();
	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *object);
	void Orbit(float t);
	void SetOrbitMoving(bool orbitMoving);
};