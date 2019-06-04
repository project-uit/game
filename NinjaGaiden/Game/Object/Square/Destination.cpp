#include "Destination.h"
Destination::Destination(int left, int top, int right, int bottom)
{
	this->SetPosition(left, top);
	this->SetVeclocity(0.0f, 0.0f);
	this->SetBoundingBox(right - left, bottom - top);
	this->SetObjectType(OBJECT_TYPE::DESTINATION);
	this->positionColide = D3DXVECTOR2(0.0f, 0.0f);
	this->position.z = 0.0f;
	this->SetLastPos(GetPosition());
	isActive = true;
}

Destination::~Destination()
{

}

void Destination::Update(float deltaTime, vector<Object*>* object)
{
	Object::Update(deltaTime);
	Object::GetTransformObjectPositionByCamera();
}

void Destination::Render()
{

}

void Destination::HandleCollision(vector<Object*> *object) {

}