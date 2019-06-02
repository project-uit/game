#include "Player.h"
#include "Camera.h"
#include "Sound.h"
#include "Square.h"
#include "SoldierSword.h"
#include "BigShuriken.h"
#include <iomanip> 
#include "Boss.h"
#include "GameDebugDraw.h"
#include "CircleFire.h"
#include "Grid.h"
#include "HUD.h"

Player* Player::_instance = NULL;
//GameDebugDraw* draw12;
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
	//draw12 = new GameDebugDraw();
	isOnGround = false;
	isWounded = false;
	katana = new Katana();
	alphaEndPoint = false;
	//weapon = new CircleFire[3];
	time = 0;
	count = 0;
	borderBot = 0;
	lifePoint = 3;
	itemPoint = 0;
	freezeTime = 0;
	alphaEndPoint = 255;
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
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_JUMP, 4, 0.0475f)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::WOUNDED,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_WOUNDED, 1, 0.0f)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::USE_WEAPON,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_WEAPON, 3, 0.07f)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::DIE,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_WOUNDED, 1, 0.0f)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::JUMP_ATK,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_JUMP_ATK, 4, 0.0475f)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::CLIMB,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_CLIMB, 2, 0.09f)));
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
	if (food) {
		delete food;
	}
	if (currentLadder) {
		delete currentLadder;
	}
	if (currentRock) {
		delete currentRock;
	}
	if (weapon) {
		if (weapon->GetObjectType() == CIRCLE_FIRE) {
			delete[] weapon;
		}
		else {
			delete weapon;
		}
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

Food* Player::GetFood() {
	return food;
}

void Player::AddScore(int score) {
	this->score += score;
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
	if (endStage) {
		SetVeclocity(0.0f, 0.0f);
		if (time >= 0.2f) {
			time = 0;
			MinusAlphaEndPoint();
			if (alphaEndPoint == 0) {
				endStage = false;
			}
		}
		else {
			time += t;
		}
		return;
	}
	if (weapon) {
		if (weapon->GetObjectType() == CIRCLE_FIRE) {
			for (int i = 0; i < CIRCLE_FIRE_NUMBER; i++) {
				CircleFire* circleFire = dynamic_cast<CircleFire*>(&weapon[i]);
				circleFire->Update(t, i, object);
				if (circleFire->GetActive() == false) {
					weapon->SetActive(false);
				}
			}
		}
		else {
			if (weapon->GetObjectType() == BIG_SHURIKEN && Game::AABB(weapon->GetBoundingBox(), GetBoundingBox())) {
				weapon->SetActive(false);
			}
			weapon->Update(t, object);
		}
	}
	if (state == PLAYER_STATE::DIE && lifePoint >= 0) {
		SetPosition(20.0f, 100.0f);
		state = JUMP;
		direction = RIGHT;
		hp = 16;
		freezeTime = 0;
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

		if (this->state == PLAYER_STATE::CLIMB) {
			if (isOnLadder) {
				if (veclocity.y == 0) {
					if (GetBoundingBox().top < currentLadder->GetBoundingBox().top - 15 && isClimbMoving) {
						this->sprite->at(this->state)->NextSprite(t);
					}
				}

				if (veclocity.y < 0) {
					if (GetBoundingBox().top < currentLadder->GetBoundingBox().top - 15) {
						SetVeclocity(0, 0);
					}
					else {
						this->sprite->at(this->state)->NextSprite(t);
					}
				}

				if (veclocity.y > 0) {
					if (GetBoundingBox().bottom - 10 > currentLadder->GetBoundingBox().bottom) {
						SetVeclocity(0, 0);
					}
					else {
						this->sprite->at(this->state)->NextSprite(t);
					}
				}
			}

			if (isOnRock) {
				SetVeclocity(0, 0);
			}
		}

		if (this->state == PLAYER_STATE::STAND_ATK && this->sprite->at(this->state)->GetIndex() == 1) {
			RECT rect;
			if (direction == RIGHT) {
				rect.left = position.x + 10;
			}
			else {
				rect.left = position.x - 24;
			}
			rect.right = rect.left + 30;
			rect.top = position.y + 8;
			rect.bottom = rect.top + 10;
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
		if (isWounded) {
			if (time >= 0.02f) {
				time = 0;
				count++;
			}
			else {
				time += t;
			}
		}
		if (count == 19) {
			count = 0;
			time = 0;
			isWounded = false;
		}
		Object::Update(t);

		SetLastPos(GetPosition());

		RECT rect = this->sprite->at(this->state)->GetBoudingBoxFromCurrentSprite();

		Object::updateBoundingBox(rect);
		if (GetBoundingBox().bottom > borderBot + 6 && state != PLAYER_STATE::CLIMB) {
			state = PLAYER_STATE::JUMP;
			isOnGround = false;
		}

		if (this->last_state != this->state) {
			ResetSpriteState(this->last_state);
		}

		if (!isOnLadder && !isOnRock) {
			this->sprite->at(this->state)->NextSprite(t);
			this->veclocity.y += GRAVITY * t;
			this->veclocity.x += acceleratorX;
		}

			/*if (this->sprite->at(this->state)->GetCount() > 2) {
				this->sprite->at(this->state)->SetIndex(0);
			}*/
		if (this->sprite->at(this->state)->GetIsComplete()
			&& (state == PLAYER_STATE::STAND_ATK || state == PLAYER_STATE::USE_WEAPON)) {
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
			itemPoint = itemPoint / 2;
			if (weapon) {
				if (weapon->GetObjectType() == CIRCLE_FIRE) {
					delete[] weapon;
				}
				else {
					delete weapon;
				}
				weapon = NULL;
			}
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
	if (coEvents->size() == 0) {
		Object::PlusPosition(this->deltaX, this->deltaY);
	}
	else {
		float min_tx, min_ty, nx = 0, ny;
		this->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		if (!isOnLadder && !isOnRock) {
			this->PlusPosition(min_tx * this->deltaX + nx * 0.2f, min_ty*this->deltaY + ny * 0.2f);
		}
		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			if (!e->object->GetActive()) {
				if (e->nx != 0) {
					Object::PlusPosition(deltaX, 0.0f);
				}
				if (e->ny != 0) {
					Object::PlusPosition(0.0f, deltaY);
				}
				continue;
			}
			if (e->object->GetObjectType() == OBJECT_TYPE::SQUARE) {
				if (state == PLAYER_STATE::CLIMB) {
					Object::PlusPosition(this->deltaX, this->deltaY);
					continue;
				}

				if (e->ny < 0) {
					this->SetVy(0.0f);
					isOnGround = true;
					isJumpClimb = false;
					borderBot = e->object->GetBoundingBox().top;
					if (state == PLAYER_STATE::WOUNDED) {
						//this->PlusPosition(0.0f, -1 * 16.0f);
						state = PLAYER_STATE::STAND;
						SetVx(0.0f);
						acceleratorX = 0;
					}
					//Khi nhân vật đáp đất sẽ tạo 1 phản lực lại 
					if (state == PLAYER_STATE::JUMP) {
						state = PLAYER_STATE::STAND;
						//this->PlusPosition(0, -1 * 20.0f);
						SetVx(0.0f);
						acceleratorX = 0;
					}
					if (state == PLAYER_STATE::JUMP_ATK) {
						state = PLAYER_STATE::STAND;
						//this->PlusPosition(0, -1 * 10.0f);
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

			if (e->object->GetObjectType() == OBJECT_TYPE::DESTINATION) {
				if (e->nx < 0) {
					endStage = true;
					time = 0;
				}
			}

			if (e->object->GetObjectType() == OBJECT_TYPE::LADDER) {
				bool climb = false;
				switch (direction)
				{
				case RIGHT:
					if (e->nx > 0) {
						directionClimb = DIRECTION::LEFT;
						climb = true;
					}
				case LEFT:
					if (e->nx < 0) {
						directionClimb = DIRECTION::RIGHT;
						climb = true;
					}
				}

				if (climb) {
					SetVeclocity(NO_VELOCITY, NO_VELOCITY);
					currentLadder = dynamic_cast<Ladder*>(e->object);
					state = PLAYER_STATE::CLIMB;
					direction = directionClimb;
					isOnLadder = true;
					isOnGround = false;
				}

				continue;
			}

			if (e->object->GetObjectType() == OBJECT_TYPE::BRICK) {
				if (e->nx != 0) {
					SetVeclocity(0, 0);
					acceleratorX = 0;
				}
				else {
					if (e->ny > 0) {
						PlusPosition(this->deltaX, this->deltaY);
					}
					else {
						if (e->ny < 0) {
							SetVx(0);
							acceleratorX = 0;
							state = PLAYER_STATE::STAND;
							isOnGround = true;
						}
					}
				}
			}

			if (e->object->GetObjectType() == OBJECT_TYPE::FOOD) {
				Food* food = dynamic_cast<Food*>(e->object);
				if (e->nx != 0) {
					Object::PlusPosition(this->deltaX, 0.0f);
					continue;
				}
				if (e->ny != 0) {
					Object::PlusPosition(0.0f, this->deltaY);
					continue;
				}
			}
			if (e->object->GetObjectType() == OBJECT_TYPE::SOLDIER_SWORD
				|| e->object->GetObjectType() == OBJECT_TYPE::PANTHER
				|| e->object->GetObjectType() == OBJECT_TYPE::WITCH
				|| e->object->GetObjectType() == OBJECT_TYPE::SOLIDER_GUN
				|| e->object->GetObjectType() == OBJECT_TYPE::SOLIDER_BAZOKA
				|| e->object->GetObjectType() == OBJECT_TYPE::BOSS
				|| e->object->GetObjectType() == OBJECT_TYPE::SOLIDER_RUN
				|| e->object->GetObjectType() == OBJECT_TYPE::BAT
				|| e->object->GetObjectType() == OBJECT_TYPE::EAGLE) {

				if (isWounded) {
					if (e->nx != 0) {
						Object::PlusPosition(deltaX, 0.0f);
					}
					if (e->ny != 0) {
						Object::PlusPosition(0.0f, deltaY);
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

void Player::Render()
{
	switch (this->direction) {
	case RIGHT:
		if (count % 2 == 0) {
			if (state == PLAYER_STATE::JUMP) {
				this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true, -1);
			}
			else if (state == PLAYER_STATE::JUMP_ATK) {
				this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true, -8);
			}
			else {
				this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true);
			}
			break;
		}
	case LEFT:
		if (count % 2 == 0) {
			if (state == PLAYER_STATE::STAND_ATK) {
				this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false, -24, 0);
			}
			else if (state == PLAYER_STATE::SIT_ATK) {
				this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false, -24, 0);
			}
			else if (state == PLAYER_STATE::JUMP) {
				this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false, -1, 0);
			}
			else if (state == PLAYER_STATE::USE_WEAPON) {
				this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false, -10, 0);
			}
			else if (state == PLAYER_STATE::JUMP_ATK) {
				this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false, -8, 0);
			}
			else {
				this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false);
			}
		}
		break;
	default:
		break;
	}

	//draw12->DrawRect(katana->GetBoundingBox(), Camera::GetInstance());
	if (weapon) {
		if (weapon->GetObjectType() == CIRCLE_FIRE) {
			for (int i = 0; i < CIRCLE_FIRE_NUMBER; i++) {
				weapon[i].Render();
			}
		}
		else {
			weapon->Render();
		}
	}
}

void Player::UseWeapon() {
	if (weapon) {
		if (weapon->GetActive() == false) {
			switch (weapon->GetObjectType())
			{
			case OBJECT_TYPE::SMALL_SHURIKEN:
				if (itemPoint >= MANA_POINT_SHURIKEN_SMALL) {
					Sound::GetInstance()->Play(SOUND_ATK_SMALL_SHURIKEN, false, 1);
					if (this->direction == LEFT) {
						weapon->SetPosition(position.x, position.y + 10);
						weapon->SetVx(-250.0f);
					}
					else {
						weapon->SetPosition(position.x + 10, position.y + 10);
						weapon->SetVx(250.0f);
					}
					weapon->SetActive(true);
					itemPoint -= MANA_POINT_SHURIKEN_SMALL;
				}
				break;
			case OBJECT_TYPE::BIG_SHURIKEN:
				if (itemPoint >= MANA_POINT_SHURIKEN_BIG) {
					Sound::GetInstance()->Play(SOUND_ATK_BIG_SHURIKEN, false, 1);
					if (this->direction == LEFT) {
						weapon->SetPosition(position.x - 20, position.y + 5);
						weapon->SetVx(-400.0f);
					}
					else {
						weapon->SetPosition(position.x + 30, position.y + 5);
						weapon->SetVx(400.0f);
					}
					weapon->SetActive(true);
					itemPoint -= MANA_POINT_SHURIKEN_BIG;
				}
				break;
			case OBJECT_TYPE::CIRCLE_FIRE:
				if (itemPoint >= MANA_POINT_FIRE) {
					Sound::GetInstance()->Play(SOUND_ATK_FIRE, false, 1);
					float vx, vy = -35.0f, posX = 0;
					if (this->direction == RIGHT) {
						vx = 280.0f;
						posX = 10;
					}
					else {
						vx = -280.0f;
						posX = -10;
					}
					for (int i = 0; i < CIRCLE_FIRE_NUMBER; i++) {
						weapon[i].SetActive(true);
						weapon[i].SetVx(vx);
						weapon[i].SetVy(vy);
						weapon[i].SetPosition(position.x + posX, position.y - i * 10 - 20);
					}
					weapon->SetActive(true);
					itemPoint -= MANA_POINT_FIRE;
				}
				break;
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

float Player::GetBorderBot() {
	return borderBot;
}

string Player::GetScoreString() {
	std::stringstream Score;
	Score << std::setw(6) << std::setfill('0') << this->score;
	return Score.str();
}

void Player::ResetState() {

}

bool Player::Wounded(float nx, float ny, Object* object, DIRECTION direction) {
	acceleratorX = 0.0f;
	SetVx(0.0f);

	if (nx != 0) {
		if (isWounded) {
			Object::PlusPosition(deltaX, 0.0f);
			return true;
		}
		else {
			if (state != PLAYER_STATE::CLIMB) {
				state = PLAYER_STATE::WOUNDED;
				SetVy(-245.0f);
				if (direction == LEFT) {
					if (this->direction == RIGHT) {
						SetVx(-110.0f);
					}
					if (this->direction == LEFT) {
						if (position.x > object->GetPosition().x) {
							SetVx(110.0f);
						}
						else {
							SetVx(-110.0f);
							this->direction = RIGHT;
						}
					}
				}

				if (direction == RIGHT) {
					if (this->direction == LEFT) {
						SetVx(110.0f);
					}
					if (this->direction == RIGHT) {
						if (position.x > object->GetPosition().x) {
							SetVx(110.0f);
							this->direction = LEFT;
						}
						else {
							SetVx(-110.0f);
						}
					}
				}
			}
		}
	}

	if (ny != 0) {
		if (isWounded) {
			Object::PlusPosition(0.0f, deltaY);
			return true;
		}
		else {
			if (state != PLAYER_STATE::CLIMB) {
				state = PLAYER_STATE::WOUNDED;
				SetVy(-245.0f);
				if (direction == LEFT) {
					SetVx(-110.0f);
				}
				else {
					SetVx(110.0f);
				}
			}
		}
	}
	isOnGround = false;
	isWounded = true;
	hp--;
	Sound::GetInstance()->Play(SOUND_WOUNDED, false, 1);
	return false;
}

void Player::KillEnemy(Object* object) {
	if (Game::AABB(katana->GetBoundingBox(), object->GetBoundingBox())) {
		object->Dead();
		return;
	}
	if (weapon) {
		if (weapon->GetObjectType() != CIRCLE_FIRE) {
			if (Game::AABB(weapon->GetBoundingBox(), object->GetBoundingBox())) {
				object->Dead();
				if (weapon->GetObjectType() == OBJECT_TYPE::SMALL_SHURIKEN) {
					weapon->SetActive(false);
				}
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				if (Game::AABB(weapon[i].GetBoundingBox(), object->GetBoundingBox())) {
					object->Dead();
					break;
				}
			}
		}
	}
}

void Player::SetClimbRock(float nx, float ny, Rock* rock) {
	if (state == PLAYER_STATE::JUMP || isWounded) {
		if (position.x >= 1155 && position.x <= 1244) {
			if (rock->GetIsCanClimbLeft() != rock->GetIsCanClimbRight()) {
				if (nx != 0) {
					Object::PlusPosition(this->deltaX, 0);
				}
				if (ny != 0) {
					Object::PlusPosition(0, this->deltaY);
				}
			}
		}

		if (nx != 0) {
			bool climb = false;
			if (nx < 0) {
				if (rock->GetIsCanClimbRight()) {
					SetVeclocity(NO_VELOCITY, NO_VELOCITY);
					directionClimb = DIRECTION::LEFT;
					direction = DIRECTION::LEFT;
					climb = true;
				}
			}
			else {
				if (nx > 0) {
					if (rock->GetIsCanClimbLeft()) {
						SetVeclocity(NO_VELOCITY, NO_VELOCITY);
						directionClimb = DIRECTION::RIGHT;
						direction = DIRECTION::RIGHT;
						climb = true;
					}
				}
			}

			if (climb) {
				acceleratorX = 0;
				state = PLAYER_STATE::CLIMB;
				isOnRock = true;
				isOnGround = false;
				currentRock = rock;
			}

			if (ny > 0) {
				state = PLAYER_STATE::STAND;
				isOnGround = true;
			}
		}
	}
}

void Player::JumpClimb(int KeyCode) {
	if ((directionClimb == DIRECTION::LEFT && KeyCode == DIK_RIGHT) ||
		(directionClimb == DIRECTION::RIGHT && KeyCode == DIK_LEFT)) {
		if (KeyCode == DIK_LEFT) {
			SetVeclocity(-75, -270);
			direction = DIRECTION::LEFT;
		}
		if (KeyCode == DIK_RIGHT) {
			SetVeclocity(75, -270);
			direction = DIRECTION::RIGHT;
		}
		Sound::GetInstance()->Play(SOUND_JUMP, false, 1);
		acceleratorX = 0;
		state = PLAYER_STATE::JUMP;
		isOnGround = false;
		isOnLadder = false;
		isOnRock = false;
		isJumpClimb = true;
	}
}

bool Player::GetIsJumpClimb() {
	return isJumpClimb;
}

void Player::DigestFood(Food* food, Sprite* sprite) {
	switch (food->GetType())
	{
	case FOOD_TYPE::ITEM_POINT_BLUE:
	case FOOD_TYPE::ITEM_POINT_RED:
		itemPoint += food->GetScore();
		break;
	case FOOD_TYPE::VASE_BLUE:
	case FOOD_TYPE::VASE_RED:
		score += food->GetScore();
		break;
	case FOOD_TYPE::TIMER:
		freezeTime = 4;
		break;
	case FOOD_TYPE::FIRE:
		if (weapon) {
			delete weapon;
			weapon = NULL;
		}
		weapon = new CircleFire[CIRCLE_FIRE_NUMBER];
		HUD::GetInstance()->SetSkill(sprite);
		break;
	case FOOD_TYPE::SHURIKEN_BLUE:
		if (weapon) {
			if (weapon->GetObjectType() == CIRCLE_FIRE) {
				delete[] weapon;
			}
			else {
				delete weapon;
			}
			weapon = NULL;
		}
		
		weapon = new SmallShuriken();
		HUD::GetInstance()->SetSkill(sprite);
		break;
	case FOOD_TYPE::SHURIKEN_RED:
		if (weapon) {
			if (weapon->GetObjectType() == CIRCLE_FIRE) {
				delete[] weapon;
			}
			else {
				delete weapon;
			}
			weapon = NULL;
		}
		weapon = new BigShuriken();
		HUD::GetInstance()->SetSkill(sprite);
		break;
	case FOOD_TYPE::MANA:
		break;
	default:
		break;
	}
}

void Player::IntersectPlayer(Object* object, DIRECTION direction) {
	float nx = 0, ny = 0;
	RECT playerRECT = GetBoundingBox();
	RECT rect = object->GetBoundingBox();
	if (!isWounded) {
		if (Game::AABB(playerRECT, rect)) {
			if (playerRECT.right >= rect.left && playerRECT.left < rect.left) {
				//Chạm trái của enemy
				nx = 1;
			}
			if (playerRECT.right > rect.right && playerRECT.left <= rect.right) {
				//Chạm phải của enemy
				nx = -1;
			}
			Wounded(nx, ny, object, direction);
		}
	}
}

void Player::SetClimbMoving(bool flag) {
	isClimbMoving = flag;
}

float Player::GetFreezeTime() {
	return freezeTime;
}

void Player::MinusFreezeTime() {
	freezeTime--;
	if (freezeTime < 0) freezeTime = 0;
}

bool Player::isFreezeTime() {
	if (freezeTime) return true;
	return false;
}

int Player::GetAlphaEndPoint() {
	return alphaEndPoint;
}

void Player::SetAlphaEndPoint(int alpha) {
	this->alphaEndPoint = alpha;
}

void Player::MinusAlphaEndPoint() {
	alphaEndPoint -= 25;
	if (alphaEndPoint < 0) alphaEndPoint = 0;
}

void Player::Restart(float x, float y) {
	SetLastPos({ -1.0f, -1.0f, 0 });
	SetPosition(x, y);
	hp = 16;
	alphaEndPoint = 255;
	endStage = false;
	SetVx(0.0f);
	state = STAND;
}