#include "CircleFire.h"
#include "Camera.h"

CircleFire::CircleFire() {
	this->SetObjectType(CIRCLE_FIRE);
	objectWidth = objectHeight = 1;
	this->position.z = 0.0f;
	this->isActive = false;
	SetVx(0.0f);
	SetVy(0.0f);
	this->SetPosition(0, 0);
	sprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY_DIE_FIRE), PATH_POS_CircleFire, 3, 0.035f);
}

CircleFire::~CircleFire() {
	delete sprite;
}

void CircleFire::Update(float t,int index, vector<Object*> *object) {
	veclocity.y -= 2 * index;
	Update(t, object);
}

void CircleFire::Update(float t, vector<Object*>* object) {
	RECT rectCam = Camera::GetInstance()->GetRECTx();
	if (position.x < rectCam.left || position.x > rectCam.right) {
		isActive = false;
	}
	if (isActive) {
		Object::Update(t);
		RECT rect = sprite->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);
		sprite->NextSprite(t);
		Object::PlusPosition(this->deltaX, this->deltaY);
	}
	else {
		SetPosition(0.0f, 0.0f);
	}
}

void CircleFire::HandleCollision(vector<Object*>* object) {
	vector<CollisionHandler*>* coEvents = new vector<CollisionHandler*>();
	vector<CollisionHandler*>* coEventsResult = new vector<CollisionHandler*>();
	coEvents->clear();
	if (isActive) {
		Object::CalcPotentialCollisions(object, coEvents);
	}
	if (coEvents->size() == 0) {
		Object::PlusPosition(this->deltaX, this->deltaY);
	}
	else {
		float min_tx, min_ty, nx = 0, ny;
		this->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			/*if (e->object->GetObjectType() == OBJECT_TYPE::MAIN_CHARACTER) {
				if (e->nx != 0 || e->ny != 0) {
					isActive = false;
					SetVx(0.0f);
					SetVy(0.0f);
				}
				continue;
			}*/
			Object::PlusPosition(this->deltaX, this->deltaY);
		}
	}
}

void CircleFire::ResetState() {

}

void CircleFire::Render() {
	if (isActive) {
		sprite->DrawSprite(Object::GetTransformObjectPositionByCamera(), false);
	}
}