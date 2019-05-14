#pragma once
#include "Object.h"
#include "Constants.h"
class Rock : public Object
{
private:
	bool isCanClimbLeft;
	bool isCanClimbRight;
public:
	Rock(int left, int top, int right, int bottom);
	~Rock();
	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *object);
	bool GetIsCanClimbLeft();
	bool GetIsCanClimbRight();
};

