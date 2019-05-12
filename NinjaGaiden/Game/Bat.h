#pragma once
#include "Object.h"
class Bat {
private:

public:
	Bat();
	~Bat();
	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *object);
};
