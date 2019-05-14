#include "Player.h"
#include "Camera.h"
#include "Square.h"
#include "SoldierSword.h"
#include "BigShuriken.h"
#include <iomanip> 
#include "Boss.h"

Player* Player::_instance = NULL;

Player::Player()
{
	this->SetObjectType(MAIN_CHARACTER);
	this->SetState(PLAYER_STATE::STAND);
	this->SetLastState(PLAYER_STATE::STAND);
	this->SetDirection(DIRECTION::RIGHT);
	this->objectWidth = 32;
	this->objectHeight = 32;
	this->SetPosition(1121, 100); //1121 150
	this->SetLastPos({ -1.0f, -1.0f, 0 });
	this->SetVeclocity(0.0f, 0.0f);
	this->position.z = 0.0f;
	this->acceleratorX = 0.0f;
	this->score = 100;
	isOnGround = false;
	isWounded = false;
	katana = new Katana();
	weapon = new BigShuriken();
	time = 0;
	count = 0;
	lifePoint = 3;
	hp = 16;
	this->sprite = new  map<PLAYER_STATE, Sprite*>();
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::STAND,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_MAIN_STAND, 1, 0.0f)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::RUN,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_MAIN_RUN, 3, 0.055f)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::SIT,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_SIT, 1, 0.02)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::SIT_ATK,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_SIT_ATK, 3, 0.06f)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::STAND_ATK,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_STAND_ATK, 3, 0.07f)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::JUMP,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_JUMP, 4, 0.0675f)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::WOUNDED,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_WOUNDED, 1, 0.0f)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::DIE,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_WOUNDED, 1, 0.0f)));
}

Player::~Player()
{
	if (this->sprite != NULL) {
		for (auto i = this->sprite->begin(); i != this->sprite->end(); i++) {
			delete i->second;
			this->sprite->erase(i);
		}
		delete this->sprite;
	}
	if (katana) {
		delete katana;
	}
}

bool Player::GetWounded() {
	return isWounded;
}

void Player::SetDirection(DIRECTION direct) {
	this->direction = direct;
}

DIRECTION Player::GetDirection() {
	return this->direction;
}

PLAYER_STATE Player::GetState()
{
	return this->state;
}

Katana* Player::GetKatana() {
	return katana;
}

Weapon* Player::GetWeapon() {
	return weapon;
}

void Player::SetState(PLAYER_STATE value)
{
	this->state = value;
}

void Player::ResetSpriteState(PLAYER_STATE state) {
	this->sprite->at(state)->Reset();
	this->last_state = this->state;
}
PLAYER_STATE Player::GetLastState() {
	return this->last_state;
}
void Player::SetLastState(PLAYER_STATE last_state) {
	this->last_state = last_state;
}

Sprite* Player::GetCurrentSprite() {
	return this->sprite->at(this->state);
}

void Player::ResetAllSprites()
{
	if (this->sprite != NULL) {
		for (auto i = this->sprite->begin(); i != this->sprite->end(); i++) {
			i->second->Reset();
		}
	}
}

void Player::SetAcceleratorX(float x) {
	this->acceleratorX = x;
}

bool Player::GetStateActive()
{
	return this->isActive;
}

void Player::SetOnGround(bool ground) {
	this->isOnGround = ground;
}

bool Player::GetOnGround() {
	return this->isOnGround;
}

void Player::Reset(float x, float y)
{
	this->isActive = true;
	this->SetLastPos(this->GetPosition());
	this->SetPosition(x, y);
}

