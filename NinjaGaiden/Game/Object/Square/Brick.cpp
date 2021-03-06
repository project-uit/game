#include "Brick.h"

Brick::Brick(int left, int top, int right, int bottom)
{
	this->SetPosition(left, top);
	this->SetVeclocity(0.0f, 0.0f);
	this->SetBoundingBox(right - left, bottom - top);
	this->SetObjectType(OBJECT_TYPE::BRICK);
	this->positionColide = D3DXVECTOR2(0.0f, 0.0f);
	this->position.z = 0.0f;
	this->SetLastPos(GetPosition());
	isActive = true;
}

Brick::~Brick()
{

}

void Brick::Update(float deltaTime, vector<Object*>* object)
{
	Object::Update(deltaTime);
	Object::GetTransformObjectPositionByCamera();
}

void Brick::Render()
{

}

void Brick::HandleCollision(vector<Object*> *object) {

}
