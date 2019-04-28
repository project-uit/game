#include "Player.h"
#include "Camera.h"
#include "Square.h"
#include "SoldierSword.h"

Player* Player::_instance = NULL;

Player::Player()
{
	this->SetObjectType(MAIN_CHARACTER);
	this->SetState(PLAYER_STATE::STAND);
	this->SetLastState(PLAYER_STATE::STAND);
	this->SetDirection(DIRECTION::RIGHT);
	this->objectWidth = 32;
	this->objectHeight = 32;
	this->SetPosition(150, 100);
	this->SetLastPos({ -1.0f, -1.0f, 0 });
	this->SetVeclocity(0.0f, 0.0f);
	this->position.z = 0.0f;
	this->acceleratorX = 0.0f;
	isOnGround = false;
	this->sprite = new  map<PLAYER_STATE, Sprite*>();
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::STAND,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_MAIN_STAND, 1, 0.0f)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::RUN,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_MAIN_RUN, 3, 0.1f)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::SIT,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_SIT, 1, 0.02)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::SIT_ATK,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_SIT_ATK, 3, 0.06)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::STAND_ATK,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_STAND_ATK, 3, 0.06)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::JUMP,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_JUMP, 4, 0.0615)));
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
			this->veclocity.x = PLAYER_VELOCITY_X/3.5f;
		}
		if (this->veclocity.x <= -PLAYER_VELOCITY_X) {
			this->veclocity.x = -PLAYER_VELOCITY_X/3.5f;
		}
	}

	if (this->state == PLAYER_STATE::STAND) {
		acceleratorX = 0;
		veclocity.x = 0;
	}
	
	Object::Update(t);
	SetLastPos(D3DXVECTOR3(position.x, position.y, 0.0f));
	RECT rect = this->sprite->at(this->state)->GetBoudingBoxFromCurrentSprite();

	Object::updateBoundingBox(rect);

	this->veclocity.y += GRAVITY;
	this->veclocity.x += acceleratorX;

	if (this->last_state != this->state) {
		ResetSpriteState(this->last_state);
	}
	
	this->sprite->at(this->state)->NextSprite(t);
	//if (this->sprite->at(this->state)->GetCount() > 2) {
	//	this->sprite->at(this->state)->SetIndex(2);
	//}
	if (this->sprite->at(this->state)->GetIsComplete() && state == PLAYER_STATE::STAND_ATK) {
		state = PLAYER_STATE::STAND;
	}

	if (this->sprite->at(this->state)->GetIsComplete() && state == PLAYER_STATE::SIT_ATK) {
		state = PLAYER_STATE::SIT;
	}

	if (state == PLAYER_STATE::JUMP && isOnGround) {
		//khi đáp đất tọa độ y cần dời lên lại để khi vẽ nhân vật trạng thái stand đảm bảo trên bounding box của mặt đất
		if (state != PLAYER_STATE::RUN) {
			state = PLAYER_STATE::STAND;
			this->PlusPosition(0, -8.96f);
			SetVx(0.0f);
			acceleratorX = 0;
		}
		
	}
	
	HandleCollision(object);
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
		/*this->PlusPosition(min_tx * this->deltaX + nx * 0.4f, min_ty*this->deltaY + ny*0.4f);*/

		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			if (dynamic_cast<Square *>(e->object)) {
				if (e->ny < 0) {				
					this->SetVy(0.0f);
					isOnGround = true;
				}
			}
			if (e->object->GetObjectType() == OBJECT_TYPE::SOLDIER_SWORD) {
				if (e->nx != 0) {
					
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


void Player::Render()
{
	switch (this->direction) {
	case RIGHT:
		this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true);
		break;
	case LEFT:
		if (state == PLAYER_STATE::STAND_ATK) {
			this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false, -24, 0);
		}
		else if (state == PLAYER_STATE::SIT_ATK) {
			this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false, -24, 0);
		}
		else {
			this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false);
		}
		break;
	default:
		break;
	}
}





