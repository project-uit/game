#include "SoldierSword.h"
#include "Square.h"
#include "Player.h"
#include "GameDebugDraw.h"
GameDebugDraw* draw2;
SoldierSword::SoldierSword() {

	
}
void SoldierSword::init() {
	this->SetObjectType(SOLDIER_SWORD);
	if (direction == LEFT) {
		this->SetVeclocity(-40.0f, 0.0f);
	}
	else {
		this->SetVeclocity(40.0f, 0.0f);
	}
	
	this->position.z = 0.0f;
	this->isActive = true;
	time = 0;
	state = FOLLOW;
	draw2 = new GameDebugDraw();
	this->sprite = new  map<ENEMY_STATE, Sprite*>();
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FOLLOW,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_SoldierSword_follow, 2, 0.09f)));
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::ATK,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_SoldierSword_atk, 2, 0.15f)));
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 2, 0.04f)));
}

SoldierSword::SoldierSword(RECT movingArea, int posX, int posY, DIRECTION direction) {
	this->movingArea = movingArea;
	this->direction = direction;
	SetPosition((float)posX, (float)posY);
	init();
}

SoldierSword::~SoldierSword() {

}

RECT SoldierSword::GetMovingArea() {
	return this->movingArea;
}

void SoldierSword::Update(float t, vector<Object*>* objects) {
	Object::Update(t);
	this->veclocity.y += GRAVITY;
	RECT rect = sprite->at(this->state)->GetBoudingBoxFromCurrentSprite();
	Object::updateBoundingBox(rect);
	sprite->at(this->state)->NextSprite(t);
	if (state == ENEMY_STATE::DEAD) {
		if (sprite->at(this->state)->GetIsComplete()) {
			sprite->at(this->state)->SetIndex(1);
		}
	}
	
	HandleCollision(objects);

	if (state != ENEMY_STATE::DEAD) {
		Line left = Line(movingArea.left, movingArea.top,
			movingArea.left, movingArea.bottom);

		Line right = Line(movingArea.right, movingArea.top,
			movingArea.right, movingArea.bottom);

		if (Game::AABB_BoxLine(GetBoundingBox(), left)) {
			SetVx(40.0f);
			direction = RIGHT;
		}

		if (Game::AABB_BoxLine(GetBoundingBox(), right)) {
			SetVx(-40.0f);
			direction = LEFT;
		}
		if (time >= 0.675f) {
			state = ATK;
			time = 0.0f;
		}
		else {
			time += t;
		}

		if (sprite->at(this->state)->GetIsComplete() && state == ATK) {
			sprite->at(this->state)->Reset();
			state = FOLLOW;
			if (direction == LEFT) {
				SetVx(-40.0f);
			}
			else {
				SetVx(40.0f);
			}
		}

		if (Game::AABB(Player::GetInstance()->GetKatana()->GetBoundingBox(), GetBoundingBox())) {
			state = ENEMY_STATE::DEAD;
			SetVx(0.0f);
			Object::PlusPosition(0, -3.0f);
		}
	}
}

void SoldierSword::HandleCollision(vector<Object*> *object) {
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
		this->PlusPosition(min_tx * this->deltaX + nx * 0.2f, min_ty*this->deltaY + ny * 0.2f);
		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			if (e->object->GetObjectType() == OBJECT_TYPE::SQUARE) {
				//Square *item = dynamic_cast<Square *>(e->object);
				if (e->ny < 0) {
					this->SetVy(0.0f);
				}
			}
			else {
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

void SoldierSword::Render() {
	
	//draw2->DrawRect(movingArea, Camera::GetInstance());
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

