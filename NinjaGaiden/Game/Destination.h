#pragma once
#include "Object.h"
class Destination : public Object {
public:
	Destination(int left, int top, int right, int bottom);
	~Destination();
	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *object);
};