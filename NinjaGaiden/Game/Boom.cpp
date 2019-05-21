#include "Boom.h"
#include "Camera.h"
#include "Player.h"
Boom::Boom() {
	objectType = BOOM_BOSS;
	isActive = false;
	state = FOLLOW;
	SetVeclocity(0.0f, 0.0f);
	this->sprite = new  map<ENEMY_STATE, Sprite*>();
	SetPosition(50.0f, 50.0f);
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FOLLOW,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_3_BOOM_BOSS, 1, 0.0f)));
}

Boom::~Boom() {
	if (this->sprite != NULL) {
		for (auto i = this->sprite->begin(); i != this->sprite->end(); i++) {
			delete i->second;
			this->sprite->erase(i);
		}
		delete this->sprite;
	}
}

void Boom::Update(float t, vector<Object*>* object) {
	if (isActive) {
		Object::Update(t);
		//this->veclocity.y += GRAVITY;
		RECT rect = sprite->at(this->state)->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);
		HandleCollision(object);
	}
}

void Boom::HandleCollision(vector<Object*>* object) {
	vector<CollisionHandler*>* coEvents = new vector<CollisionHandler*>();
	vector<CollisionHandler*>* coEventsResult = new vector<CollisionHandler*>();
	coEvents->clear();
	if (state != ENEMY_STATE::DEAD) {
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
			if (e->object->GetObjectType() == OBJECT_TYPE::MAIN_CHARACTER) {
				if (!Player::GetInstance()->GetWounded()) {
					Player::GetInstance()->Wounded(e->nx, e->ny, this, GetObjectDirection());
				}
			}
			Object::PlusPosition(this->deltaX, deltaY);
		}
	}

	for (UINT i = 0; i < coEvents->size(); i++) {
		delete coEvents->at(i);
	}

	delete coEvents;
	delete coEventsResult;
}

void Boom::Render() {
	if (isActive) {
		sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false);
	}
}

void Boom::ResetState() {

}

bool Boom::IsOutCamera() {
	return !Game::AABB(GetBoundingBox(), Camera::GetInstance()->GetRECTx());
}

void Boom::SetFly(bool fly) {
	this->isFly = fly;
}

bool Boom::IsFly() {
	return isFly;
}