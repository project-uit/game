#include "Eagle.h"
#include "Player.h"
#include "Debug.h"
#include <math.h>
Eagle::Eagle() {

}

void Eagle::init() {
	this->SetObjectType(EAGLE);
	this->position.z = 0.0f;
	this->isActive = false;
	objectHeight = objectWidth = 1;
	SetVeclocity(0.0f, 0.0f);
	top = bottom = 0;
	isCollidePlayer = false;
	state = FOLLOW;
	finishFly = 0;
	destination = 0;
	score = 300;
	time = 0;
	this->sprite = new  map<ENEMY_STATE, Sprite*>();
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FOLLOW,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_Eagle_follow, 2, 0.075f)));
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY_DIE_FIRE), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 3, 0.03f)));
}

Eagle::Eagle(vector<int> activeArea, int positionX, int positionY) {
	this->activeArea = activeArea;
	SetPosition(positionX, positionY);
	init();
}

Eagle::~Eagle() {
	if (this->sprite != NULL) {
		for (auto i = this->sprite->begin(); i != this->sprite->end(); i++) {
			delete i->second;
			this->sprite->erase(i);
		}
		delete this->sprite;
	}
}

void Eagle::UpdatteActiveArea(float t) {
	
	if (!isActive) {
		
		if (Player::GetInstance()->GetPosition().x >= activeArea.at(0)
			&& Player::GetInstance()->GetPosition().x <= activeArea.at(1)
			&& Player::GetInstance()->GetDirection() == RIGHT
			&& activeArea.at(0) != 0
			&& activeArea.at(1) != 0) {
			isActive = true;
			direction = LEFT;
			SetVx(-200.0f);
		}
		else {
			if (Player::GetInstance()->GetPosition().x >= activeArea.at(2)
				&& Player::GetInstance()->GetPosition().x <= activeArea.at(3)
				&& Player::GetInstance()->GetDirection() == LEFT
				&& activeArea.at(2) != 0
				&& activeArea.at(3) != 0) {
				isActive = true;
				direction = RIGHT;
				SetVx(200.0f);
			}
		}
	}
	
}

void Eagle::FollowPlayer(float t) {
	
	if (direction == LEFT) {
		if (position.x < Player::GetInstance()->GetPosition().x) {
			direction = RIGHT;
		}
	}
	if (direction == RIGHT) {
		if (position.x > Player::GetInstance()->GetPosition().x) {
			direction = LEFT;
		}
	}
	int width = GetBoundingBox().right - GetBoundingBox().left;
	float dx = 0;
	RECT rect = Player::GetInstance()->GetBoundingBox();
	if (position.x > Player::GetInstance()->GetPosition().x) {
		dx = GetBoundingBox().left - rect.right;
	}
	else {
		dx = rect.left - GetBoundingBox().right;
	}
	if (veclocity.x < 0) {
		if (dx <= 10) {
			destination = Player::GetInstance()->GetPosition().x - 190.0f;
		}
		else if (dx <= 30 && dx > 10) {
			destination = Player::GetInstance()->GetPosition().x - 150.0f;
		}
		else if (dx <= 100 && dx > 30) {
			destination = Player::GetInstance()->GetPosition().x - 100.0f;
		}
		
		if (position.x - width < destination && dx < 75 && veclocity.x > -310) {
			SetVx(0);
			finishFly = 1;
		}
	}
	else if (veclocity.x > 0) {
		if (dx <= 10) {
			destination = Player::GetInstance()->GetPosition().x + 190.0f;
		}
		else if (dx <= 30 && dx > 10) {
			destination = Player::GetInstance()->GetPosition().x + 150.0f;
		}
		else if (dx <= 100 && dx > 30) {
			destination = Player::GetInstance()->GetPosition().x + 100.0f;
		}
		if (position.x + width > destination && dx < 75 && veclocity.x < 310) {
			SetVx(0);
			finishFly = 2;
		}
	}
	else {
		if (finishFly == 1 || finishFly == 2) {
			if (time >= 0.125f) {
				time = 0;
				finishFly = 0;
			}
			else {
				time += t;
				if (position.y > Player::GetInstance()->GetPosition().y + 10) {
					SetVy(65);
				}
			}
		}
	}
	if (finishFly == 0) {
		float vy = Player::GetInstance()->GetVeclocity().y;
		veclocity.y = vy * 0.5;
		float distanceX = Player::GetInstance()->GetPosition().x - position.x;
		float log = log10(abs((distanceX)) * 30 + 10);
		log = (exp(0.75 + log)) / 40;
		veclocity.x += distanceX < 0 ? log * -1 : log;
		float temp = (Player::GetInstance()->GetPosition().y + 2 - position.y);
		if (temp < 45 && temp > 0) {
			temp += 45;
		}
		temp = temp < 0 ? temp*0.87 : temp;
		veclocity.y += temp;
	}
}

