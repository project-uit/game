#include "Witch.h"
#include "WitchSword.h"
#include "Square.h"
#include "Player.h"
#include "GameDebugDraw.h"
GameDebugDraw* draw3;
Witch::Witch() {

}

Witch::~Witch() {

}

Witch::Witch(int posX, int posY, vector<int> movingLimit, vector<int> activeArea) {
	this->movingLimit = movingLimit;
	this->activeArea = activeArea;

	draw3 = new GameDebugDraw();

	for (int i = 0; i < NUMBER_OF_SWORD; i++) {
		sword[i] = new WitchSword(posX, posY, direction);
	}

	SetObjectType(OBJECT_TYPE::WITCH);
	direction = direction;
	SetPosition((float)posX, (float)posY);
	isOnGround = false;
	timerSkill = 0;
	timerThrow = 0;
	countThrow = 0;
	GotoStateFollow();

	InitSpite();
}

void Witch::InitSpite() {
	sprite = new  map<ENEMY_STATE, Sprite*>();
	sprite->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FOLLOW,
		new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_WITCH_FOLLOW, 2, 0.09f)));
	sprite->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::ATK,
		new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_WITCH_ATK, 2, 0.09f)));
	sprite->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
		new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 2, 0.04f)));
}
void Witch::Update(float t, vector<Object*>* objects) {
	if (state != INVISIBLE) {
		Object::Update(t);
		RECT rect = sprite->at(state)->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);
		sprite->at(state)->NextSprite(t);
		if (state == ENEMY_STATE::DEAD) {
			if (sprite->at(state)->GetIsComplete()) {
				sprite->at(state)->Reset();
				state = ENEMY_STATE::INVISIBLE;
				for (int i = 0; i < NUMBER_OF_SWORD; i++) {
					sword[i]->SetState(ENEMY_STATE::INVISIBLE);
				}
			}
		}
		else {
			HandleCollision(objects);
			HandleDirection();
			HandleAttack(t);

			if (isOnGround) {
				PlusPosition(deltaX, 0);
			}
			else {
				veclocity.y += GRAVITY;
				PlusPosition(deltaX, deltaY);
			}

			if (Game::AABB(Player::GetInstance()->GetKatana()->GetBoundingBox(), GetBoundingBox())) {
				state = ENEMY_STATE::DEAD;
			}
		}
	}

	for (int i = 0; i < NUMBER_OF_SWORD; i++) {
		sword[i]->Update(t, objects);
		sword[i]->UpdateWitchPosition(position);
	}
}

void Witch::HandleCollision(vector<Object*> *objects) {
	vector<CollisionHandler*>* coEvents = new vector<CollisionHandler*>();
	vector<CollisionHandler*>* coEventsResult = new vector<CollisionHandler*>();
	coEvents->clear();
	Object::CalcPotentialCollisions(objects, coEvents);
	if (coEvents->size() != 0) {
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			if (e->object->GetObjectType() == OBJECT_TYPE::SQUARE) {
				if (e->ny < 0) {
					isOnGround = true;
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

void Witch::GotoStateFollow() {
	state = ENEMY_STATE::FOLLOW;
	if (direction == DIRECTION::LEFT) {
		SetVeclocity(-WITCH_VX, 0);
	}
	else {
		SetVeclocity(WITCH_VX, 0);
	}
}

void Witch::HandleDirection(){
	float boxWidth = GetBoundingBox().right - GetBoundingBox().left;

	if (position.x <= movingLimit.at(0)) {
		SetVx(WITCH_VX);
	}

	if (position.x + boxWidth >= movingLimit.at(1)) {
		SetVx(-WITCH_VX);
	}

	if (state != ENEMY_STATE::ATK) {
		if (Player::GetInstance()->GetPosition().x >= activeArea.at(0)
			&& Player::GetInstance()->GetPosition().x <= activeArea.at(1)) {
			if (Player::GetInstance()->GetPosition().x <= position.x) {
				direction = DIRECTION::LEFT;
			}
			else {
				direction = DIRECTION::RIGHT;
			}
		}
	}
}

void Witch::HandleAttack(float t) {
	if (state != ATK) {
		if (countThrow < 3) {
			if (timerThrow >= THROW_DELAY_TIME) {
				state = ENEMY_STATE::ATK;
				veclocity.x = 0;
				switch (countThrow)
				{
				case 0:
					sword[0]->Fly(70, direction);
					countThrow++;
					break;
				case 1:
					sword[1]->Fly(100, direction);
					countThrow++;
					break;
				case 2:
					sword[2]->Fly(-10, direction);
					countThrow++;
					break;
				default:
					break;
				}
				timerThrow = 0;
			}
			else {
				timerThrow += t;
			}
		}
		else {
			if (timerThrow >= THROW_DELAY_TIME) {
				if (timerSkill >= SKILL_DELAY_TIME) {
					state = ENEMY_STATE::ATK;
					veclocity.x = 0;
					switch (countThrow)
					{
					case 3:
						sword[0]->Fly(70, direction);
						countThrow++;
						break;
					case 4:
						sword[1]->Fly(100, direction);
						countThrow++;
						break;
					case 5:
						sword[2]->Fly(-10, direction);
						countThrow = 0;
						timerThrow = 0;
						break;
					default:
						break;
					}
					timerSkill = 0;
				}
				else {
					timerSkill += t;
				}
			}
			else {
				timerThrow += t;
			}
		}
	}
	else {
		if (sprite->at(state)->GetIsComplete()) {
			sprite->at(state)->Reset();
			this->GotoStateFollow();
		}
	}
}

void Witch::Render() {
	if (state != INVISIBLE) {
		switch (direction) {
		case RIGHT:
			sprite->at(state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true);
			break;
		case LEFT:
			sprite->at(state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false);
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < NUMBER_OF_SWORD; i++) {
		sword[i]->Render();
	}
}

void Witch::ResetState() {
	isActive = false;
	isOnGround = false;
	if (state == ENEMY_STATE::DEAD) {
		sprite->at(ENEMY_STATE::DEAD)->Reset();
	}
	GotoStateFollow();
	SetPosition(lastPos.x, lastPos.y);
	for (int i = 0; i < NUMBER_OF_SWORD; i++) {
		sword[i]->SetState(ENEMY_STATE::INVISIBLE);
	}
}