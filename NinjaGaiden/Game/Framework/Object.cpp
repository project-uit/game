#include "Object.h"
#include "../Logging/Debug.h"
#include "Camera.h"
#include "Game.h"
Object::Object()
{
	this->isActive = true;
}

Object::~Object()
{

}

CollisionHandler* Object::GetCollsionObjectsBySweptAABB(Object * obj)
{
	RECT statiRect = obj->GetBoundingBox();
	float sl = statiRect.left, st = statiRect.top, sr = statiRect.right, sb = statiRect.bottom;
	float ml = GetBoundingBox().left, mt = GetBoundingBox().top, mr = GetBoundingBox().right, mb = GetBoundingBox().bottom;
	float dx = this->deltaX - obj->GetVeclocity().x*this->deltaTime;
	float dy = this->deltaY - obj->GetVeclocity().y*this->deltaTime;
	
	float collisionTime, nx, ny;

	Game::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		collisionTime, nx, ny);
	
	return new CollisionHandler(collisionTime, nx, ny, obj);
}

void Object::CalcPotentialCollisions(vector<Object*>* objects, vector<CollisionHandler*>* coEvents)
{
	UINT k = 0;
	if (objectType == OBJECT_TYPE::MAIN_CHARACTER) {
		k++;
	}
	for (UINT i = k; i < objects->size(); i++) {
		CollisionHandler* coEvent = this->GetCollsionObjectsBySweptAABB(objects->at(i));
		if (coEvent->collisionTime >= 0 && coEvent->collisionTime < 1.0f)
			coEvents->push_back(coEvent);
		else
			delete coEvent;
	}

	sort(coEvents->begin(), coEvents->end(), CollisionHandler::Compare);
}

void Object::FilterCollision(
	vector<CollisionHandler*>* coEvents, 
	vector<CollisionHandler*>* coEventsResult, 
	float & minTx, float & minTy, 
	float & nx, float & ny)
{
	minTx = 1.0f;
	minTy = 1.0f;
	int minIx = -1;
	int minIy = -1;

	ny = 0.0f;
	nx = 0.0f;

	coEventsResult->clear();

	for (UINT i = 0; i < coEvents->size(); i++) {
		CollisionHandler* c = coEvents->at(i);

		if (c->collisionTime < minTx && c->nx != 0) {
			minTx = c->collisionTime;
			nx = c->nx;
			minIx = i;
		}

		if (c->collisionTime < minTy && c->ny != 0) {
			minTy = c->collisionTime;
			ny = c->ny;
			minIy = i;
		}
	}

	if (minIx >= 0) coEventsResult->push_back(coEvents->at(minIx));
	if (minIy >= 0) coEventsResult->push_back(coEvents->at(minIy));
}

RECT Object::GetBoundingBox()
{
	RECT rect;
	rect.left = (LONG)(this->position.x + this->positionColide.x);
	rect.top = (LONG)(this->position.y + this->positionColide.y);
	rect.right =  rect.left + (LONG)this->objectWidth;
	rect.bottom = rect.top + (LONG)this->objectHeight;
	return rect;
}

RECT Object::GetRECTSprite()
{
	RECT rect;
	rect.left = (LONG)(this->position.x);
	rect.top = (LONG)(this->position.y);
	rect.right = rect.left + (LONG)this->objectWidth;
	rect.bottom = rect.top + (LONG)this->objectHeight;
	return rect;
}

void Object::Update(float deltaTime, std::vector<Object*>* objects)
{
	this->deltaTime = deltaTime;
	this->deltaX = this->veclocity.x * deltaTime;
	this->deltaY = this->veclocity.y * deltaTime;
}

void Object::ResetState() {

}

void Object::Dead() {

}

D3DXVECTOR3 Object::GetTransformObjectPositionByCamera() {
	return Camera::GetInstance()->transformObjectPosition(position);
}

void Object::updateBoundingBox(RECT rect) {
	positionColide.x = rect.left;
	positionColide.y = rect.top;
	SetBoundingBox(rect.right - rect.left, rect.bottom - rect.top);
}

DIRECTION Object::GetObjectDirection() {
	if (veclocity.x < 0) {
		return DIRECTION::LEFT;
	}
	return DIRECTION::RIGHT;
}

void Object::SetActive(bool active) {
	isActive = active;
}

bool Object::GetActive() {
	return isActive;
}

int Object::GetScore() {
	return score;
}

void Object::SetPositionX(float x) {
	this->position.x += x;
}

void Object::SetPositionY(float y) {
	this->position.y += y;
}

void Object::SetObjectBoudingBox(int &width, int &height) {
	width = this->objectWidth;
	height = this->objectHeight;
}

OBJECT_TYPE Object::GetObjectType() { return this->objectType; }

void Object::SetObjectType(OBJECT_TYPE objectType) { this->objectType = objectType; }

void Object::SetBoundingBox(int width, int height) {
	this->objectWidth = width;
	this->objectHeight = height;
}

void Object::SetLastPos(float x, float y) { this->lastPos.x = x; this->lastPos.y = y; }
void Object::SetLastPos(D3DXVECTOR3 pos) { this->lastPos.x = pos.x; this->lastPos.y = pos.y; }
D3DXVECTOR3 Object::GetLastPos() { return this->lastPos; }

D3DXVECTOR3 Object::GetPosition() { return this->position; }
void Object::SetPosition(float x, float y) {
	this->position.x = x;
	this->position.y = y;
}
void Object::PlusPosition(float x, float y) {
	this->position.x += x;
	this->position.y += y;
}
D3DXVECTOR3 Object::GetVeclocity() { return this->veclocity; }
void Object::SetVeclocity(float vx, float vy) { this->veclocity.x = vx; this->veclocity.y = vy; }
void Object::SetVx(float vx) {
	this->veclocity.x = vx;
}
void Object::SetVy(float vy) {
	this->veclocity.y = vy;
}