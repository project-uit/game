#include "Boss.h"
#include "Player.h"
#include "Debug.h"
Boss::Boss() {
	objectType = OBJECT_TYPE::BOSS;
	hp = 16;
	isOnGround = true;
	SetVx(0.0f);
	SetVy(0.0f);
	SetPosition(187.0f, 122.0f);
	position.z = 0.0f;
	isActive = true;
	direction = LEFT;
	count = 0;
	timeHurt = 0;
	throwBoom = false;
	score = 6100;
	right = 188.0f;
	left = 29.0f;
	state = ENEMY_STATE::HIGH_JUMP;
	this->sprite = new  map<ENEMY_STATE, Sprite*>();
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::HIGH_JUMP,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_3_ENEMY_BOSS, 2, 0.09f)));
	explosion = new vector<Sprite*>();
	explosion->reserve(4);
	for (int i = 0; i < 4; i++) {
		Sprite* sprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_3_EXPLOSION_BOSS, 2, 0.06f);
		explosion->push_back(sprite);
	}
	//this->sprite
	//	->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
	//		new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 2, 0.04f)));
}

Boss::~Boss() {
	if (this->sprite != NULL) {
		for (auto i = this->sprite->begin(); i != this->sprite->end(); i++) {
			delete i->second;
			this->sprite->erase(i);
		}
		delete this->sprite;
	}
	for (int i = 0; explosion->size(); i++) {
		delete explosion->at(i);
	}
	explosion->clear();
	delete explosion;
}

void Boss::Update(float t, vector<Object*> * object) {
	if (isActive) {
		if (count % 3 == 0 && count > 0 && throwBoom == false && isOnGround) {
			throwBoom = true;
			for (int i = 0; i < BOOM_NUMBERS; i++) {
				boom[i].SetActive(true);
				if (direction == LEFT) {
					boom[i].SetVx(120.0f);
					boom[i].SetPosition(position.x, position.y + 6 + i * 16);
				}
				else {
					boom[i].SetVx(-120.0f);
					boom[i].SetPosition(position.x + 23, position.y + 6 + i * 16);
				}
			}
		}
		if (throwBoom) {
			bool flag = true;
			for (int i = 0; i < BOOM_NUMBERS; i++) {
				boom[i].Update(t, 0.1 + 0.125*i, object);
				if (boom[i].IsOutCamera()) {
					flag = false;
					boom[i].SetActive(false);
					boom[i].ResetState();
				}
				throwBoom = flag || boom[i].GetActive();
			}
		}
		
		Object::Update(t);
		SetLastPos(GetPosition());
		this->veclocity.y += GRAVITY * t;
		RECT rect = sprite->at(this->state)->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);
		if (isOnGround) {
			deltaX = 0.0f;
			SetVx(0.0f);
			/*186.847412*/
		}
		HandleCollision(object);
		if (isOnGround) {
			sprite->at(this->state)->SetIndex(0);
			if (time >= 0.2f) {
				isOnGround = false;
				time = 0.0f;
				float tempVy = 510.0f;
				SetVy(-tempVy);
				count++;
				/*float vy = (50 / 2678)*veclocity.x*veclocity.x - 3.78*veclocity.x - 263;
				if (vy > 0) vy *= -1;*/
				
			}
			else {
				time += t;
				//Tránh boss bị lệch vị trí khi nhảy qua nhảy lại
				if (position.x >= 27 && position.x < 33) {
					position.x = 29.89f;
				}
				if (position.x >= 185 && position.x < 187) {
					position.x = 187;
				}
			}
		}
		else {
			if (veclocity.y < 0) {
				if (count % 2 == 0) {
					SetVx(220.0f);
					direction = RIGHT;
				}
				else {
					SetVx(-220.0f);
					direction = LEFT;
				}
			}
			sprite->at(this->state)->SetIndex(1);
		}		
		if (Game::AABB(Player::GetInstance()->GetKatana()->GetBoundingBox(), GetBoundingBox())) {
			if (timeHurt >= 0.06f) {
				timeHurt = 0;
				hp--;
			}
			else {
				timeHurt += t;
			}
		}
		if (Player::GetInstance()->GetWeapon()) {
			if (Player::GetInstance()->GetWeapon()->GetObjectType() != CIRCLE_FIRE) {
				if (Game::AABB(Player::GetInstance()->GetWeapon()->GetBoundingBox(), GetBoundingBox())) {
					hp--;
					Player::GetInstance()->GetWeapon()->SetActive(false);
				}
			}
			else {
				Weapon* weapon = Player::GetInstance()->GetWeapon();
				for (int i = 0; i < CIRCLE_FIRE_NUMBER; i++) {
					if (Game::AABB(weapon[i].GetBoundingBox(), GetBoundingBox())) {
						hp--;
						weapon[i].SetActive(false);
						break;
					}
				}
			}
		}
		if (hp == 0) {
			isActive = false;
			for (int i = 0; i < BOOM_NUMBERS; i++) {
				boom[i].SetActive(false);
			}
			Player::GetInstance()->AddScore(score);
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			explosion->at(i)->NextSprite(t);
		}
	}
}

void Boss::HandleCollision(vector<Object*> *object) {
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
		this->PlusPosition(0.0f, min_ty*this->deltaY + ny * 0.2f);	
		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			if (e->object->GetObjectType() == OBJECT_TYPE::SQUARE) {
				if (e->ny < 0) {
					isOnGround = true;
					SetVx(0.0f);
					SetVy(0.0f);
				}
				continue;
			}
			if (e->object->GetObjectType() == OBJECT_TYPE::MAIN_CHARACTER) {
				if (e->nx != 0) {
					PlusPosition(deltaX, 0.0f);
				}
				if (e->ny != 0) {
					PlusPosition(deltaX, 0.0f);
				}
				if (!Player::GetInstance()->GetWounded()) {
					Player::GetInstance()->Wounded(e->nx, e->ny, this, direction);
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

void Boss::ResetState() {

}

void Boss::Render() {
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
	if (throwBoom) {
		for (int i = 0; i < BOOM_NUMBERS; i++) {
			boom[i].Render();
		}
	}
	if (!isActive) {
		for (int i = 0; i < 4; i++) {
			switch (i) {
			case 0:
				explosion->at(i)->DrawSprite(D3DXVECTOR3(position.x - 12, position.y, 0), true);
				break;
			case 1:
				explosion->at(i)->DrawSprite(D3DXVECTOR3(position.x + 13 * i, position.y + 5 , 0), true);
				break;
			case 2:
				explosion->at(i)->DrawSprite(D3DXVECTOR3(position.x + - 12, position.y + 25, 0), true);
				break;
			case 3:
				explosion->at(i)->DrawSprite(D3DXVECTOR3(position.x + 13 * (i - 2), position.y + 30, 0), true);
				break;
			}
		}
	} 
}

int Boss::GetHp() {
	return hp;
}

