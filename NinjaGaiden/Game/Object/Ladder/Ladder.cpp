#include "Ladder.h"
#include "../../Logging/Debug.h"

Ladder::Ladder(int left, int top, int right, int bottom)
{
	this->SetPosition(left, top);
	this->SetVeclocity(0.0f, 0.0f);
	this->SetBoundingBox(right - left, bottom - top);
	this->SetObjectType(OBJECT_TYPE::LADDER);
	this->positionColide = D3DXVECTOR2(0.0f, 0.0f);
	this->position.z = 0.0f;
	this->SetLastPos(GetPosition());
}

Ladder::~Ladder()
{

}

void Ladder::Update(float deltaTime, vector<Object*>* object)
{
	Object::Update(deltaTime);
	Object::GetTransformObjectPositionByCamera();
}

void Ladder::Render()
{

}

void Ladder::HandleCollision(vector<Object*> *object) {

}
