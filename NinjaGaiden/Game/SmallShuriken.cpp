#include "SmallShuriken.h"
#include "Camera.h"
#include "SoldierSword.h"
#include "Panther.h"

SmallShuriken::SmallShuriken() {
	this->SetObjectType(SMALL_SHURIKEN);
	objectWidth = objectHeight = 1;
	this->position.z = 0.0f;
	this->isActive = false;
	SetVx(0.0f);
	SetVy(0.0f);
	this->SetPosition(0, 0);
	sprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_SmallShuriken, 1, 0.0f);
}

SmallShuriken::~SmallShuriken() {
	delete sprite;
}

void SmallShuriken::Update(float t, vector<Object*> *object) {
	RECT rectCam = Camera::GetInstance()->GetRECTx();
	if (position.x < rectCam.left || position.x > rectCam.right) {
		isActive = false;
	}
	if (isActive) {
		Object::Update(t);
		//this->veclocity.y += GRAVITY;
		RECT rect = sprite->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);
		sprite->NextSprite(t);
	}
	HandleCollision(object);
}

void SmallShuriken::HandleCollision(vector<Object*> *object) {
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
		this->PlusPosition(min_tx * this->deltaX + nx * 0.2f, min_ty*this->deltaY + ny * 0.2f);
		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			if (e->object->GetObjectType() == OBJECT_TYPE::SOLDIER_SWORD) {		
				SoldierSword *enemy = dynamic_cast<SoldierSword *>(e->object);
				if (e->nx != 0) {
					enemy->SetState(ENEMY_STATE::DEAD);
					this->isActive = false;
				}
			}
			if (e->object->GetObjectType() == OBJECT_TYPE::PANTHER) {
				Panther *enemy = dynamic_cast<Panther *>(e->object);
				if (e->nx != 0) {
					enemy->SetState(ENEMY_STATE::DEAD);
					this->isActive = false;
				}
			}
			Object::PlusPosition(this->deltaX, 0.0f);
		}
	}
}

void SmallShuriken::Render() {
	if (isActive) {
		sprite->DrawSprite(Object::GetTransformObjectPositionByCamera(), false);
	}
}