#include "Player.h"

Player* Player::_instance = NULL;

Player::Player()
{
	this->SetObjectType(MAIN_CHARACTER);
	this->SetState(PLAYER_STATE::STAND);
	this->SetLastState(PLAYER_STATE::STAND);
	this->SetDirection(DIRECTION::RIGHT);
	this->objectWidth = DEFAULT_MAIN_WIDTH;
	this->objectHeight = DEFAULT_MAIN_HEIGHT;
	this->SetPosition(300, 300);
	this->SetVeclocity(0.0f, 0.0f);
	this->position.z = 0.0f;

	this->sprite = new  map<PLAYER_STATE, Sprite*>();
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::STAND,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_MAIN_STAND, 1, 17, 32, 1.8f)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::RUN,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_MAIN_RUN, 3, 22, 32, 1.8f)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::SIT,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_SIT, 1, 17, 32, 1.8f)));
	this->sprite
		->insert(pair<PLAYER_STATE, Sprite*>(PLAYER_STATE::SIT_ATK,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_SIT_ATK, 3, 17, 32, 1.8f)));
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

void Player::SetLastState(PLAYER_STATE last_state) {
	this->last_state = last_state;
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
	this->PlusPosition(this->deltaX, this->deltaY);
	if (this->last_state != this->state) {
		ResetSpriteState(this->last_state);
	}
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

