#include "Square.h"


Square::Square(int left, int top, int right, int bottom)
{
	this->SetPosition(left, top);
	this->SetVeclocity(0, 0);
	this->SetBoundingBox(right - left, bottom - top);
	this->SetObjectType(BRICK);
}

Square::~Square()
{
}

void Square::Update(float deltaTime, vector<Object*>* object)
{
}

void Square::Render()
{

}

