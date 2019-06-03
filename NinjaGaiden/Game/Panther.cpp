#include "Panther.h"
#include "Player.h"
#include "Camera.h"
#include "Sound.h"

Panther::Panther() {
	
}

void Panther::init() {
	this->SetObjectType(PANTHER);
	this->position.z = 0.0f;
	this->isActive = false;
	isOnGround = false;
	objectHeight = objectWidth = 1;
	SetVy(0.0f);
	SetVx(0.0f);
	state = FOLLOW;
	score = 200;
	this->sprite = new  map<ENEMY_STATE, Sprite*>();
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FOLLOW,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_Panther_follow, 2, 0.08f)));
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY_DIE_FIRE), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 3, 0.03f)));
}

Panther::Panther(vector<int> movingLimit, vector<int> activeArea, int positionX, int positionY) {
	this->movingLimit = movingLimit;
	this->activeArea = activeArea;
	SetPosition((float)positionX, (float)positionY);
	init();
}

Panther::~Panther() {
	if (this->sprite != NULL) {
		for (auto i = this->sprite->begin(); i != this->sprite->end(); i++) {
			delete i->second;
			this->sprite->erase(i);
		}
		delete this->sprite;
	}
}

void Panther::UpdateActiveArea(float t) {
	if (state != DEAD) {
		/*if (Player::GetInstance()->GetPosition().x >= 813 && Player::GetInstance()->GetPosition().x <= 850) {
			if (Player::GetInstance()->GetPosition().x >= activeArea.at(0)
				&& Player::GetInstance()->GetPosition().x <= activeArea.at(1)
				&& Player::GetInstance()->GetDirection() == RIGHT
				&& activeArea.at(0) != 0
				&& activeArea.at(1) != 0) {
				isActive = true;
				direction = LEFT;
				SetVx(-180.0f);
				leftMoving = movingLimit.at(0);
				rightMoving = movingLimit.at(1);
			}
			return;
		}*/
		if (Player::GetInstance()->GetPosition().x >= 1125 && Player::GetInstance()->GetPosition().x <= 1410) {
			if (Player::GetInstance()->GetPosition().x >= activeArea.at(0)
				&& Player::GetInstance()->GetPosition().x <= activeArea.at(1)
				&& Player::GetInstance()->GetDirection() == RIGHT
				&& activeArea.at(0) != 0
				&& activeArea.at(1) != 0) {
				isActive = true;
				direction = LEFT;
				SetVx(-180.0f);
				leftMoving = movingLimit.at(0);
				rightMoving = movingLimit.at(1);
			}
			else {
				if (Player::GetInstance()->GetPosition().x >= activeArea.at(2)
					&& Player::GetInstance()->GetPosition().x <= activeArea.at(3)
					&& Player::GetInstance()->GetDirection() == LEFT
					&& activeArea.at(2) != 0
					&& activeArea.at(3) != 0) {
					isActive = true;
					direction = RIGHT;
					SetVx(180.0f);
					leftMoving = movingLimit.at(2);
					rightMoving = movingLimit.at(3);
				}
			}
			return;
		}
		if (Player::GetInstance()->GetPosition().x >= activeArea.at(0)
			&& Player::GetInstance()->GetPosition().x <= activeArea.at(1)
			&& Player::GetInstance()->GetDirection() == LEFT
			&& activeArea.at(0) != 0 
			&& activeArea.at(1) != 0) {
			isActive = true;
			direction = LEFT;
			SetVx(-180.0f);
			leftMoving = movingLimit.at(0);
			rightMoving = movingLimit.at(1);
		}
		else {
			if (Player::GetInstance()->GetPosition().x >= activeArea.at(2)
				&& Player::GetInstance()->GetPosition().x <= activeArea.at(3)
				&& Player::GetInstance()->GetDirection() == RIGHT
				&& activeArea.at(2) != 0
				&& activeArea.at(3) != 0) {
				isActive = true;
				direction = RIGHT;
				SetVx(180.0f);
				leftMoving = movingLimit.at(2);
				rightMoving = movingLimit.at(3);
			}
		}
	}
}

void Panther::Update(float t, vector<Object*>* objects) {
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
	UpdateActiveArea(t);
	if (isActive) {
		Object::Update(t);
		this->veclocity.y += GRAVITY*t;
		RECT rect = sprite->at(this->state)->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);

		sprite->at(this->state)->NextSprite(t);

		if (state == ENEMY_STATE::DEAD) {
			if (sprite->at(this->state)->GetIsComplete()) {
				sprite->at(this->state)->SetIndex(2);
				ResetState();
			}
			SetVx(0.0f);
		}

		HandleCollision(objects);
		if (state != ENEMY_STATE::DEAD) {
			float width = GetBoundingBox().right - GetBoundingBox().left;
			if (position.x + width <= leftMoving) {
				direction = RIGHT;
				SetVx(180.0f);
			}
			if (position.x + width >= rightMoving) {
				direction = LEFT;
				SetVx(-180.0f);
			}
			Player::GetInstance()->KillEnemy(this);
		}
	}
}

void Panther::Dead() {
	Sound::GetInstance()->Play(SOUND_ENEMY_DIE, false, 1);
	state = ENEMY_STATE::DEAD;
	SetVeclocity(0.0f, 0.0f);
	objectHeight = objectWidth = 1;
	Object::PlusPosition(0, -17.5f);
}

void Panther::HandleCollision(vector<Object*>* object) {
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
			if (e->object->GetObjectType() == OBJECT_TYPE::SQUARE) {
				if (e->ny < 0) {
					isOnGround = true;
					if (sprite->at(this->state)->GetIndex() == 1) {
						SetVy(-189.0f);
						isOnGround = false;
					}
				}
				if (e->nx != 0) {
					this->PlusPosition(min_tx * this->deltaX + nx * 0.2f, -12.0f);
				}
			}
			else if (e->object->GetObjectType() == OBJECT_TYPE::MAIN_CHARACTER) {
				if (!Player::GetInstance()->GetWounded()) {
					Player::GetInstance()->Wounded(e->nx, e->ny, this, direction);
				}
			}
		}
	}

	for (UINT i = 0; i < coEvents->size(); i++) {
		delete coEvents->at(i);
	}
	coEventsResult->clear();

	delete coEvents;
	delete coEventsResult;
}

void Panther::Render() {
	if (this->isActive) {
		switch (this->direction) {
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

void Panther::ResetState() {
	if (isActive) {
		this->isActive = false;
		if (this->state == DEAD) {
			this->sprite->at(ENEMY_STATE::DEAD)->Reset();
			sprite->at(this->state)->SetScale(1.0f);
		}
		objectWidth = objectHeight = 1;
		state = ENEMY_STATE::FOLLOW;
		SetPosition(lastPos.x, lastPos.y);
		SetVeclocity(0.0f, 0.0f);
	}
}

void Panther::SetState(ENEMY_STATE state) {
	this->state = state;
}