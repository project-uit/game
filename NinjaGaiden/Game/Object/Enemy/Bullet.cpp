#include "../Square/Square.h"
#include "../Player/Player.h"
#include "SoliderGun.h"
#include "../../Logging/GameDebugDraw.h"
#include "../../Framework/MCIPlayer.h"
Bullet::Bullet(int positionX, int positionY, BULLET_TYPE type, DIRECTION direction) {
	this->direction = direction;
	this->type = type;
	SetPosition(positionX, positionY);
	isActive = false;
	state = ENEMY_STATE::INVISIBLE;
	sprite = new map<ENEMY_STATE, Sprite*>();
	this->score = 100;
	switch (type)
	{
	case GUN:
		sprite->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FLY,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_GUN_BULLET, 1, 0)));
		break;
	case BAZOKA:
		sprite->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FLY,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_BAZOKA_BULLET, 1, 0)));
		break;
	default:
		break;
	}

	sprite->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
		new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY_DIE_FIRE), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 3, 0.03f)));
}

Bullet::~Bullet() {
	if (this->sprite != NULL) {
		for (auto i = this->sprite->begin(); i != this->sprite->end(); i++) {
			delete i->second;
			this->sprite->erase(i);
		}
		delete this->sprite;
	}
}

void Bullet::Update(float t, vector<Object*>* objects) {
	if (state != INVISIBLE) {
		Object::Update(t);
		RECT rect = sprite->at(state)->GetBoudingBoxFromCurrentSprite();
		updateBoundingBox(rect);
		HandleCollision(objects);
		sprite->at(state)->NextSprite(t);
		if (state == ENEMY_STATE::DEAD) {
			if (sprite->at(state)->GetIsComplete()) {
				sprite->at(state)->Reset();
				sprite->at(this->state)->SetScale(1.0f);
				state = ENEMY_STATE::INVISIBLE;
			}
		}
		else {
			PlusPosition(deltaX, 0);
			Player::GetInstance()->KillEnemy(this);
		}
	}
}

void Bullet::HandleCollision(vector<Object*> *object) {
	vector<CollisionHandler*>* coEvents = new vector<CollisionHandler*>();
	vector<CollisionHandler*>* coEventsResult = new vector<CollisionHandler*>();
	coEvents->clear();
	Object::CalcPotentialCollisions(object, coEvents);
	if (coEvents->size() != 0) {
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			if (e->object->GetObjectType() == OBJECT_TYPE::MAIN_CHARACTER) {
				if (state == FLY) {
					if (!Player::GetInstance()->GetWounded()) {
						if (Player::GetInstance()->GetState() == JUMP_ATK) {
							state = ENEMY_STATE::DEAD;
							MCIPlayer::GetInstance()->Play(SOUND_ENEMY_DIE);
							Player::GetInstance()->AddScore(score);
						}
						else {
							Player::GetInstance()->Wounded(e->nx, e->ny, this, direction);
						}
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

void Bullet::Fly(DIRECTION direction) {
	state = FLY;
	this->direction = direction;

	switch (type)
	{
	case GUN:
		if (direction == LEFT) {
			SetVx(-BULLET_VX);
			SetPosition(soliderPosition.x, soliderPosition.y + 10);
		}
		else {
			SetVx(BULLET_VX);
			SetPosition(soliderPosition.x + 5, soliderPosition.y + 10);
		}
		break;
	case BAZOKA:
		if (direction == LEFT) {
			SetVx(-BULLET_VX);
			SetPosition(soliderPosition.x, soliderPosition.y + 5);
		}
		else {
			SetVx(BULLET_VX);
			SetPosition(soliderPosition.x + 15, soliderPosition.y + 5);
		}
		break;
	default:
		break;
	}
}

void Bullet::Dead() {
	MCIPlayer::GetInstance()->Play(SOUND_ENEMY_DIE);
	state = ENEMY_STATE::DEAD;
	SetVeclocity(0, 0);
	position.y = Player::GetInstance()->GetPosition().y - 10;
	Player::GetInstance()->AddScore(score);
}

void Bullet::Render() {
	if (state != INVISIBLE) {
		switch (direction) {
		case RIGHT:
			if (state == ENEMY_STATE::DEAD) {
				sprite->at(this->state)->SetScale(sprite->at(this->state)->GetScale() + 0.015f);
				sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true);
			}
			else {
				sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true);
			}
			break;
		case LEFT:
			if (state == ENEMY_STATE::DEAD) {
				sprite->at(this->state)->SetScale(sprite->at(this->state)->GetScale() + 0.015f);
				sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false);
			}
			else {
				sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false);
			}
			break;
		default:
			break;
		}
	}
}

void Bullet::ResetState() {
	isActive = false;
	if (state == DEAD) {
		sprite->at(ENEMY_STATE::DEAD)->Reset();
		sprite->at(this->state)->SetScale(1.0f);
	}
	state = ENEMY_STATE::INVISIBLE;
	SetPosition(lastPos.x, lastPos.y);
}

void Bullet::UpdateSoliderPosition(D3DXVECTOR3 soliderPosition) {
	this->soliderPosition = soliderPosition;
}

void Bullet::SetState(ENEMY_STATE state) {
	this->state = state;
}