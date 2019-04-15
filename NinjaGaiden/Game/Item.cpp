#include "Item.h"

Item::Item()
{
	this->SetObjectType(MAIN_CHARACTER);
	this->SetPosition(150, 100);
	this->SetVeclocity(0.0f, 0.0f);
	this->position.z = 0.0f;
	sprite = new  Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_MAIN_STAND, 1, 1.0f);
}

Item::~Item()
{

}


void Item::Update(float t)
{
	Object::Update(t);
	RECT rect = sprite->GetBoudingBoxFromCurrentSprite();
	Object::updateBoundingBox(rect);
	
	sprite->NextSprite();
}

void Item::Render()
{
	sprite->DrawSprite(this->position, true);
}

