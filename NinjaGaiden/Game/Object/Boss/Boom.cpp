#include "Boom.h"
#include "../../Framework/Camera.h"
#include "../Player/Player.h"
#include "../../Framework/MCIPlayer.h"
Boom::Boom() {
	objectType = BOOM_BOSS;
	isActive = false;
	state = FOLLOW;
	SetVeclocity(0.0f, 0.0f);
	this->sprite = new  map<ENEMY_STATE, Sprite*>();
	position.z = 0;
	SetPosition(50.0f, 50.0f);
	score = 200;
	time = 0;
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FOLLOW,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_3_BOOM_BOSS, 1, 0.0f)));
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY_DIE_FIRE), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 3, 0.03f)));
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

void Boom::Update(float t, float runTime, vector<Object*>* object) {
	if (isActive) {
		if (time >= runTime) {
			Update(t, object);
		}
		else {
			time += t;
		}
	}
}

void Boom::Update(float t, vector<Object*>* object) {
	
	Object::Update(t);
	RECT rect = sprite->at(this->state)->GetBoudingBoxFromCurrentSprite();
	Object::updateBoundingBox(rect);
	HandleCollision(object);
	Player::GetInstance()->KillEnemy(this);
	if (state == ENEMY_STATE::DEAD) {
		sprite->at(this->state)->NextSprite(t);
		if (sprite->at(this->state)->GetIsComplete()) {
			sprite->at(this->state)->SetIndex(2);
			sprite->at(this->state)->SetScale(1.0f);
			isActive = false;
			sprite->at(this->state)->Reset();
			state = FOLLOW;
			time = 0;
		}
	}
}

void Boom::Dead() {
	state = DEAD;
	SetVeclocity(0.0f, 0.0f);
	sprite->at(this->state)->SetScale(1.0f);
	Player::GetInstance()->AddScore(score);
	MCIPlayer::GetInstance()->Play(SOUND_ENEMY_DIE);
}

ENEMY_STATE Boom::GetState() {
	return state;
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
		//this->PlusPosition(min_tx * this->deltaX + nx * 0.2f, min_ty*this->deltaY + ny * 0.2f);
		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			if (e->object->GetObjectType() == OBJECT_TYPE::MAIN_CHARACTER) {
				if (!Player::GetInstance()->GetWounded()) {
					if (Player::GetInstance()->GetState() == JUMP_ATK) {
						state = ENEMY_STATE::DEAD;
						MCIPlayer::GetInstance()->Play(SOUND_ENEMY_DIE);
						Player::GetInstance()->AddScore(score);
					}
					else {
						Player::GetInstance()->Wounded(e->nx, e->ny, this, GetObjectDirection());
					}
				}
			}
			Object::PlusPosition(this->deltaX, this->deltaY);
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
		if (state != DEAD) {
			sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false);
		}
		else {
			sprite->at(this->state)->SetScale(sprite->at(this->state)->GetScale() + 0.015f);
			if (GetObjectDirection() == LEFT) {
				sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false, -5, -5);
			}
			else {
				sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false, -15, -9);
			}
		}
	}
}

void Boom::ResetState() {
	time = 0;
	state = FOLLOW;
}

bool Boom::IsOutCamera() {
	return !Game::AABB(GetBoundingBox(), Camera::GetInstance()->GetRECTx());
}
