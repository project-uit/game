#include "SoliderGun.h"
#include "Bullet.h"
#include "Square.h"
#include "Player.h"
#include "GameDebugDraw.h"
#include "Sound.h"

SoliderGun::SoliderGun() {

}

SoliderGun::~SoliderGun() {

}

SoliderGun::SoliderGun(int posX, int posY, vector<int> movingLimit, vector<int> activeArea) {
	this->movingLimit = movingLimit;
	this->activeArea = activeArea;
	SetObjectType(OBJECT_TYPE::SOLIDER_GUN);
	isOnGround = false;
	for (int i = 0; i < MAX_NUMBER_OF_BULLET; i++) {
		bullet[i] = new Bullet(posX, posY, BULLET_TYPE::GUN, direction);
	}

	countShoot = 0;
	timerDelayShooting = 0;
	SetPosition(posX, posY);

	InitSpite();
	GotoStateFollow();
}

void SoliderGun::InitSpite() {
	sprite = new  map<ENEMY_STATE, Sprite*>();
	sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FOLLOW,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_GUN_FOLLOW, 2, 0.09f)));
	sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::ATK,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_GUN_ATK, 2, 0.09f)));
	sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY_DIE_FIRE), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 3, 0.04f)));
}

void SoliderGun::Update(float t, vector<Object*>* objects) {
	if (state != ENEMY_STATE::INVISIBLE) {
		Object::Update(t);
		RECT rect = sprite->at(state)->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);
		sprite->at(state)->NextSprite(t);
		if (state == ENEMY_STATE::DEAD) {
			if (sprite->at(state)->GetIsComplete()) {
				sprite->at(state)->Reset();
				state = ENEMY_STATE::INVISIBLE;
				for (int i = 0; i < MAX_NUMBER_OF_BULLET; i++) {
					bullet[i]->SetState(ENEMY_STATE::INVISIBLE);
				}
			}
		}
		else {
			HandleCollision(objects);
			HandleDirection();
			HandleAttack(t);

			if (!isOnGround) {
				veclocity.y += GRAVITY * t;
			}
			else {
				SetVy(0);
			}
			PlusPosition(deltaX, deltaY);
			Player::GetInstance()->KillEnemy(this);
		}

		for (int i = 0; i < MAX_NUMBER_OF_BULLET; i++) {
			bullet[i]->Update(t, objects);
			bullet[i]->UpdateSoliderPosition(position);
		}
	}
}

void SoliderGun::HandleCollision(vector<Object*> *objects) {
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
	coEventsResult->clear();
	coEvents->clear();
	delete coEvents;
	delete coEventsResult;
}

void SoliderGun::HandleDirection() {
	float width = GetBoundingBox().right - GetBoundingBox().left;

	if (position.x + width <= movingLimit.at(0)) {
		SetVx(SOLIDERGUN_VX);
		direction = DIRECTION::RIGHT;
	}

	if (position.x + width >= movingLimit.at(1)) {
		SetVx(-SOLIDERGUN_VX);
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

void SoliderGun::HandleAttack(float t) {
	if (this->state != ENEMY_STATE::ATK) {
		if (timerDelayShooting >= SHOOT_TIME_DELAY) {
			Sound::GetInstance()->Play(SOUND_ENEMY_GUN, false, 1);
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
				this->GotoStateFollow();
			}
			timerDelayShooting = 0;
		}
		else {
			timerDelayShooting += t;
		}
	}
}

void SoliderGun::Dead() {
	Sound::GetInstance()->Play(SOUND_ENEMY_DIE, false, 1);
	state = ENEMY_STATE::DEAD;
	SetVeclocity(0.0f, 0.0f);
	Object::PlusPosition(0, -3.0f);
}

void SoliderGun::GotoStateFollow() {
	state = ENEMY_STATE::FOLLOW;
	if (direction == DIRECTION::LEFT) {
		this->SetVeclocity(-SOLIDERGUN_VX, 0);
	}
	else {
		this->SetVeclocity(SOLIDERGUN_VX, 0);
	}
}

void SoliderGun::Render() {
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

		for (int i = 0; i < MAX_NUMBER_OF_BULLET; i++) {
			bullet[i]->Render();
		}
	}
}

void SoliderGun::ResetState() {
	isActive = false;
	isOnGround = false;
	if (state == ENEMY_STATE::DEAD) {
		sprite->at(ENEMY_STATE::DEAD)->Reset();
	}
	GotoStateFollow();
	SetPosition(lastPos.x, lastPos.y);
	for (int i = 0; i < MAX_NUMBER_OF_BULLET; i++) {
		bullet[i]->SetState(ENEMY_STATE::INVISIBLE);
	}
}