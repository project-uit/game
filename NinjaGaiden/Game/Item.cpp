#include "Item.h"
#include "Camera1.h"
Item::Item()
{
	this->SetObjectType(MAIN_CHARACTER);
	this->SetPosition(100, 95);
	this->SetVeclocity(0.0f, 0.0f);
	this->position.z = 0.0f;
	sprite = new  Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_LiNH, 1);
}

Item::~Item()
{

}


void Item::Update(float t)
{
	Object::Update(t);
	RECT rect = sprite->GetBoudingBoxFromCurrentSprite();
	Object::updateBoundingBox(rect);
	Object::PlusPosition(this->deltaX, this->deltaY);
	sprite->NextSprite();
}

void Item::Render()
{
	D3DXVECTOR3 pos = Camera1::GetInstance()->transformObjectPosition(position);
	sprite->DrawSprite(pos, true);
}

