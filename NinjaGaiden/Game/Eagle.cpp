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
	left = 0;
	right = 0;
	SetVeclocity(0.0f, 0.0f);
	firstFly = true;
	state = FOLLOW;
	finishFly = 0;
	destination = 0;
	this->sprite = new  map<ENEMY_STATE, Sprite*>();
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FOLLOW,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_Eagle_follow, 2, 0.045f)));
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
		float y1 = 145;
		float x2 = position.x, y2 = position.y;
		if (Player::GetInstance()->GetPosition().x >= activeArea.at(0)
			&& Player::GetInstance()->GetPosition().x <= activeArea.at(1)
			&& Player::GetInstance()->GetDirection() == RIGHT
			&& activeArea.at(0) != 0
			&& activeArea.at(1) != 0) {
			isActive = true;
			direction = LEFT;
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
		//Khoảng cách giữa player và đại bàng
		
		if (firstFly) {
			left = Player::GetInstance()->GetPosition().x - 90.0f;
			right = Player::GetInstance()->GetPosition().x + 90.0f;
			RECT rect = Player::GetInstance()->GetBoundingBox();
			if (position.y < rect.bottom && position.x > left) {
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
				SetVy(0.0f);
			}
		}
		
	}
}

void Eagle::FollowPlayer(float t) {
	if (!firstFly) {
		float dx = 0;
		if (direction == LEFT) {
			if (position.x < Player::GetInstance()->GetPosition().x) {
				direction = RIGHT;
				SetVx(-180.0f);
			}
		}
		if (direction == RIGHT) {
			if (position.x > Player::GetInstance()->GetPosition().x) {
				direction = LEFT;
				SetVx(180.0f);
			}
		}
		if (veclocity.x < 0) {
			if (position.x < left) {
				finishFly = 2;
			}
		}
		else {
			if (position.x > right) {
				finishFly = 1;
			}
		}
		RECT rect = Player::GetInstance()->GetBoundingBox();

		if (position.x > Player::GetInstance()->GetPosition().x) {
			dx = GetBoundingBox().left - rect.right;
		}
		else {
			dx = rect.left - GetBoundingBox().right;
		}

		if (finishFly > 0) {
			if (time >= 0.03f) {
				left = Player::GetInstance()->GetPosition().x - 90.0f;
				right = Player::GetInstance()->GetPosition().x + 90.0f;
				time = 0;
				finishFly = 0;
				SetVy(0.0f);
				if (direction == LEFT) {
					SetVx(-200.0f);
				}
				if (direction == RIGHT) {
					SetVx(200.0f);
				}
			}
			else {
				time += t;
				SetVy(30);
				switch (finishFly) {
				case 1:
					
					break;
				case 2:
					
					break;
				default:
					SetVx(0.0f);
					break;
				}
			}
		}
		else {
			//&& position.y > Player::GetInstance()->GetPosition().y - 40
			if (dx <= MIN_DISTANCE_PLAYER) {
				SetVy(-100);
			}
			else {
				if (position.y < bottom) {
					SetVy(120);
				}
				else {
					SetVy(-10.0f);
					//position.y += 0.05f;
				}
			}
		}
	}
}

void Eagle::Update(float t, vector<Object*>* object) {
	UpdatteActiveArea(t);
	if (isActive) {
		Object::Update(t);
		RECT rect = sprite->at(state)->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);
		FollowPlayer(t);
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
		//this->PlusPosition(min_tx * this->deltaX + nx * 0.2f, min_ty*this->deltaY + ny * 0.2f);
		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			if (e->object->GetObjectType() == OBJECT_TYPE::MAIN_CHARACTER) {
				/*if (e->nx != 0 || e->ny != 0) {
					Player::GetInstance()->Wounded(e->nx, e->ny, this, direction);
				}*/
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