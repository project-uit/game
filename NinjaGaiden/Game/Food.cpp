#include "Sound.h"
#include "Food.h"
#include "Square.h"
#include "Player.h"
#include "HUD.h"

Food::Food(SCENCE scene, int foodType, int posX, int posY) {
	this->SetObjectType(FOOD);
	this->SetPosition(posX, posY);
	this->initialPosition.x = posX;
	this->initialPosition.y = posY;
	this->SetVeclocity(0.0f, 0.0f);
	this->position.z = 0.0f;
	this->isActive = true;
	state = UNTOUCH;
	this->sprite = new  map<FOOD_STATE, Sprite*>();

	this->sprite
		->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::DIGESTED,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_DEAD, 1, 0.0f)));

	switch (scene)
	{
	case SCENCE::SCENCE_1:
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::UNTOUCH,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_UNTOUCH_BUTTERFLY, 2, 0.09f)));
		break;
	case SCENCE::SCENCE_2:
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::UNTOUCH,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_UNTOUCH_BIRD, 2, 0.09f)));
		break;
	default:
		break;
	}

	switch (foodType)
	{
	case 0:
		type = FOOD_TYPE::ITEM_POINT_BLUE;
		score = 5;
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::TOUCHED,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_ITEM_POINT_BLUE, 1, 0.0f)));
		break;
	case 1:
		type = FOOD_TYPE::ITEM_POINT_RED;
		score = 10;
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::TOUCHED,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_ITEM_POINT_RED, 1, 0.0f)));
		break;
	case 2:
		type = FOOD_TYPE::VASE_BLUE;
		score = 500;
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::TOUCHED,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_VASE_BLUE, 1, 0.0f)));
		break;
	case 3:
		type = FOOD_TYPE::VASE_RED;
		score = 1000;
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::TOUCHED,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_VASE_RED, 1, 0.0f)));
		break;
	case 4:
		type = FOOD_TYPE::TIMER;
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::TOUCHED,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_TIME, 1, 0.0f)));
		break;
	case 5:
		type = FOOD_TYPE::FIRE;
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::TOUCHED,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_FIRE, 1, 0.0f)));
		break;
	case 6:
		type = FOOD_TYPE::SHURIKEN_BLUE;
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::TOUCHED,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_SHURIKEN_BLUE, 1, 0.0f)));
		break;
	case 7:
		type = FOOD_TYPE::SHURIKEN_RED;
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::TOUCHED,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_SHURIKEN_RED, 1, 0.0f)));
		break;
	case 8:
		type = FOOD_TYPE::MANA;
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::TOUCHED,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_MANA, 1, 0.0f)));
		break;
	default:
		break;
	}
}

Food::~Food() {

}

bool Food::GetIsOnGround() {
	return this->isOnGround;
}

void Food::SetIsOnGround(bool flag) {
	this->isOnGround = flag;
}

FOOD_TYPE Food::GetType() {
	return this->type;
}

int Food::GetScore() {
	return this->score;
}

FOOD_STATE Food::GetState() {
	return this->state;
}

void Food::Update(float t, vector<Object*>* objects) {
	if (this->state == TOUCHED) {
		if (!isOnGround) {
			this->veclocity.y += GRAVITY * t;
			Object::PlusPosition(this->deltaX, this->deltaY);
		}
		else {
			if (timer >= TIME_DISAPPEAR) {
				state = FOOD_STATE::DIGESTED;
				timer = 0;
			}
			else {
				timer += t;
			}
		}
	}

	Object::Update(t);
	RECT rect = sprite->at(this->state)->GetBoudingBoxFromCurrentSprite();
	Object::updateBoundingBox(rect);
	sprite->at(this->state)->NextSprite(t);
	HandleCollision(objects);
}

void Food::HandleCollision(vector<Object*> *object) {
	vector<CollisionHandler*>* coEvents = new vector<CollisionHandler*>();
	vector<CollisionHandler*>* coEventsResult = new vector<CollisionHandler*>();
	coEvents->clear();
	Object::CalcPotentialCollisions(object, coEvents);
	if (coEvents->size() != 0) {
		float min_tx, min_ty, nx = 0, ny;
		this->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			if (e->object->GetObjectType() == OBJECT_TYPE::SQUARE) {
				this->SetVy(0.0f);
				isOnGround = true;
			}
			else if (e->object->GetObjectType() == OBJECT_TYPE::MAIN_CHARACTER) {
				if (Player::GetInstance()->GetState() == JUMP_ATK) {
					this->state = TOUCHED;
				}
			}
		}
	}

	if (this->state == UNTOUCH) {
		if (Game::AABB(Player::GetInstance()->GetKatana()->GetBoundingBox(), GetBoundingBox())) {
			this->state = TOUCHED;
		}
		
		if (Player::GetInstance()->GetWeapon()) {
			if (Player::GetInstance()->GetWeapon()->GetObjectType() != CIRCLE_FIRE) {
				if (Game::AABB(Player::GetInstance()->GetWeapon()->GetBoundingBox(), GetBoundingBox())) {
					this->state = TOUCHED;
				}
			}
			else {
				for (int i = 0; i < 3; i++) {
					if (Game::AABB(Player::GetInstance()->GetWeapon()[i].GetBoundingBox(), GetBoundingBox())) {
						this->state = TOUCHED;
						break;
					}
				}
			}
		}
	}

	if (Game::AABB(Player::GetInstance()->GetBoundingBox(), GetBoundingBox())) {
		if (this->state == TOUCHED) {
			Sound::GetInstance()->Play(SOUND_DIGEST_FOOD, false, 1);
			Player::GetInstance()->DigestFood(this, sprite->at(FOOD_STATE::TOUCHED));
			this->state = DIGESTED;
		}
	}

	for (UINT i = 0; i < coEvents->size(); i++) {
		delete coEvents->at(i);
	}

	delete coEvents;
	delete coEventsResult;
}

void Food::Render() {
	if (this->state != DIGESTED) {
		sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true);
	}
}

void Food::Reset() {
	state = FOOD_STATE::UNTOUCH;
	position = initialPosition;
	isOnGround = false;
}

void Food::ResetState() {
	if (Player::GetInstance()->GetState() == PLAYER_STATE::DIE) {
		Reset();
	}
}