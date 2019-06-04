#pragma once
#include "../../Framework/Object.h"
#include "../../Framework/Constants.h"
class Brick : public Object
{
public:
	Brick(int left, int top, int right, int bottom);
	~Brick();
	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *object);
};

