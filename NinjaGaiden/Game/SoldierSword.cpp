#include "SoldierSword.h"
#include "Square.h"
#include "Player.h"

SoldierSword::SoldierSword() {

	this->SetObjectType(SOLDIER_SWORD);
	this->SetPosition(239, 150);
	this->SetVeclocity(0.0f, 0.0f);
	this->position.z = 0.0f;
	this->direction = LEFT;
	this->isActive = true;
	movingArea.left = 200;
	movingArea.right = 200 + 150;
	movingArea.top = 150;
	movingArea.bottom = 150 + 50;
	state = FOLLOW;
	this->sprite = new  map<ENEMY_STATE, Sprite*>();
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FOLLOW,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_SoldierSword_follow, 2)));
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::ATK,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_SoldierSword_atk, 2)));
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 1)));
}

SoldierSword::~SoldierSword() {

}

RECT SoldierSword::GetMovingArea() {
	return this->movingArea;
}

void SoldierSword::Update(float t, vector<Object*>* objects) {
	Object::Update(t);
	this->veclocity.y += GRAVITY * t;
	RECT rect = sprite->at(this->state)->GetBoudingBoxFromCurrentSprite();
	Object::updateBoundingBox(rect);
	sprite->at(this->state)->NextSprite();
	//sprite->at(this->state)->SetIndex(1);
	HandleCollision(objects);

	Line left = Line(movingArea.left, movingArea.top,
		movingArea.left, movingArea.bottom);

	Line right = Line(movingArea.right, movingArea.top,
		movingArea.right, movingArea.bottom);
	
	if (Game::AABB_BoxLine(GetBoundingBox(), left)) {
		
		/*SetVx(0.04625);
		direction = RIGHT;*/
	}

	if (Game::AABB_BoxLine(GetBoundingBox(), right)) {
		DebugOut((wchar_t *)L"[SoldierSword.cpp] chạm xx\n");
		/*SetVx(-0.04625);
		direction = LEFT;*/
	}
}

void SoldierSword::HandleCollision(vector<Object*> *object) {
	vector<CollisionHandler*>* coEvents = new vector<CollisionHandler*>();
	vector<CollisionHandler*>* coEventsResult = new vector<CollisionHandler*>();
	coEvents->clear();
	Object::CalcPotentialCollisions(object, coEvents);
	if (coEvents->size() == 0) {
		Object::PlusPosition(this->deltaX, this->deltaY);
	}
	else {
		float min_tx, min_ty, nx = 0, ny;
		this->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		//this->PlusPosition(min_tx * this->deltaX + nx * 0.4f, min_ty*this->deltaY + ny*0.4f);

		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			if (dynamic_cast<Square *>(e->object)) {
				Square *item = dynamic_cast<Square *>(e->object);
				if (ny != 0) {
					//DebugOut((wchar_t *)L"[SoldierSword.cpp] Va chạm gạch\n");
					this->SetVy(0.0f);
				}
				if (nx != 0) {
					this->SetVx(0.0f);
				}
			}
		}
	}

	for (UINT i = 0; i < coEvents->size(); i++) {
		delete coEvents->at(i);
	}

	delete coEvents;
	delete coEventsResult;

	if (Game::AABB(Player::GetInstance()->GetBoundingBox(), movingArea)) {
		SetVx(-0.04625);
	}
	if (Game::AABB(Player::GetInstance()->GetBoundingBox(), GetBoundingBox())) {
		state = ATK;
	}
	else {
		state = FOLLOW;
	}
}

void SoldierSword::Render() {
	
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

