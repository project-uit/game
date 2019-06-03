#include "SoliderRun.h"
#include "Square.h"
#include "Player.h"

SoliderRun::SoliderRun() {

}

SoliderRun::~SoliderRun() {
	if (this->sprite != NULL) {
		for (auto i = this->sprite->begin(); i != this->sprite->end(); i++) {
			delete i->second;
			this->sprite->erase(i);
		}
		delete this->sprite;
	}
}

SoliderRun::SoliderRun(int posX, int posY, vector<int> movingLimit, vector<int> activeArea) {
	this->movingLimit = movingLimit;
	this->activeArea = activeArea;
	SetPosition(posX, posY);
	Init();
}

void SoliderRun::Init() {
	SetObjectType(OBJECT_TYPE::SOLIDER_RUN);
	isOnGround = false;
	objectWidth = objectHeight = 1;
	this->position.z = 0.0f;
	this->isActive = false;
	state = FOLLOW;
	SetVeclocity(0.0f, 0.0f);
	resetTime = 0;
	leftMoving = 0;
	left = 0;
	right = 9999;
	rightMoving = 0;
	score = 300;
	sprite = new  map<ENEMY_STATE, Sprite*>();
	sprite->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FOLLOW,
		new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_SoldierRun, 2, 0.085f)));
	sprite->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::HIGH_JUMP,
		new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_SoldierRun_JUMP, 1, 0.0f)));
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY_DIE_FIRE), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 3, 0.03f)));
}

void SoliderRun::HandleDirection(float t) {
	if (state == DEAD && !isActive) {
		if (resetTime >= 0.15f) {
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
			if (direction == RIGHT) {
				SetVeclocity(40.0f, 0.0f);
			}
			if (direction == LEFT) {
				SetVeclocity(-40.0f, 0.0f);
			}
		}
		else {
			resetTime += t;
		}
	}
	if (state != DEAD && !isActive) {
		if (Player::GetInstance()->GetPosition().x >= activeArea.at(0)
			&& Player::GetInstance()->GetPosition().x <= activeArea.at(1)
			&& Player::GetInstance()->GetDirection() == RIGHT) {
			isActive = true;
			direction = LEFT;
			SetVx(-150.0f);
			leftMoving = movingLimit.at(0);
			rightMoving = movingLimit.at(1);
		}
		else {
			if (Player::GetInstance()->GetPosition().x >= activeArea.at(2)
				&& Player::GetInstance()->GetPosition().x <= activeArea.at(3)
				&& Player::GetInstance()->GetDirection() == RIGHT) {
				isActive = true;
				direction = RIGHT;
				SetVx(150.0f);
				leftMoving = movingLimit.at(2);
				rightMoving = movingLimit.at(3);
			}
		}
	}
}

void SoliderRun::Update(float t, vector<Object*>* objects) {
	HandleDirection(t);
	if (isActive) {
		Object::Update(t);
		this->veclocity.y += GRAVITY * t;
		RECT rect = sprite->at(this->state)->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);
		sprite->at(this->state)->NextSprite(t);
		if (state == ENEMY_STATE::DEAD) {
			if (sprite->at(this->state)->GetIsComplete()) {
				sprite->at(this->state)->SetIndex(2);
				sprite->at(this->state)->SetScale(1.0f);
				isActive = false;
			}
			this->sprite->at(ENEMY_STATE::FOLLOW)->Reset();
			SetVx(0.0f);
		}
		else {
			HandleCollision(objects);
			float width = GetBoundingBox().right - GetBoundingBox().left;
			if (width + position.x < left + 20) {
				SetVy(-250.0f);
				SetVx(-140.0f);
				state = HIGH_JUMP;
				left = 0;
			}
			if (width + position.x > right + 20) {
				SetVy(-250.0f);
				SetVx(170.0f);
				state = HIGH_JUMP;
				right = 8888;
			}
			Player::GetInstance()->KillEnemy(this);
		}
	}
}

void SoliderRun::HandleCollision(vector<Object*> *objects) {
	vector<CollisionHandler*>* coEvents = new vector<CollisionHandler*>();
	vector<CollisionHandler*>* coEventsResult = new vector<CollisionHandler*>();
	coEvents->clear();
	if (state != ENEMY_STATE::DEAD) {
		Object::CalcPotentialCollisions(objects, coEvents);
	}
	if (coEvents->size() == 0) {
		Object::PlusPosition(this->deltaX, this->deltaY);
	}
	else {
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		this->PlusPosition(min_tx * this->deltaX + nx * 0.2f, min_ty*this->deltaY + ny * 0.2f);
		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			
			if (e->object->GetObjectType() == OBJECT_TYPE::SQUARE) {
				if (right == 8888) {
					Object::PlusPosition(this->deltaX, this->deltaY);
					continue;
				}
				if (e->ny < 0) {
					isOnGround = true;
					state = FOLLOW;
					this->SetVy(0.0f);
					if (direction == LEFT) {
						SetVx(-150.0f);
					}
					else {
						SetVx(150.0f);
					}

					left = e->object->GetBoundingBox().left;
					right = e->object->GetBoundingBox().right;
				}
				if (e->nx != 0) {
					SetVx(-10.0f);
					SetVy(-190.0f);
					state = HIGH_JUMP;
					isOnGround = false;
				}
				continue;
			}
			else if (e->object->GetObjectType() == OBJECT_TYPE::ROCK) {
				if (e->nx != 0) {
					state = HIGH_JUMP;
					SetVy(-150.0f);
					SetVx(0.0f);
					
				}
				continue;
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
			else if (e->object->GetObjectType() == OBJECT_TYPE::FOOD) {
				if (e->nx != 0) {
					Object::PlusPosition(this->deltaX, 0.0f);
				}
				if (e->ny != 0) {
					Object::PlusPosition(0, deltaY);
				}
				continue;
			}
			Object::PlusPosition(this->deltaX, 0.0f);
		}
	}

	for (UINT i = 0; i < coEvents->size(); i++) {
		delete coEvents->at(i);
	}

	delete coEvents;
	delete coEventsResult;
}


void SoliderRun::Render() {
	if (isActive) {
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

void SoliderRun::Dead() {
	state = ENEMY_STATE::DEAD;
	SetVeclocity(0.0f, 0.0f);
	resetTime = 0;
	Object::PlusPosition(0, -3.0f);
	Player::GetInstance()->AddScore(this->score);
}

void SoliderRun::ResetState() {
	isActive = false;
	isOnGround = false;
	if (state == ENEMY_STATE::DEAD) {
		sprite->at(ENEMY_STATE::DEAD)->Reset();
	}
	right = 9999;
	left = 0;
	SetVeclocity(0.0f, 0.0f);
	state = ENEMY_STATE::FOLLOW;
	SetPosition(lastPos.x, lastPos.y);
}