void Player::Update(float t, vector<Object*>* object)
{
	if (weapon) {
		//if (Game::AABB(weapon->GetBoundingBox(), GetBoundingBox())) {
		//	weapon->SetActive(false);
		//}
		weapon->Update(t, object);
	}
	if (state == PLAYER_STATE::DIE && lifePoint > 0) {
		SetPosition(20.0f, 100.0f);
		state = JUMP;
		direction = RIGHT;
		hp = 16;
		return;
	}
	if (state != PLAYER_STATE::DIE) {

		if (this->state == PLAYER_STATE::RUN) {
			if (this->veclocity.x >= PLAYER_VELOCITY_X) {
				this->veclocity.x = PLAYER_VELOCITY_X;
			}
			if (this->veclocity.x <= -PLAYER_VELOCITY_X) {
				this->veclocity.x = -PLAYER_VELOCITY_X;
			}
		}

		if (this->state == PLAYER_STATE::JUMP) {

			if (this->veclocity.x >= PLAYER_VELOCITY_X) {
				this->veclocity.x = PLAYER_VELOCITY_X / 3.5f;
			}
			if (this->veclocity.x <= -PLAYER_VELOCITY_X) {
				this->veclocity.x = -PLAYER_VELOCITY_X / 3.5f;
			}
		}

		if (this->state == PLAYER_STATE::STAND) {
			acceleratorX = 0;
			veclocity.x = 0;
		}

		if (this->state == PLAYER_STATE::STAND_ATK && this->sprite->at(this->state)->GetIndex() == 1) {
			RECT rect;
			if (direction == RIGHT) {
				rect.left = position.x + 26;
			}
			else {
				rect.left = position.x - 24;
			}
			rect.right = rect.left + 13;
			rect.top = position.y + 8;
			rect.bottom = rect.top + 6;
			katana->SetBoundingBox(rect);
		}
		else if (this->state == PLAYER_STATE::SIT_ATK && this->sprite->at(this->state)->GetIndex() == 1) {
			RECT rect;
			if (direction == RIGHT) {
				rect.left = position.x + 26;
			}
			else {
				rect.left = position.x - 24;
			}
			rect.right = rect.left + 13;
			rect.top = position.y + 15;
			rect.bottom = rect.top + 6;
			katana->SetBoundingBox(rect);
		}
		else {
			katana->Reset();
		}
		if (count == 30) {
			count = 0;
			time = 0;
			isWounded = false;
		}
		if (isWounded) {
			if (time >= 0.02f) {
				time = 0;
				count++;
			}
			else {
				time += t;
			}
		}

		Object::Update(t);
		SetLastPos(GetPosition());

		RECT rect = this->sprite->at(this->state)->GetBoudingBoxFromCurrentSprite();

		Object::updateBoundingBox(rect);

		this->veclocity.y += GRAVITY;
		this->veclocity.x += acceleratorX;

		if (this->last_state != this->state) {
			ResetSpriteState(this->last_state);
		}
		this->sprite->at(this->state)->NextSprite(t);
		//if (this->sprite->at(this->state)->GetCount() > 2) {
		//	this->sprite->at(this->state)->SetIndex(0);
		//}
		if (this->sprite->at(this->state)->GetIsComplete() && state == PLAYER_STATE::STAND_ATK) {
			state = PLAYER_STATE::STAND;
		}

		if (this->sprite->at(this->state)->GetIsComplete() && state == PLAYER_STATE::SIT_ATK) {
			state = PLAYER_STATE::SIT;
		}

		HandleCollision(object);
		if (hp == 0 || !Game::AABB(GetBoundingBox(), Camera::GetInstance()->GetRECTx())) {
			state = PLAYER_STATE::DIE;
			lifePoint--;
			isWounded = false;
			time = 0;
			SetVx(0.0f);
			count = 0;
			return;
		}
	}
}

void Player::HandleCollision(vector<Object*> *object) {

	vector<CollisionHandler*>* coEvents = new vector<CollisionHandler*>();
	vector<CollisionHandler*>* coEventsResult = new vector<CollisionHandler*>();
	coEvents->clear();

	if (this->state != PLAYER_STATE::DIE) {
		Object::CalcPotentialCollisions(object, coEvents);
	}
	//DebugOut((wchar_t *)L"OnGround: %d\n", isOnGround);
	if (coEvents->size() == 0) {
		Object::PlusPosition(this->deltaX, this->deltaY);
	}
	else {
		float min_tx, min_ty, nx = 0, ny;
		this->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		this->PlusPosition(min_tx * this->deltaX + nx * 0.2f, min_ty*this->deltaY + ny*0.2f);
		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			if (!e->object->GetActive()) {
				Object::PlusPosition(deltaX, deltaY);
				continue;
			}
			if (e->object->GetObjectType() == OBJECT_TYPE::SQUARE) {
				if (e->ny < 0) {	
					this->SetVy(0.0f);
					isOnGround = true;
					if (state == PLAYER_STATE::WOUNDED) {
						this->PlusPosition(0.0f, -1 * 16.0f);
						state = PLAYER_STATE::STAND;
						SetVx(0.0f);
						acceleratorX = 0;
					}
					//Khi nhân vật đáp đất sẽ tạo 1 phản lực lại 
					if (isOnGround && state == PLAYER_STATE::JUMP) {
						state = PLAYER_STATE::STAND;
						this->PlusPosition(0, -1 * 20.0f);
						SetVx(0.0f);
						acceleratorX = 0;
					}
				}
				if (e->ny > 0) {
					Object::PlusPosition(0.0f, this->deltaY);
				}
				if (e->nx != 0) {
					Object::PlusPosition(this->deltaX, 0.0f);
				}
				continue;
			}
			if (e->object->GetObjectType() == OBJECT_TYPE::SOLDIER_SWORD
				|| e->object->GetObjectType() == OBJECT_TYPE::PANTHER
				|| e->object->GetObjectType() == OBJECT_TYPE::BOSS) {
				if (Wounded(e, e->object->GetObjectDirection())) {
					continue;
				}
			}
			if (e->object->GetObjectType() == OBJECT_TYPE::FOOD) {
				Object::PlusPosition(this->deltaX, this->deltaY);
			}
		}
	}

	for (UINT i = 0; i < coEvents->size(); i++) {
		delete coEvents->at(i);
	}

	delete coEvents;
	delete coEventsResult;
}

