#include "Eagle.h"
#include "Player.h"
#include "Debug.h"
Eagle::Eagle() {

}

void Eagle::init() {
	this->SetObjectType(EAGLE);
	this->position.z = 0.0f;
	this->isActive = false;
	objectHeight = objectWidth = 1;
	acceleratorX = 0;
	acceleratorY = 0;
	SetVeclocity(0.0f, 0.0f);
	firstFly = true;
	state = FOLLOW;
	finishFly = 1;
	this->sprite = new  map<ENEMY_STATE, Sprite*>();
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FOLLOW,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_Eagle_follow, 2, 0.07f)));
	//this->sprite
	//	->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
	//		new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 2, 0.04f)));
}

Eagle::Eagle(vector<int> activeArea, int positionX, int positionY) {
	this->activeArea = activeArea;
	SetPosition(positionX, positionY);
	init();
}

Eagle::~Eagle() {
	if (this->sprite != NULL) {
		for (auto i = this->sprite->begin(); i != this->sprite->end(); i++) {
			delete i->second;
			this->sprite->erase(i);
		}
		delete this->sprite;
	}
}

void Eagle::UpdatteActiveArea(float t) {
	
	if (!isActive) {
		int a = 0, b = 1, c = 0;
		float x1 = Player::GetInstance()->GetPosition().x;
		float y1 = Player::GetInstance()->GetPosition().y - 5;
		float x2 = position.x, y2 = position.y;
		if (Player::GetInstance()->GetPosition().x >= activeArea.at(0)
			&& Player::GetInstance()->GetPosition().x <= activeArea.at(1)
			&& Player::GetInstance()->GetDirection() == RIGHT
			&& activeArea.at(0) != 0
			&& activeArea.at(1) != 0) {
			isActive = true;
			direction = LEFT;
			finishFly = 1;
			SetVx(-200.0f);
			firstFly = true;
		}
		else {
			if (Player::GetInstance()->GetPosition().x >= activeArea.at(2)
				&& Player::GetInstance()->GetPosition().x <= activeArea.at(3)
				&& Player::GetInstance()->GetDirection() == LEFT
				&& activeArea.at(2) != 0
				&& activeArea.at(3) != 0) {
				isActive = true;
				direction = RIGHT;
				finishFly = 2;
				firstFly = true;
			}
		}
		a = y2 - y1;
		b = x2 - x1;
		c = y1 * b - x1 * (y2 - y1);
		number.push_back(a);
		number.push_back(b);
		number.push_back(c);
		top = Player::GetInstance()->GetPosition().y - 15;
		bottom = Player::GetInstance()->GetPosition().y + 15;
	}
	if (isActive) {
		float left = Player::GetInstance()->GetPosition().x - 80.0f;
		float right = Player::GetInstance()->GetPosition().x + 80.0f;
		//Khoảng cách giữa player và đại bàng
		float dx = 0;
		RECT rect = Player::GetInstance()->GetBoundingBox();
		if (position.x > Player::GetInstance()->GetPosition().x) {
			dx = GetBoundingBox().left - rect.right;
		}
		else {
			dx = rect.left - GetBoundingBox().right;
		}
		if (firstFly) {
			if (position.y < bottom) {
				veclocity.y += (number[0]*veclocity.x + number[2]) / number[1];
				if (veclocity.y >= 82) {
					SetVy(82.0f);
				}
				if (position.x < Player::GetInstance()->GetPosition().x) {
					direction = RIGHT;
				}
				if (position.x > Player::GetInstance()->GetPosition().x) {
					direction = LEFT;
				}
			}
			else {
				firstFly = false;
			}
		}
		if (!firstFly) {
			if (direction == LEFT) {
				if (position.x < Player::GetInstance()->GetPosition().x) {
					direction = RIGHT;
				}
				if (dx >= MAX_DISTANCE_PLAYER && finishFly == 2) {
					//Hoàn thành bay qua phải, cb bay qua trái
					finishFly = 1;
					SetVy(82.0f);
					SetVx(-200.0f);
				}
				if (position.y < top && finishFly == 2) {

				}
			}

			if (direction == RIGHT) {
				if (position.x > Player::GetInstance()->GetPosition().x) {
					direction = LEFT;
				}
				if (finishFly == 1 && dx >= MAX_DISTANCE_PLAYER) {
					//Hoàn thành bay qua trái, = 2 là cb bay qua phải
					finishFly = 2;
					SetVy(0.0f);
					SetVx(0.0f);
				}
				if (finishFly == 2) {
					if (time >= 0.2f) {

					}
					else {
						time += t;
					}
				}
			}
		}
	}
}

void Eagle::FollowPlayer(float t) {
	
}

void Eagle::Update(float t, vector<Object*>* object) {
	UpdatteActiveArea(t);
	if (isActive) {
		Object::Update(t);
		RECT rect = sprite->at(state)->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);
		sprite->at(state)->NextSprite(t);
		HandleCollision(object);
		FollowPlayer(t);
	}
}

void Eagle::HandleCollision(vector<Object*>* object) {
	vector<CollisionHandler*>* coEvents = new vector<CollisionHandler*>();
	vector<CollisionHandler*>* coEventsResult = new vector<CollisionHandler*>();
	coEvents->clear();
	if (isActive) {
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
			if (e->object->GetObjectType() == OBJECT_TYPE::MAIN_CHARACTER) {
				if (e->nx != 0 || e->ny ) {
					
				}
			}
			Object::PlusPosition(this->deltaX, this->deltaY);
		}
	}
}

void Eagle::Render() {
	if (isActive) {
		switch (this->direction) {
		case RIGHT:
			this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true);
			break;
		case LEFT:
			this->sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false);
			break;
		default:
			break;
		}
	}
}

void Eagle::ResetState() {
	if (isActive) {
		isActive = false;
		SetPosition(GetLastPos().x, GetLastPos().y);
		SetVx(0.0f);
		SetVy(0.0f);
	} 
}