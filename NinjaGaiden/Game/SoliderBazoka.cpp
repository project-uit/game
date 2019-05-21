#include "SoliderBazoka.h"
#include "Bullet.h"
#include "Square.h"
#include "Player.h"
#include "GameDebugDraw.h"

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
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 2, 0.04f)));
}

void SoliderBazoka::Update(float t, vector<Object*>* objects) {
	if (state != INVISIBLE) {
		Object::Update(t);
		RECT rect = sprite->at(state)->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);
		sprite->at(state)->NextSprite(t);
		if (state == ENEMY_STATE::DEAD) {
			if (sprite->at(state)->GetIsComplete()) {
				sprite->at(state)->Reset();
				state = ENEMY_STATE::INVISIBLE;
				bullet->SetState(ENEMY_STATE::INVISIBLE);
			}
		}
		else {
			HandleCollision(objects);
			HandleDirection();
			HandleAttack(t);

			if (isOnGround) {
				PlusPosition(deltaX, 0);
			}
			else {
				veclocity.y += GRAVITY;
				PlusPosition(deltaX, 0);
			}

			if (Game::AABB(Player::GetInstance()->GetKatana()->GetBoundingBox(), GetBoundingBox())) {
				state = ENEMY_STATE::DEAD;
			}
		}

		bullet->Update(t, objects);
		bullet->UpdateSoliderPosition(position);
	}
}

void SoliderBazoka::HandleCollision(vector<Object*> *objects) {
	vector<CollisionHandler*>* coEvents = new vector<CollisionHandler*>();
	vector<CollisionHandler*>* coEventsResult = new vector<CollisionHandler*>();
	coEvents->clear();
	Object::CalcPotentialCollisions(objects, coEvents);
	if (coEvents->size() != 0) {
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			if (e->object->GetObjectType() == OBJECT_TYPE::SQUARE) {
				if (e->ny < 0) {
					isOnGround = true;
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

void SoliderBazoka::Render() {
	if (state != INVISIBLE) {
		switch (this->direction) {
		case RIGHT:
			sprite->at(state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true, 15,0);
			break;
		case LEFT:
			sprite->at(state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false);
			break;
		default:
			break;
		}
	}

	bullet->Render();
}

void SoliderBazoka::ResetState() {
	isActive = false;
	isOnGround = false;
	if (state == ENEMY_STATE::DEAD) {
		sprite->at(ENEMY_STATE::DEAD)->Reset();
	}
	SetPosition(lastPos.x, lastPos.y);

	state = ENEMY_STATE::DO_NOTHING;
	bullet->SetState(ENEMY_STATE::INVISIBLE);
}
