#include "Panther.h"

Panther::Panther() {
	
}

void Panther::init() {
	this->SetObjectType(PANTHER);
	if (direction == LEFT) {
		this->SetVeclocity(-40.0f, 0.0f);
	}
	else {
		this->SetVeclocity(40.0f, 0.0f);
	}
	this->position.z = 0.0f;
	this->isActive = true;
	state = FOLLOW;
	this->sprite = new  map<ENEMY_STATE, Sprite*>();
	this->sprite
		->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FOLLOW,
			new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_Panther_follow, 2, 0.06f)));
}

Panther::Panther(RECT movingArea, int posX, int posY, DIRECTION direction) {
	this->movingArea = movingArea;
	this->direction = direction;
	SetPosition((float)posX, (float)posY);
	init();
}

Panther::~Panther() {

}

void Panther::Update(float t, vector<Object*>* objects) {
	Object::Update(t);
	this->veclocity.y += GRAVITY;
	RECT rect = sprite->at(this->state)->GetBoudingBoxFromCurrentSprite();
	Object::updateBoundingBox(rect);
	sprite->at(this->state)->NextSprite(t);
}

void Panther::HandleCollision(vector<Object*>* objects) {

}

void Panther::Render() {

}