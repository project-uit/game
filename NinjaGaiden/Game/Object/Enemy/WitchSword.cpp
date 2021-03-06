#include "../Square/Square.h"
#include "../Player/Player.h"
#include "WitchSword.h"
#include "../../Logging/GameDebugDraw.h"
#include "../../Framework/MCIPlayer.h"

WitchSword::WitchSword(int positionX, int positionY, DIRECTION direction) {
	this->SetObjectType(WITCH_SWORD);
	this->SetPosition(positionX, positionY);
	this->position.z = 0.0f;
	this->SetVeclocity(0.0f, 0.0f);
	this->isActive = true;
	this->state = INVISIBLE;
	this->countThrow = 0;
	this->direction = direction;
	this->score = 100;
	this->sprite = new  map<ENEMY_STATE, Sprite*>();
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FLY,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_WITCH_SWORD, 2, 0.09f)));
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY_DIE_FIRE), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 3, 0.03f)));
}

WitchSword::~WitchSword() {
	if (this->sprite != NULL) {
		for (auto i = this->sprite->begin(); i != this->sprite->end(); i++) {
			delete i->second;
			this->sprite->erase(i);
		}
		delete this->sprite;
	}
}

void WitchSword::Update(float t, vector<Object*>* objects) {
	if (Player::GetInstance()->isFreezeTime() && isActive) {
		SetVeclocity(0, 0);
		Object::Update(t);
		HandleCollision(objects);
		Player::GetInstance()->KillEnemy(this);
		if (state == DEAD) {
			sprite->at(this->state)->NextSprite(t);
			if (sprite->at(this->state)->GetIsComplete()) {
				sprite->at(this->state)->SetIndex(2);
				sprite->at(this->state)->SetScale(1.0f);
				isActive = false;
			}
			this->sprite->at(ENEMY_STATE::FOLLOW)->Reset();
			SetVx(0.0f);
		}
		return;
	}
	if (state != INVISIBLE) {
		Object::Update(t);
		veclocity.y += GRAVITY * t;

		PlusPosition(deltaX, deltaY);
		RECT rect = sprite->at(this->state)->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);
		sprite->at(this->state)->NextSprite(t);
		HandleCollision(objects);
		if (state == ENEMY_STATE::DEAD) {
			if (sprite->at(state)->GetIsComplete()) {
				sprite->at(state)->Reset();
				sprite->at(this->state)->SetScale(1.0f);
				state = ENEMY_STATE::INVISIBLE;
			}
		}
		else {
			Player::GetInstance()->KillEnemy(this);
		}
	}
}

void WitchSword::UpdateWitchPosition(D3DXVECTOR3 witchPosition) {
	this->witchPosition = witchPosition;
}

void WitchSword::HandleCollision(vector<Object*> *object) {
	vector<CollisionHandler*>* coEvents = new vector<CollisionHandler*>();
	vector<CollisionHandler*>* coEventsResult = new vector<CollisionHandler*>();
	coEvents->clear();
	Object::CalcPotentialCollisions(object, coEvents);
	if (coEvents->size() != 0) {
		float min_tx, min_ty, nx = 0, ny;
		this->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			if (e->object->GetObjectType() == OBJECT_TYPE::MAIN_CHARACTER) {
				if (this->state == FLY) {
					if (!Player::GetInstance()->GetWounded()) {
						state = INVISIBLE;
						if (Player::GetInstance()->GetState() == JUMP_ATK) {
							state = ENEMY_STATE::DEAD;
							MCIPlayer::GetInstance()->Play(SOUND_ENEMY_DIE);
							Player::GetInstance()->AddScore(score);
							continue;
						}
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

void WitchSword::Render() {
	if (state != INVISIBLE) {
		switch (this->direction) {
		case RIGHT:
			if (state == ENEMY_STATE::DEAD) {
				sprite->at(this->state)->SetScale(sprite->at(this->state)->GetScale() + 0.015f);
				sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false, -9, 0);
			}
			else {
				sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true);
			}
			break;
		case LEFT:
			if (state == ENEMY_STATE::DEAD) {
				sprite->at(this->state)->SetScale(sprite->at(this->state)->GetScale() + 0.015f);
				sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false, -9, 0);
			}
			else {
				sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true);
			}
			break;
		default:
			break;
		}
	}
}

void WitchSword::ResetState() {
	this->isActive = false;
	if (this->state == DEAD) {
		this->sprite->at(ENEMY_STATE::DEAD)->Reset();
		sprite->at(this->state)->SetScale(1.0f);
	}
	state = ENEMY_STATE::INVISIBLE;
	SetPosition(lastPos.x, lastPos.y);
}

void WitchSword::Fly(int vX, DIRECTION direction) {
	this->state = FLY;
	this->direction = direction;
	this->veclocity.y = -WITCH_SWORD_VY;
	this->SetPosition(witchPosition.x, witchPosition.y);

	this->SetVx(-vX);

	if (direction == LEFT) {
		this->SetVx(-vX);
	}
	else {
		this->SetVx(vX);
	}
}

void WitchSword::Dead() {
	MCIPlayer::GetInstance()->Play(SOUND_ENEMY_DIE);
	state = ENEMY_STATE::DEAD;
	SetVeclocity(0, 0);
	Player::GetInstance()->AddScore(score);
}

void WitchSword::SetState(ENEMY_STATE state) {
	this->state = state;
}