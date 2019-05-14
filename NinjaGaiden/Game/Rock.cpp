#include "Rock.h"
#include "Debug.h"

Rock::Rock(int left, int top, int right, int bottom)
{
	this->SetPosition(left, top);
	this->SetVeclocity(0.0f, 0.0f);
	this->SetBoundingBox(right - left, bottom - top);
	this->SetObjectType(OBJECT_TYPE::ROCK);
	this->positionColide = D3DXVECTOR2(0.0f, 0.0f);
	this->position.z = 0.0f;
	this->SetLastPos(GetPosition());
}

Rock::~Rock()
{

}

void Rock::Update(float deltaTime, vector<Object*>* object)
{
	Object::Update(deltaTime);
	Object::GetTransformObjectPositionByCamera();
}

void Rock::Render()
{

}

void Rock::HandleCollision(vector<Object*> *object) {

}

bool Rock::GetIsCanClimbLeft() {
	return isCanClimbLeft;
}

bool Rock::GetIsCanClimbRight() {
	return isCanClimbRight;
}