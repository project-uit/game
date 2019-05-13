#include "Square.h"
#include "Debug.h"

Square::Square(int left, int top, int right, int bottom)
{
	this->SetPosition(left, top);
	this->SetVeclocity(0.0f, 0.0f);
	this->SetBoundingBox(right - left, bottom - top);
	this->SetObjectType(OBJECT_TYPE::SQUARE);
	this->positionColide = D3DXVECTOR2(0.0f, 0.0f);
	this->position.z = 0.0f;
	this->SetLastPos(GetPosition());
	isActive = true;
}

Square::~Square()
{
	
}

void Square::Update(float deltaTime, vector<Object*>* object)
{
	Object::Update(deltaTime);
	Object::GetTransformObjectPositionByCamera();
}

void Square::Render()
{

}

void Square::HandleCollision(vector<Object*> *object) {

}
