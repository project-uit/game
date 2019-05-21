#include "SoliderRun.h"
#include "Square.h"
#include "Player.h"

SoliderRun::SoliderRun() {

}

SoliderRun::~SoliderRun() {

}

SoliderRun::SoliderRun(int posX, int posY, vector<int> movingLimit, vector<int> activeArea) {
	this->movingLimit = movingLimit;
	this->activeArea = activeArea;
	SetObjectType(OBJECT_TYPE::SOLIDER_RUN);
	isOnGround = false;
	SetPosition(posX, posY);
	InitSpite();
}

void SoliderRun::InitSpite() {
	sprite = new  map<ENEMY_STATE, Sprite*>();
	/*sprite->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FOLLOW,
		new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_RUN_ATK, 2, 0.09f)));*/
	sprite->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
		new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 2, 0.04f)));
}

void SoliderRun::Update(float t, vector<Object*>* objects) {
	if (state != ENEMY_STATE::INVISIBLE) {
		Object::Update(t);
		RECT rect = sprite->at(state)->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);
		sprite->at(state)->NextSprite(t);
		if (state == ENEMY_STATE::DEAD) {
			if (sprite->at(state)->GetIsComplete()) {
				sprite->at(state)->Reset();
				state = ENEMY_STATE::INVISIBLE;
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
				veclocity.y += GRAVITY * t;
				PlusPosition(deltaX, deltaY);
			}

			if (Game::AABB(Player::GetInstance()->GetKatana()->GetBoundingBox(), GetBoundingBox())) {
				state = ENEMY_STATE::DEAD;
			}
		}
	}
}

void SoliderRun::HandleCollision(vector<Object*> *objects) {
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

void SoliderRun::HandleDirection() {
	float width = GetBoundingBox().right - GetBoundingBox().left;

	if (position.x + width <= movingLimit.at(0)) {
		SetVx(SOLIDER_RUN_VX);
		direction = DIRECTION::RIGHT;
	}

	if (position.x + width >= movingLimit.at(1)) {
		SetVx(-SOLIDER_RUN_VX);
		direction = DIRECTION::LEFT;
	}

	if (state != ENEMY_STATE::ATK) {
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
}

void SoliderRun::HandleAttack(float t) {
	/*if (this->state != ENEMY_STATE::ATK) {
		if (timerDelayShooting >= SHOOT_TIME_DELAY) {
			state = ENEMY_STATE::ATK;
			SetVx(0);
			timerDelayShooting = 0;
		}
		else {
			timerDelayShooting += t;
		}
	}
	else {
		if (timerDelayShooting >= BULLET_DELAY_TIME) {
			if (countShoot < MAX_NUMBER_OF_BULLET) {
				bullet[countShoot]->Fly(direction);
				countShoot++;
			}
			else {
				countShoot = 0;
				sprite->at(state)->Reset();
			}
			timerDelayShooting = 0;
		}
		else {
			timerDelayShooting += t;
		}
	}*/
}

void SoliderRun::Render() {
	if (state != ENEMY_STATE::INVISIBLE) {
		switch (direction) {
		case RIGHT:
			sprite->at(state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true);
			break;
		case LEFT:
			sprite->at(state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false);
			break;
		default:
			break;
		}
	}
}

void SoliderRun::ResetState() {
	isActive = false;
	isOnGround = false;
	if (state == ENEMY_STATE::DEAD) {
		sprite->at(ENEMY_STATE::DEAD)->Reset();
	}
	state = ENEMY_STATE::DO_NOTHING;
	SetPosition(lastPos.x, lastPos.y);
}