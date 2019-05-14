#pragma once
#include "Object.h"
#include "Constants.h"
class Ladder : public Object
{
private:
	
public:
	Ladder(int left, int top, int right, int bottom);
	~Ladder();
	void Update(float deltaTime, vector<Object*> *object = NULL);
	void Render();
	void HandleCollision(vector<Object*> *object);
};

