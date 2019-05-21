#include "Food.h"
#include "Square.h"
#include "Player.h"

Food::Food(SCENCE scene, int type, int posX, int posY) {
	this->SetObjectType(FOOD);
	this->SetPosition(posX, posY);
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
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_UNTOUCH, 2, 0.09f)));
		break;
	case SCENCE::SCENCE_2:
		//this->sprite
		//	->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::UNTOUCH,
		//		new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_UNTOUCH, 2, 0.09f)));
		break;
	default:
		break;
	}

	switch (type)
	{
	case 311:
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::TOUCHED,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_BLOOD_BLUE, 1, 0.0f)));
		break;
	case 312:
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::TOUCHED,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_BLOOD_RED, 1, 0.0f)));
		break;
	case 321:
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::TOUCHED,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_DARTS_BLUE, 1, 0.0f)));
		break;
	case 322:
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::TOUCHED,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_DARTS_RED, 1, 0.0f)));
		break;
	case 331:
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::TOUCHED,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_ITEM_BLUE, 1, 0.0f)));
		break;
	case 332:
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::TOUCHED,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_ITEM_RED, 1, 0.0f)));
		break;
	case 340:
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::TOUCHED,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_TIME, 1, 0.0f)));
		break;
	case 350:
		this->sprite
			->insert(pair<FOOD_STATE, Sprite*>(FOOD_STATE::TOUCHED,
				new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_FOOD_FIRE, 1, 0.0f)));
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

void Food::Update(float t, vector<Object*>* objects) {
	if (this->state == TOUCHED && !isOnGround) {
		this->veclocity.y += GRAVITY*t;
		Object::PlusPosition(this->deltaX, this->deltaY);
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
			if (e->object->GetObjectType() == OBJECT_TYPE::SQUARE && e->ny < 0) {
				this->SetVy(0.0f);
				isOnGround = true;
			}
		}
	}

	if (Game::AABB(Player::GetInstance()->GetKatana()->GetBoundingBox(), GetBoundingBox())) {
		if (this->state == UNTOUCH) {
			this->state = TOUCHED;
		}
	}

	if (Game::AABB(Player::GetInstance()->GetBoundingBox(), GetBoundingBox())) {
		if (this->state == TOUCHED) {
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