void Player::Render()
{
	switch (this->direction) {
	case RIGHT:
		if (count % 3 == 0) {
			if (state == PLAYER_STATE::JUMP) {
				this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true, -4);
			}
			else {
				this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true);
			}
			break;
		}
	case LEFT:
		if (count % 3 == 0) {
			if (state == PLAYER_STATE::STAND_ATK) {
				this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false, -24, 0);
			}
			else if (state == PLAYER_STATE::SIT_ATK) {
				this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false, -24, 0);
			}
			else if (state == PLAYER_STATE::JUMP) {
				this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false, -4, 0);
			}
			else {
				this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false);
			}
		}
		break;
	default:
		break;
	}
	if (weapon) {
		weapon->Render();
	}
}

void Player::UseWeapon() {
	if (weapon) {
		if (weapon->GetActive() == false) {
			weapon->SetActive(true);
			if (weapon->GetObjectType() == OBJECT_TYPE::SMALL_SHURIKEN) {
				if (this->direction == LEFT) {
					weapon->SetPosition(position.x, position.y + 10);
					weapon->SetVx(-200.0f);
				}
				else {
					weapon->SetPosition(position.x + 10, position.y + 10);
					weapon->SetVx(200.0f);
				}
			}
			if (weapon->GetObjectType() == OBJECT_TYPE::BIG_SHURIKEN) {
				BigShuriken *bigShuriken = dynamic_cast<BigShuriken *>(weapon);
				bigShuriken->SetOrbitMoving(isOnGround);
				if (this->direction == LEFT) {
					bigShuriken->SetPosition(position.x - 8, position.y + 7);
					bigShuriken->SetVx(-400.0f);
				}
				else {
					bigShuriken->SetPosition(position.x + 15, position.y + 7);
					bigShuriken->SetVx(400.0f);
				}
			}
		}
	}
}

int Player::GetLifePoint() {
	return lifePoint;
}

int Player::GetItemPoint() {
	return itemPoint;
}

int Player::GetHp() {
	return hp;
}

void Player::SetHp(int hp) {
	this->hp = hp;
}

float Player::GetAcceleratorX() {
	return acceleratorX;
}

string Player::GetScoreString() {
	std::stringstream Score;
	Score << std::setw(6) << std::setfill('0') << this->score;
	return Score.str();
}

void Player::ResetState() {

}

bool Player::Wounded(CollisionHandler* e, DIRECTION direction) {
	acceleratorX = 0.0f;
	Object* obj = e->object;
	if (e->nx != 0) {
		if (isWounded) {
			Object::PlusPosition(deltaX, 0.0f);
			return true;
		}
		else {
			state = PLAYER_STATE::WOUNDED;
			SetVy(-230.0f);
			if (direction == LEFT) {
				SetVx(-100.0f);
			}
			else {
				SetVx(100.0f);
			}
		}
	}
	if (e->ny != 0) {
		if (isWounded) {
			Object::PlusPosition(0.0f, deltaY);
			return true;
		}
		else {
			state = PLAYER_STATE::WOUNDED;
			SetVy(-230.0f);
			if (direction == LEFT) {
				SetVx(-100.0f);
			}
			else {
				SetVx(100.0f);
			}
		}
	}
	isOnGround = false;
	isWounded = true;
	hp--;
	return false;
}




