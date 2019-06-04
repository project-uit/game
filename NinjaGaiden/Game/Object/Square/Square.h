#pragma once
#include "../../Framework/Object.h"
#include "../../Framework/Constants.h"
class Square : public Object
{
public:
	Square(int left, int top, int right, int bottom);
	~Square();
	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *object);
};

