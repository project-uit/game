#include "Item.h"

Item::Item()
{
	this->SetObjectType(MAIN_CHARACTER);
	this->objectWidth = DEFAULT_MAIN_WIDTH;
	this->objectHeight = DEFAULT_MAIN_HEIGHT;
	this->SetPosition(350, 300);
	this->SetVeclocity(0.0f, 0.0f);
	this->position.z = 0.0f;

	sprite = new  Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_MAIN_STAND, 1, 17, 32, 1.0f);
}

Item::~Item()
{

}


void Item::Update(float t)
{
	Object::Update(t);
	sprite->NextSprite();
}

void Item::Render()
{
	sprite->DrawSprite(this->position, true);
}

