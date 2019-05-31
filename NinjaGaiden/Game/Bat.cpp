#include "Bat.h"
#include "Square.h"
#include "Player.h"
#include "GameDebugDraw.h"
//GameDebugDraw* draw2;
Bat::Bat() {
}
void Bat::init() {
	this->SetObjectType(OBJECT_TYPE::BAT);
	objectWidth = objectHeight = 1;
	this->position.z = 0.0f;
	this->isActive = false;
	state = FOLLOW;
	score = 200;
	SetVeclocity(0.0f, 0.0f);
	this->sprite = new  map<ENEMY_STATE, Sprite*>();
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FOLLOW,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_BAT_FOLLOW, 2, 0.1f)));
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY_DIE_FIRE), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 3, 0.06f)));
}

Bat::Bat(vector<int> movingLimit, vector<int> activeArea, int positionX, int positionY) {
	this->movingLimit = movingLimit;
	this->activeArea = activeArea;
	SetPosition((float)positionX, (float)positionY);
	init();
}

Bat::~Bat() {
	if (this->sprite != NULL) {
		for (auto i = this->sprite->begin(); i != this->sprite->end(); i++) {
			delete i->second;
			this->sprite->erase(i);
		}
		delete this->sprite;
	}
}
void Bat::UpdateActiveArea(float t) {
	if (state == DEAD && !isActive) {

		if (Player::GetInstance()->GetPosition().x >= activeArea.at(0)
			&& Player::GetInstance()->GetPosition().x <= activeArea.at(1)
			&& Player::GetInstance()->GetDirection() == RIGHT) {
			this->sprite->at(ENEMY_STATE::DEAD)->Reset();
			SetPosition(lastPos.x, lastPos.y);
			state = FOLLOW;
			if (direction == RIGHT) {
				this->SetVeclocity(60.0f, 0);
			}
			if (direction == LEFT) {
				this->SetVeclocity(-60.0f, 0);
			}
		}
		else {
			if (Player::GetInstance()->GetPosition().x >= activeArea.at(2)
				&& Player::GetInstance()->GetPosition().x <= activeArea.at(3)
				&& Player::GetInstance()->GetDirection() == LEFT) {
				this->sprite->at(ENEMY_STATE::DEAD)->Reset();
				SetPosition(lastPos.x, lastPos.y);
				state = FOLLOW;
				if (direction == RIGHT) {
					this->SetVeclocity(60.0f, 0);
				}
				if (direction == LEFT) {
					this->SetVeclocity(-60.0f, 0);
				}
			}
		}

	}
	if (state != DEAD && !isActive) {
		if (Player::GetInstance()->GetPosition().x >= activeArea.at(0)
			&& Player::GetInstance()->GetPosition().x <= activeArea.at(1)
			&& Player::GetInstance()->GetDirection() == LEFT) {
			isActive = true;
			direction = LEFT;
			this->SetVeclocity(-60.0f, 0);
			leftMoving = movingLimit.at(0);
			rightMoving = movingLimit.at(1);
		}
		else {
			if (Player::GetInstance()->GetPosition().x >= activeArea.at(2)
				&& Player::GetInstance()->GetPosition().x <= activeArea.at(3)
				&& Player::GetInstance()->GetDirection() == RIGHT) {
				isActive = true;
				direction = RIGHT;
				this->SetVeclocity(60.0f, 0);
				leftMoving = movingLimit.at(2);
				rightMoving = movingLimit.at(3);
			}
		}
	}
}

void Bat::Update(float t, vector<Object*>* objects) {
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
	if (this->isActive) {
		float k = 1.4 * sin(position.x / 5);
		veclocity.y = k / t;
		Object::Update(t);
		RECT rect = sprite->at(this->state)->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);
		sprite->at(this->state)->NextSprite(t);
		if (state != ENEMY_STATE::DEAD) {
			HandleCollision(objects);
			Player::GetInstance()->KillEnemy(this);
		}
		else {
			if (sprite->at(this->state)->GetIsComplete()) {
				sprite->at(this->state)->SetIndex(2);
				sprite->at(this->state)->SetScale(1.0f);
				isActive = false;
			}
			this->sprite->at(ENEMY_STATE::FOLLOW)->Reset();
			SetVx(0.0f);
		}
	}

}

void Bat::HandleCollision(vector<Object*> *object) {
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
			if (e->object->GetObjectType() == OBJECT_TYPE::MAIN_CHARACTER) {
				if (Player::GetInstance()->GetState() == JUMP_ATK) {
					state = ENEMY_STATE::DEAD;
					continue;
				}
				if (!Player::GetInstance()->GetWounded()) {
					Player::GetInstance()->Wounded(e->nx, e->ny, this, direction);
				}
			}
			Object::PlusPosition(this->deltaX, this->deltaY);
		}
	}

	for (UINT i = 0; i < coEvents->size(); i++) {
		delete coEvents->at(i);
	}
	coEventsResult->clear();
	delete coEvents;
	delete coEventsResult;
}

void Bat::Dead() {
	state = ENEMY_STATE::DEAD;
	SetVeclocity(0.0f, 0.0f);
	Object::PlusPosition(0, -3.0f);
	Player::GetInstance()->AddScore(this->score);
}

void Bat::ResetState() {
	this->isActive = false;
	if (this->state == DEAD) {
		this->sprite->at(ENEMY_STATE::DEAD)->Reset();
	}
	state = ENEMY_STATE::FOLLOW;
	SetPosition(lastPos.x, lastPos.y);
}

void Bat::Render() {
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

void Bat::SetState(ENEMY_STATE state) {
	this->state = state;
}
