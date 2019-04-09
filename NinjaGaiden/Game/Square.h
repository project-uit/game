#pragma once
#include "Object.h"
#include "Constants.h"
class Square : public Object
{
public:
	Square(int left, int top, int right, int bottom);
	~Square();

	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
};
