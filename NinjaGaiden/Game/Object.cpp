#include "Object.h"
#include "Debug.h"
#include "Camera.h"
#include "Game.h"
#include "Debug.h"
Object::Object()
{
	this->isActive = true;
	//this->nextObj = NULL;
	//this->preObj = NULL;
}

Object::~Object()
{

}

void Object::SweptAABB(Object * obj, float dx, float dy, float &collisionTime, float & nx, float &ny)
{
	float dxEntry, dxExit, txEntry, txExit;
	float dyEntry, dyExit, tyEntry, tyExit;

	float entryTime;
	float exitTime;
	
	RECT movingRect = this->GetBoundingBox();
	float movingTop = (float)movingRect.top;
	float movingBottom = (float)movingRect.bottom;
	float movingLeft = (float)movingRect.left;
	float movingRight = (float)movingRect.right;

	RECT staticRect = obj->GetBoundingBox();
	float staticTop =(float) staticRect.top;
	float staticBottom = (float)staticRect.bottom;
	float staticLeft = (float)staticRect.left;
	float staticRight = (float)staticRect.right;

	collisionTime = -1.0f;
	nx = ny = 0;
	//Vẽ broadphase
	float bl = dx > 0 ? movingLeft : movingLeft + dx;
	float bt = dy > 0 ? movingTop : movingTop + dy;
	float br = dx > 0 ? movingRight + dx : movingRight - dx;
	float bb = dy > 0 ? movingBottom + dy : movingBottom - dy;
	//Check AABB
	if (br < staticLeft || bl >  staticRight
		|| bb < staticTop || bt > staticBottom)
		
		return;

	if (dx == 0 && dy == 0) {
		return;
	}

	// đi qua phải
	if (dx > 0) {
		dxEntry = staticLeft - movingRight;
		dxExit = staticRight - movingLeft;
	}
	else if (dx < 0) {
		dxEntry = staticRight - movingLeft;
		dxExit = staticLeft - movingRight;
	}

	// đi xuống
	if (dy > 0) {
		dyEntry = staticTop - movingBottom;
		dyExit = staticBottom - movingTop;
	}
	else if (dy < 0) {
		dyEntry = staticBottom - movingTop;
		dyExit = staticTop - movingBottom;
	}

	if (dx == 0) {
		txEntry = -99999999999;
		txExit = 99999999999;
	}
	else {
		txEntry = dxEntry / dx;
		txExit = dxExit / dx;
	}

	if (dy == 0) {
		tyEntry = -99999999999;
		tyExit = 99999999999;
	}
	else {
		tyEntry = dyEntry / dy;
		tyExit = dyExit / dy;
	}

	if ((txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f) return;

	entryTime = max(txEntry, tyEntry);
	exitTime = min(txExit, tyExit);

	if (entryTime > exitTime) return;
	collisionTime = entryTime;
	
	if (txEntry > tyEntry) {
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else {
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
		
	}
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
	for (UINT i = 0; i < objects->size(); i++) {
		CollisionHandler* coEvent = this->GetCollsionObjectsBySweptAABB(objects->at(i));
		//float remainingTime = 1.0f - coEvent->collisionTime;
		if (coEvent->collisionTime < 1.0f)
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