void Eagle::Update(float t, vector<Object*>* object) {
	if (Player::GetInstance()->isFreezeTime() && isActive) {
		SetVeclocity(0, 0);
		Object::Update(t);
		HandleCollision(object);
		Player::GetInstance()->KillEnemy(this);
		if (state == DEAD) {
			sprite->at(this->state)->NextSprite(t);
			if (sprite->at(this->state)->GetIsComplete()) {
				sprite->at(this->state)->SetIndex(2);
				sprite->at(this->state)->SetScale(1.0f);
			}
			this->sprite->at(ENEMY_STATE::FOLLOW)->Reset();
			SetVx(0.0f);
		}
		return;
	}
	UpdatteActiveArea(t);
	if (isActive) {
		Object::Update(t);
		RECT rect = sprite->at(this->state)->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);
		sprite->at(this->state)->NextSprite(t);
		if (state != DEAD) {
			HandleCollision(object);
			FollowPlayer(t);
			Player::GetInstance()->KillEnemy(this);
		}
		else {
			if (sprite->at(this->state)->GetIsComplete()) {
				sprite->at(this->state)->SetIndex(2);
				sprite->at(this->state)->SetScale(1.0f);
				state = DEAD;
				SetPosition(lastPos.x, lastPos.y);
			}
		}
		
	}
}

void Eagle::Dead() {
	state = DEAD;
	SetVeclocity(0.0f, 0.0f);
	objectHeight = objectWidth = 1;
	time = 0;
	destination = 0;
	Player::GetInstance()->AddScore(this->score);
}

void Eagle::HandleCollision(vector<Object*>* object) {
	vector<CollisionHandler*>* coEvents = new vector<CollisionHandler*>();
	vector<CollisionHandler*>* coEventsResult = new vector<CollisionHandler*>();
	coEvents->clear();
	if (isActive) {
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
				if (!Player::GetInstance()->GetWounded()) {
					if (Player::GetInstance()->GetState() == JUMP_ATK) {
						state = ENEMY_STATE::DEAD;
					}
					else {
						Player::GetInstance()->Wounded(e->nx, e->ny, this, direction);
					}
				}
				if (e->nx != 0) {
					Object::PlusPosition(this->deltaX, 0.0f);
				}
				if (e->ny != 0) {
					Object::PlusPosition(0.0f, this->deltaY);
				}
				continue;
			}
			else if (e->object->GetObjectType() == OBJECT_TYPE::SQUARE) {
				if (e->nx != 0) {
					Object::PlusPosition(this->deltaX, 0.0f);
				}
				if (e->ny != 0) {
					Object::PlusPosition(0.0f, this->deltaY);
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

void Eagle::Render() {
	if (isActive) {
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

void Eagle::ResetState() {
	if (isActive) {
		isActive = false;
		SetPosition(lastPos.x, lastPos.y);
		SetVx(0.0f);
		SetVy(0.0f);
		if (this->state == DEAD) {
			this->sprite->at(ENEMY_STATE::DEAD)->Reset();
			sprite->at(this->state)->SetScale(1.0f);
		}
		state = ENEMY_STATE::FOLLOW;
		objectHeight = objectWidth = 1;
	} 
}
