#include "SoldierSword.h"
#include "Square.h"
#include "Player.h"
#include "GameDebugDraw.h"
GameDebugDraw* draw2;
SoldierSword::SoldierSword() {
}
void SoldierSword::init() {
	this->SetObjectType(SOLDIER_SWORD);
	objectWidth = objectHeight = 1;
	this->position.z = 0.0f;
	this->isActive = false;
	time = 0;
	resetTime = 0;
	state = FOLLOW;
	draw2 = new GameDebugDraw();
	this->sprite = new  map<ENEMY_STATE, Sprite*>();
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FOLLOW,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_SoldierSword_follow, 2, 0.09f)));
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::ATK,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_SoldierSword_atk, 2, 0.15f)));
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 2, 0.04f)));
}

SoldierSword::SoldierSword(vector<int> movingLimit, vector<int> activeArea, int positionX, int positionY) {
	this->movingLimit = movingLimit;
	this->activeArea = activeArea;
	SetPosition((float)positionX, (float)positionY);
	init();
}

SoldierSword::~SoldierSword() {

}
void SoldierSword::UpdateActiveArea(float t) {
	if (state == DEAD && isActive) {
		if (resetTime >= 0.09f) {
			resetTime = 0;
			if (Player::GetInstance()->GetPosition().x >= activeArea.at(0)
				&& Player::GetInstance()->GetPosition().x <= activeArea.at(1)
				&& Player::GetInstance()->GetDirection() == RIGHT) {
				this->sprite->at(ENEMY_STATE::DEAD)->Reset();
				SetPosition(lastPos.x, lastPos.y);
				state = FOLLOW;
			}
			else {
				if (Player::GetInstance()->GetPosition().x >= activeArea.at(2)
					&& Player::GetInstance()->GetPosition().x <= activeArea.at(3)
					&& Player::GetInstance()->GetDirection() == LEFT) {
					this->sprite->at(ENEMY_STATE::DEAD)->Reset();
					SetPosition(lastPos.x, lastPos.y);
					state = FOLLOW;
				}
			}
		}
		else {
			resetTime += t;
		}
	}
	if (state != DEAD) {
		if (Player::GetInstance()->GetPosition().x >= activeArea.at(0)
			&& Player::GetInstance()->GetPosition().x <= activeArea.at(1)
			&& Player::GetInstance()->GetDirection() == RIGHT) {
			isActive = true;
			direction = LEFT;
			this->SetVeclocity(-40.0f, 0.0f);
			leftMoving = movingLimit.at(0);
			rightMoving = movingLimit.at(1);
		}
		else {
			if (Player::GetInstance()->GetPosition().x >= activeArea.at(2)
				&& Player::GetInstance()->GetPosition().x <= activeArea.at(3)
				&& Player::GetInstance()->GetDirection() == LEFT) {
				isActive = true;
				direction = RIGHT;
				this->SetVeclocity(40.0f, 0.0f);
				leftMoving = movingLimit.at(2);
				rightMoving = movingLimit.at(3);
			}
		}
	}
	
	
}

void SoldierSword::Update(float t, vector<Object*>* objects) {
	
	UpdateActiveArea(t);
	if (this->isActive) {
		Object::Update(t);
		this->veclocity.y += GRAVITY;
		RECT rect = sprite->at(this->state)->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);
		sprite->at(this->state)->NextSprite(t);

		if (state == ENEMY_STATE::DEAD) {
			if (sprite->at(this->state)->GetIsComplete()) {
				sprite->at(this->state)->SetIndex(1);
			}
			this->sprite->at(ENEMY_STATE::FOLLOW)->Reset();
			this->sprite->at(ENEMY_STATE::ATK)->Reset();
			SetVx(0.0f);
		}
		HandleCollision(objects);
		if (state != ENEMY_STATE::DEAD) {
			float width = GetBoundingBox().right - GetBoundingBox().left;
			if (position.x + width <= leftMoving) {
				SetVx(40.0f);
				direction = RIGHT;
			}
			if (position.x + width >= rightMoving) {
				SetVx(-40.0f);
				direction = LEFT;
			}
			if (time >= 0.675f) {
				state = ATK;
				time = 0.0f;
			}
			else {
				time += t;
			}

			if (sprite->at(this->state)->GetIsComplete() && state == ATK) {
				sprite->at(this->state)->Reset();
				state = FOLLOW;
				if (direction == LEFT) {
					SetVx(-40.0f);
				}
				else {
					SetVx(40.0f);
				}
			}

			if (Game::AABB(Player::GetInstance()->GetKatana()->GetBoundingBox(), GetBoundingBox())) {
				state = ENEMY_STATE::DEAD;
				SetVx(0.0f);
				Object::PlusPosition(0, -3.0f);
			}
		}
	}

}

void SoldierSword::HandleCollision(vector<Object*> *object) {
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
				//Square *item = dynamic_cast<Square *>(e->object);
				if (e->ny < 0) {
					this->SetVy(0.0f);
				}
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

void SoldierSword::ResetState() {
	this->isActive = false;
	if (this->state == DEAD) {
		this->sprite->at(ENEMY_STATE::DEAD)->Reset();
	}
	state = ENEMY_STATE::FOLLOW;
	SetPosition(lastPos.x, lastPos.y);
}

void SoldierSword::Render() {
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

void SoldierSword::SetState(ENEMY_STATE state) {
	this->state = state;
}
