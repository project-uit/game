#include "SoliderBazoka.h"
#include "Bullet.h"
#include "Square.h"
#include "Player.h"
#include "GameDebugDraw.h"
#include "Sound.h"

SoliderBazoka::SoliderBazoka() {

}

SoliderBazoka::~SoliderBazoka() {

}

SoliderBazoka::SoliderBazoka(int posX, int posY, vector<int> movingLimit, vector<int> activeArea) {
	this->movingLimit = movingLimit;
	this->activeArea = activeArea;
	SetObjectType(OBJECT_TYPE::SOLIDER_BAZOKA);
	isOnGround = false;
	state = ENEMY_STATE::DO_NOTHING;
	bullet = new Bullet(posX, posY, BULLET_TYPE::BAZOKA, direction);

	timerDelayShooting = 0;
	SetPosition(posX, posY);

	InitSpite();
}

void SoliderBazoka::InitSpite() {
	this->sprite = new  map<ENEMY_STATE, Sprite*>();
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DO_NOTHING,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_BAZOKA_DO_NOT_THING, 1, 0)));
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::ATK,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_BAZOKA_ATK, 2, 0.09f)));
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY_DIE_FIRE), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 3, 0.04f)));
}

void SoliderBazoka::Update(float t, vector<Object*>* objects) {
	if (isActive) {
		Object::Update(t);
		this->veclocity.y += GRAVITY * t;
		RECT rect = sprite->at(state)->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);
		sprite->at(state)->NextSprite(t);
		if (state == ENEMY_STATE::DEAD) {
			if (sprite->at(state)->GetIsComplete()) {
				sprite->at(state)->Reset();
				isActive = false;
				bullet->SetState(ENEMY_STATE::INVISIBLE);
			}
		}
		else {
			HandleCollision(objects);
			HandleDirection();
			HandleAttack(t);
			Player::GetInstance()->KillEnemy(this);
		}

		bullet->Update(t, objects);
		bullet->UpdateSoliderPosition(position);
	}
}

void SoliderBazoka::HandleCollision(vector<Object*> *objects) {
	vector<CollisionHandler*>* coEvents = new vector<CollisionHandler*>();
	vector<CollisionHandler*>* coEventsResult = new vector<CollisionHandler*>();
	coEvents->clear();
	if (state != ENEMY_STATE::DEAD) {
		Object::CalcPotentialCollisions(objects, coEvents);
	}
	if (coEvents->size() == 0) {
		Object::PlusPosition(this->deltaX, this->deltaY);
	} else {
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		this->PlusPosition(min_tx * this->deltaX + nx * 0.2f, min_ty*this->deltaY + ny * 0.2f);
		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			if (e->object->GetObjectType() == OBJECT_TYPE::SQUARE) {
				if (e->ny < 0) {
					SetVy(0);
				}
			}
			else if (e->object->GetObjectType() == OBJECT_TYPE::MAIN_CHARACTER) {
				if (!Player::GetInstance()->GetWounded()) {
					if (Player::GetInstance()->GetState() == JUMP_ATK) {
						state = ENEMY_STATE::DEAD;
					}
					else {
						Player::GetInstance()->Wounded(e->nx, e->ny, this, direction);
					}
				}
			}
		}
	}

	for (UINT i = 0; i < coEvents->size(); i++) {
		delete coEvents->at(i);
	}

	delete coEvents;
	delete coEventsResult;
}

void SoliderBazoka::HandleDirection() {
	float boxWidth = GetBoundingBox().right - GetBoundingBox().left;

	if (position.x <= movingLimit.at(0)) {
		SetVx(SOLIDER_BAZOKA_VX);
		direction = DIRECTION::RIGHT;
	}

	if (position.x + boxWidth >= movingLimit.at(1)) {
		SetVx(-SOLIDER_BAZOKA_VX);
		direction = DIRECTION::LEFT;
	}

	if (Player::GetInstance()->GetPosition().x >= activeArea.at(0)
		&& Player::GetInstance()->GetPosition().x <= activeArea.at(1)) {
		if (Player::GetInstance()->GetPosition().x <= position.x) {
			direction = DIRECTION::LEFT;
		}
		else {
			direction = DIRECTION::RIGHT;
		}
	}
}

void SoliderBazoka::HandleAttack(float t) {
	if (state != ENEMY_STATE::ATK) {
		if (timerDelayShooting >= SHOOT_TIME_DELAY) {
			Sound::GetInstance()->Play(SOUND_ENEMY_BAZOKA, false, 1);
			state = ENEMY_STATE::ATK;
			bullet->Fly(direction);
			SetVx(0);
			timerDelayShooting = 0;
		}
		else {
			timerDelayShooting += t;
		}
	}
	else {
		if (sprite->at(state)->GetIsComplete()) {
			sprite->at(state)->Reset();
			state = ENEMY_STATE::DO_NOTHING;
		}
	}
}

void SoliderBazoka::Dead() {
	Sound::GetInstance()->Play(SOUND_ENEMY_DIE, false, 1);
	state = ENEMY_STATE::DEAD;
}

void SoliderBazoka::Render() {
	if (isActive) {
		switch (this->direction) {
		case RIGHT:
			if (state == ENEMY_STATE::DEAD) {
				sprite->at(state)->SetScale(sprite->at(state)->GetScale() + 0.015f);
			}
			sprite->at(state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true);
			break;
		case LEFT:
			if (state == ENEMY_STATE::DEAD) {
				sprite->at(state)->SetScale(sprite->at(state)->GetScale() + 0.015f);
			}
			sprite->at(state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false);
			break;
		default:
			break;
		}
	}

	bullet->Render();
}

void SoliderBazoka::ResetState() {
	isActive = true;
	if (state == ENEMY_STATE::DEAD) {
		sprite->at(ENEMY_STATE::DEAD)->Reset();
	}
	SetPosition(lastPos.x, lastPos.y);

	state = ENEMY_STATE::DO_NOTHING;
	bullet->SetState(ENEMY_STATE::INVISIBLE);
}
