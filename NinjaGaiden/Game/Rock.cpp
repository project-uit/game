#include "Rock.h"
#include "Player.h"
#include "Debug.h"

Rock::Rock(int left, int top, int right, int bottom, bool isCanClimbLeft, bool isCanClimbRight)
{
	this->SetPosition(left, top);
	this->SetVeclocity(0.0f, 0.0f);
	this->SetBoundingBox(right - left, bottom - top);
	this->isCanClimbLeft = isCanClimbLeft;
	this->isCanClimbRight = isCanClimbRight;
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
	HandleCollision(object);
}

void Rock::Render()
{

}

void Rock::HandleCollision(vector<Object*> *object) {
	vector<CollisionHandler*>* coEvents = new vector<CollisionHandler*>();
	vector<CollisionHandler*>* coEventsResult = new vector<CollisionHandler*>();
	coEvents->clear();
	Object::CalcPotentialCollisions(object, coEvents);
	if (coEvents->size() != 0) {
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			if (e->object->GetObjectType() == OBJECT_TYPE::MAIN_CHARACTER) {
				Player::GetInstance()->SetClimbRock(e->nx, e->ny, this);
			}
		}
	}

	for (UINT i = 0; i < coEvents->size(); i++) {
		delete coEvents->at(i);
	}

	delete coEvents;
	delete coEventsResult;
}

bool Rock::GetIsCanClimbLeft() {
	return isCanClimbLeft;
}

bool Rock::GetIsCanClimbRight() {
	return isCanClimbRight;
}