#include "Square.h"
#include "Player.h"
#include "SoliderGun.h"
#include "GameDebugDraw.h"

Bullet::Bullet(int positionX, int positionY, BULLET_TYPE type, DIRECTION direction) {
	this->direction = direction;
	this->type = type;
	SetPosition(positionX, positionY);
	isActive = false;
	state = ENEMY_STATE::INVISIBLE;
	sprite = new map<ENEMY_STATE, Sprite*>();

	switch (type)
	{
	case GUN:
		sprite->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FLY,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_GUN_BULLET, 1, 0)));
		break;
	case BAZOKA:
		sprite->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FLY,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_SOLIDER_BAZOKA_BULLET, 1, 0)));
		break;
	default:
		break;
	}

	sprite->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
		new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 2, 0.04f)));
}

Bullet::~Bullet() {

}

void Bullet::Update(float t, vector<Object*>* objects) {
	if (state != INVISIBLE) {
		Object::Update(t);
		RECT rect = sprite->at(state)->GetBoudingBoxFromCurrentSprite();
		updateBoundingBox(rect);
		HandleCollision(objects);
		sprite->at(state)->NextSprite(t);
		if (state == ENEMY_STATE::DEAD) {
			if (sprite->at(state)->GetIsComplete()) {
				sprite->at(state)->Reset();
				state = ENEMY_STATE::INVISIBLE;
			}
		}
		else {
			PlusPosition(deltaX, 0);
			if (Game::AABB(Player::GetInstance()->GetKatana()->GetBoundingBox(), GetBoundingBox())) {
				state = ENEMY_STATE::DEAD;
				position.y = Player::GetInstance()->GetPosition().y - 10;
			}
		}
	}
}

void Bullet::HandleCollision(vector<Object*> *object) {
	vector<CollisionHandler*>* coEvents = new vector<CollisionHandler*>();
	vector<CollisionHandler*>* coEventsResult = new vector<CollisionHandler*>();
	coEvents->clear();
	Object::CalcPotentialCollisions(object, coEvents);
	if (coEvents->size() != 0) {
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionHandler* e = coEventsResult->at(i);
			if (e->object->GetObjectType() == OBJECT_TYPE::MAIN_CHARACTER) {
				if (state == FLY) {
					if (!Player::GetInstance()->GetWounded()) {
						if (Player::GetInstance()->Wounded(e, direction)) {
							continue;
						}
					}
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

void Bullet::Fly(DIRECTION direction) {
	state = FLY;
	this->direction = direction;

	switch (type)
	{
	case GUN:
		if (direction == LEFT) {
			SetVx(-BULLET_VX);
			SetPosition(soliderPosition.x, soliderPosition.y + 10);
		}
		else {
			SetVx(BULLET_VX);
			SetPosition(soliderPosition.x + 5, soliderPosition.y + 10);
		}
		break;
	case BAZOKA:
		if (direction == LEFT) {
			SetVx(-BULLET_VX);
			SetPosition(soliderPosition.x, soliderPosition.y + 5);
		}
		else {
			SetVx(BULLET_VX);
			SetPosition(soliderPosition.x + 15, soliderPosition.y + 5);
		}
		break;
	default:
		break;
	}
}

void Bullet::Render() {
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
}

void Bullet::ResetState() {
	isActive = false;
	if (state == DEAD) {
		sprite->at(ENEMY_STATE::DEAD)->Reset();
	}
	state = ENEMY_STATE::INVISIBLE;
	SetPosition(lastPos.x, lastPos.y);
}

void Bullet::UpdateSoliderPosition(D3DXVECTOR3 soliderPosition) {
	this->soliderPosition = soliderPosition;
}

void Bullet::SetState(ENEMY_STATE state) {
	this->state = state;
}