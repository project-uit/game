#include "Panther.h"
#include "Player.h"
#include "Camera.h"
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
	this->sprite = new  map<ENEMY_STATE, Sprite*>();
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FOLLOW,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_Panther_follow, 2, 0.08f)));
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 2, 0.04f)));
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
	UpdateActiveArea(t);
	if (isActive) {
		Object::Update(t);
		this->veclocity.y += GRAVITY;
		RECT rect = sprite->at(this->state)->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);

		sprite->at(this->state)->NextSprite(t);

		if (state == ENEMY_STATE::DEAD) {
			if (sprite->at(this->state)->GetIsComplete()) {
				sprite->at(this->state)->SetIndex(1);
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
			if (Game::AABB(Player::GetInstance()->GetKatana()->GetBoundingBox(), GetBoundingBox())
				|| Game::AABB(Player::GetInstance()->GetWeapon()->GetBoundingBox(), GetBoundingBox())) {
				state = ENEMY_STATE::DEAD;
				SetVx(0.0f);
				Object::PlusPosition(0, -20.0f);
			}
		}
	}
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
			else if (e->object->GetObjectType() == OBJECT_TYPE::PANTHER) {
				Object::PlusPosition(this->deltaX,deltaY);
			}
			else {
				Object::PlusPosition(this->deltaX, 0.0f);
			}
		}
	}

	for (UINT i = 0; i < coEvents->size(); i++) {
		delete coEvents->at(i);
	}

	delete coEvents;
	delete coEventsResult;
}

void Panther::Render() {
	if (this->isActive) {
		switch (this->direction) {
		case RIGHT:
			sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true);
			break;
		case LEFT:
			sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false);
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
		}
		objectWidth = objectHeight = 1;
		state = ENEMY_STATE::FOLLOW;
		SetPosition(lastPos.x, lastPos.y);
	}
}

void Panther::SetState(ENEMY_STATE state) {
	this->state = state;
}