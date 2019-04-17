#include "Player.h"

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
	this->SetVeclocity(0.0f, 0.0f);
	this->position.z = 0.0f;

	this->sprite = new  map<PLAYER_STATE, Sprite*>();
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::STAND,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_MAIN_STAND, 1)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::RUN,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_MAIN_RUN, 3)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::SIT,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_SIT, 1)));
	//this->sprite
	//	->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::SIT_ATK,
	//		new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_SIT_ATK, 3)));
	//this->sprite
	//	->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::STAND_ATK,
	//		new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_STAND_ATK, 3)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::JUMP,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_JUMP, 4)));
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

bool Player::GetStateActive()
{
	return this->isActive;
}

void Player::Reset(float x, float y)
{
	this->isActive = true;
	this->SetLastPos(this->GetPosition());
	this->SetPosition(x, y);
}

void Player::Update(float t, vector<Object*>* object)
{
	Object::Update(t);
	
	RECT rect = this->sprite->at(this->state)->GetBoudingBoxFromCurrentSprite(this->direction);

	Object::updateBoundingBox(rect);
	//this->veclocity.y += 0.00009f*t;
	if (this->last_state != this->state) {
		ResetSpriteState(this->last_state);
		this->sprite->at(this->state)->NextSprite();
	}

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
		
		//this->PlusPosition(min_tx * this->deltaX + nx * 0.4f, min_ty * this->deltaY + ny * 0.4f);

		if (nx > 0) {
			DebugOut((wchar_t *)L"Va chạm trục X1!\n");
			this->SetVx(0.0f);
		}
		if (nx < 0) {
			DebugOut((wchar_t *)L"Va chạm trục X2!\n");
			this->SetVx(0.0f);
		}
		if (ny != 0) {
			this->SetVy(0.0f);
			DebugOut((wchar_t *)L"Va chạm trục Y %f %f %f %f!\n", rect.top, rect.left, rect.right, rect.bottom);
		}

		for (UINT i = 0; i < coEventsResult->size(); i++) {

			CollisionHandler* e = coEventsResult->at(i);
			//xu ly va cham
			if (dynamic_cast<Item *>(e->getObject())) {
				Item *item = dynamic_cast<Item *>(e->getObject());
				float x = item->GetPosition().x;
				float y = item->GetPosition().y;
				//item->SetPosition(x + 5, y);
			}
		}
	}
	
	
	for (UINT i = 0; i < coEvents->size(); i++) {
		delete coEvents->at(i);
	}	

	delete coEvents;
	delete coEventsResult;

	this->sprite->at(this->state)->NextSprite();
}

void Player::Render()
{
	switch (this->direction) {
	case RIGHT:
		this->sprite->at(this->state)->DrawSprite(this->position, true);
		break;
	case LEFT:
		this->sprite->at(this->state)->DrawSprite(this->position, false);
		break;
	default:
		break;
	}
}

