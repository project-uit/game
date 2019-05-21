#include "BigShuriken.h"
#include "SoldierSword.h"
#include "Player.h"
BigShuriken::BigShuriken() {
	this->SetObjectType(BIG_SHURIKEN);
	objectWidth = objectHeight = 1;
	this->position.z = 0.0f;
	this->isActive = false;
	left = 0.0f;
	right = 0.0f;
	SetVx(0.0f);
	SetVy(0.0f);
	this->SetPosition(0, 0);
	sprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_BigShuriken, 1, 0.0f);
}

BigShuriken::~BigShuriken() {
	delete sprite;
}

void BigShuriken::SetOrbitMoving(bool moving) {
	orbitMoving = moving;
}

void BigShuriken::Orbit(float t) {
	left = Player::GetInstance()->GetPosition().x + 80.0f;
	right = Player::GetInstance()->GetPosition().x - 80.0f;
	if (position.x >= left) {
		SetVx(-400.0f);
	}
	if (position.x <= right) {
		SetVx(400.0f);
	}
	if (Player::GetInstance()->GetPosition().y + 4  < position.y) {
		if (this->veclocity.y >= 0) {
			this->veclocity.y = 0.0f;
		}
		this->veclocity.y += -130.0f*t;
		if (this->veclocity.y <= -200.0f) {
			this->veclocity.y = -200.0f;
		}
	}
	else {
		if (this->veclocity.y <= 0) {
			this->veclocity.y = 0.0f;
		}
		this->veclocity.y += 130.0f*t;
		if (this->veclocity.y >= 200.0f) {
			this->veclocity.y = 200.0f;
		}
	}
}

void BigShuriken::Update(float t, vector<Object*> *object) {
	if (isActive) {
		Orbit(t);
		Object::Update(t);
		RECT rect = sprite->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);
		sprite->NextSprite(t);
		//HandleCollision(object);
		Object::PlusPosition(this->deltaX, this->deltaY);
	}
	else {
		SetPosition(0.0f, 0.0f);
	}
}

void BigShuriken::HandleCollision(vector<Object*> *object) {
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
		//this->PlusPosition(min_tx * this->deltaX + nx * 0.2f, min_ty*this->deltaY + ny * 0.2f);
		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			if (e->object->GetObjectType() == OBJECT_TYPE::MAIN_CHARACTER) {
				if (e->nx != 0 || e->ny != 0) {
					isActive = false;
					SetVx(0.0f);
					SetVy(0.0f);
				}
				continue;
			}
			Object::PlusPosition(this->deltaX, this->deltaY);
		}
	}
}

void BigShuriken::Render() {
	if (isActive) {
		sprite->DrawSprite(Object::GetTransformObjectPositionByCamera(), false);
	}
}
